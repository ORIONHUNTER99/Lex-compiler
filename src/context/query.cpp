#include "query.hpp"
#include <sstream>
#include <algorithm>
#include <cctype>
#include <set>
#include <map>

namespace lex {

// ============================================================================
// Helper Functions
// ============================================================================

namespace {

// Convert string to lowercase
std::string to_lower(const std::string& s) {
    std::string result = s;
    for (auto& c : result) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return result;
}



// Tokenize string into words (removes punctuation)
std::vector<std::string> tokenize(const std::string& s) {
    std::vector<std::string> tokens;
    std::istringstream iss(s);
    std::string token;
    while (iss >> token) {
        // Remove punctuation from start and end
        size_t start = 0;
        size_t end = token.size();
        while (start < end && std::ispunct(static_cast<unsigned char>(token[start]))) start++;
        while (end > start && std::ispunct(static_cast<unsigned char>(token[end - 1]))) end--;
        if (start < end) {
            token = token.substr(start, end - start);
            tokens.push_back(to_lower(token));
        }
    }
    return tokens;
}

// Check if tokens contain a word (case-insensitive)
bool contains_word(const std::vector<std::string>& tokens, const std::string& word) {
    std::string lower_word = to_lower(word);
    for (const auto& t : tokens) {
        if (t == lower_word) return true;
    }
    return false;
}

// Get word after a specific token
std::string get_word_after(const std::vector<std::string>& tokens, const std::string& word) {
    std::string lower_word = to_lower(word);
    for (size_t i = 0; i + 1 < tokens.size(); i++) {
        if (tokens[i] == lower_word) {
            return tokens[i + 1];
        }
    }
    return "";
}



// Get the first capitalized word (likely entity name) - check original query
std::string extract_entity_name(const std::vector<std::string>& tokens, const std::string& original_query) {
    // Common words to skip (question words, articles, etc.)
    static const std::set<std::string> skip_words = {
        "what", "which", "who", "when", "where", "why", "how",
        "is", "are", "does", "do", "did", "has", "have", "can", "could", "would", "should",
        "the", "a", "an", "this", "that", "these", "those",
        "show", "list", "get", "find", "all"
    };
    
    // First, try to find capitalized words in the original query (excluding common words)
    std::istringstream orig_iss(original_query);
    std::string orig_token;
    while (orig_iss >> orig_token) {
        // Clean punctuation
        std::string clean;
        for (char c : orig_token) {
            if (std::isalnum(static_cast<unsigned char>(c))) {
                clean += c;
            }
        }
        
        if (!clean.empty() && std::isupper(static_cast<unsigned char>(clean[0]))) {
            std::string lower_clean = to_lower(clean);
            // Skip common words
            if (skip_words.find(lower_clean) == skip_words.end()) {
                return clean;
            }
        }
    }
    
    // Fallback: get word after "does", "is"
    for (size_t i = 0; i + 1 < tokens.size(); i++) {
        if (tokens[i] == "does" || tokens[i] == "is") {
            if (i + 1 < tokens.size()) {
                std::string candidate = tokens[i + 1];
                // Capitalize first letter
                if (!candidate.empty()) {
                    candidate[0] = static_cast<char>(std::toupper(static_cast<unsigned char>(candidate[0])));
                }
                return candidate;
            }
        }
    }
    return "";
}

// Get entity type from query (structure, technology, unit, etc.)
std::string extract_entity_type(const std::vector<std::string>& tokens) {
    static const std::set<std::string> types = {
        "structure", "structures", "technology", "technologies", "tech",
        "unit", "units", "era", "eras", "resource", "resources",
        "building", "buildings"
    };
    
    for (const auto& t : tokens) {
        if (types.count(t)) {
            // Singularize
            if (t == "structures") return "structure";
            if (t == "technologies" || t == "tech") return "technology";
            if (t == "units") return "unit";
            if (t == "eras") return "era";
            if (t == "resources") return "resource";
            if (t == "buildings") return "building";
            return t;
        }
    }
    return "";
}

// Get property name from query (handles synonyms and verb forms)
std::string extract_property(const std::vector<std::string>& tokens) {
    // Map of query terms to property names
    static const std::map<std::string, std::string> property_map = {
        {"cost", "cost"},
        {"costs", "cost"},
        {"production", "production"},
        {"produces", "production"},
        {"produce", "production"},
        {"maintenance", "maintenance"},
        {"era", "era"},
        {"attack", "attack"},
        {"defense", "defense"},
        {"movement", "movement"},
        {"research_cost", "research_cost"},
        {"unlocks", "unlocks"},
        {"unlock", "unlocks"},
        {"requires", "requires"},
        {"require", "requires"},
        {"prerequisites", "prerequisites"},
        {"prerequisite", "prerequisites"}
    };
    
    for (const auto& t : tokens) {
        auto it = property_map.find(t);
        if (it != property_map.end()) {
            return it->second;
        }
    }
    
    // Check for "X's Y" pattern
    for (size_t i = 0; i + 1 < tokens.size(); i++) {
        if (tokens[i].find("'s") != std::string::npos) {
            auto it = property_map.find(tokens[i + 1]);
            if (it != property_map.end()) {
                return it->second;
            }
        }
    }
    
    return "";
}

// Extract property value from query (e.g., "Gold" in "what produces Gold?")
std::string extract_property_value(const std::vector<std::string>& tokens, const std::string& prop) {
    // Map of query terms to property names (same as extract_property)
    static const std::map<std::string, std::string> property_map = {
        {"cost", "cost"},
        {"costs", "cost"},
        {"production", "production"},
        {"produces", "production"},
        {"produce", "production"},
        {"maintenance", "maintenance"},
        {"era", "era"},
        {"attack", "attack"},
        {"defense", "defense"},
        {"movement", "movement"},
        {"research_cost", "research_cost"},
        {"unlocks", "unlocks"},
        {"unlock", "unlocks"},
        {"requires", "requires"},
        {"require", "requires"},
        {"prerequisites", "prerequisites"},
        {"prerequisite", "prerequisites"}
    };
    
    // Look for any property term that maps to the target property
    for (size_t i = 0; i + 1 < tokens.size(); i++) {
        auto it = property_map.find(tokens[i]);
        if (it != property_map.end() && it->second == prop && i + 1 < tokens.size()) {
            std::string val = tokens[i + 1];
            // Capitalize
            if (!val.empty()) {
                val[0] = static_cast<char>(std::toupper(static_cast<unsigned char>(val[0])));
            }
            return val;
        }
    }
    return "";
}

} // anonymous namespace

// ============================================================================
// Query Parser
// ============================================================================

ParsedQuery parse_query(const std::string& query_str) {
    ParsedQuery result;
    result.raw_query = query_str;
    
    auto tokens = tokenize(query_str);
    if (tokens.empty()) {
        result.type = QueryType::UNKNOWN;
        return result;
    }
    
    // Pattern: "What does X require?" / "What does X need?"
    if ((contains_word(tokens, "what") && contains_word(tokens, "does")) ||
        (contains_word(tokens, "what") && contains_word(tokens, "need"))) {
        
        std::string entity = extract_entity_name(tokens, result.raw_query);
        if (!entity.empty()) {
            result.entity_name = entity;
            
            if (contains_word(tokens, "require") || contains_word(tokens, "needs")) {
                result.type = QueryType::DEPENDENCIES;
                return result;
            }
        }
    }
    
    // Pattern: "What requires X?" / "What unlocks X?" / "What needs X?"
    if (contains_word(tokens, "what")) {
        std::string after_requires = get_word_after(tokens, "requires");
        std::string after_unlocks = get_word_after(tokens, "unlocks");
        std::string after_needs = get_word_after(tokens, "needs");
        
        if (!after_requires.empty()) {
            result.type = QueryType::DEPENDENTS;
            result.entity_name = after_requires;
            // Capitalize first letter
            if (!result.entity_name.empty()) {
                result.entity_name[0] = static_cast<char>(std::toupper(static_cast<unsigned char>(result.entity_name[0])));
            }
            return result;
        }

        if (!after_unlocks.empty()) {
            result.type = QueryType::DEPENDENTS;
            result.entity_name = after_unlocks;
            if (!result.entity_name.empty()) {
                result.entity_name[0] = static_cast<char>(std::toupper(static_cast<unsigned char>(result.entity_name[0])));
            }
            return result;
        }
    }
    
    // Pattern: "What costs the most?" / "Which is cheapest?" / "What produces the most?"
    // IMPORTANT: Check this BEFORE FIND_BY_PROPERTY to avoid false matches
    if (contains_word(tokens, "most") || contains_word(tokens, "cheapest") || 
        contains_word(tokens, "expensive") || contains_word(tokens, "highest") ||
        contains_word(tokens, "lowest")) {
        
        std::string prop = extract_property(tokens);
        if (!prop.empty()) {
            result.type = QueryType::COMPARE;
            result.property_name = prop;
            return result;
        }
    }
    
    // Pattern: "What produces Gold?" / "Which structures cost Gold?"
    if (contains_word(tokens, "what") || contains_word(tokens, "which")) {
        std::string prop = extract_property(tokens);
        std::string val = extract_property_value(tokens, prop);
        std::string type = extract_entity_type(tokens);
        
        if (!prop.empty()) {
            result.type = QueryType::FIND_BY_PROPERTY;
            result.property_name = prop;
            result.property_value = val;
            result.entity_type = type;
            return result;
        }
    }
    
    // Pattern: "Show all structures" / "List technologies"
    if (contains_word(tokens, "show") || contains_word(tokens, "list")) {
        std::string type = extract_entity_type(tokens);
        if (!type.empty()) {
            result.type = QueryType::FIND_BY_TYPE;
            result.entity_type = type;
            return result;
        }
    }
    
    // Pattern: "Show technology tree" / "Show dependency tree"
    if (contains_word(tokens, "tree") || contains_word(tokens, "graph")) {
        result.type = QueryType::TREE;
        std::string type = extract_entity_type(tokens);
        result.entity_type = type.empty() ? "technology" : type;
        return result;
    }
    
    // Pattern: "What is X's era?" / "What is the cost of X?"
    if (contains_word(tokens, "what") && contains_word(tokens, "is")) {
        std::string entity = extract_entity_name(tokens, result.raw_query);
        std::string prop = extract_property(tokens);
        
        if (!entity.empty()) {
            result.type = QueryType::PROPERTY;
            result.entity_name = entity;
            result.property_name = prop;
            return result;
        }
    }
    
    // Fallback: check if first word is an entity name
    if (!tokens.empty() && std::isupper(static_cast<unsigned char>(tokens[0][0]))) {
        result.entity_name = tokens[0];
        
        // Check remaining tokens for clues
        if (contains_word(tokens, "require") || contains_word(tokens, "need")) {
            result.type = QueryType::DEPENDENCIES;
            return result;
        }
    }
    
    result.type = QueryType::UNKNOWN;
    return result;
}

// ============================================================================
// Query Executor
// ============================================================================

QueryResult execute_query(const ParsedQuery& query, const ContextResult& context) {
    QueryResult result;
    
    switch (query.type) {
        case QueryType::DEPENDENCIES: {
            // Find what an entity requires
            const EntityContext* entity = context.find_entity(query.entity_name);
            if (!entity) {
                result.success = false;
                result.error = "Entity not found: " + query.entity_name;
                return result;
            }
            
            result.success = true;
            result.entity_ids = entity->dependencies;
            
            if (entity->dependencies.empty()) {
                result.answer = entity->id + " has no dependencies";
            } else {
                result.answer = entity->id + " requires: " + 
                    [&]() {
                        std::string deps;
                        for (size_t i = 0; i < entity->dependencies.size(); i++) {
                            if (i > 0) deps += ", ";
                            deps += entity->dependencies[i];
                        }
                        return deps;
                    }();
            }
            break;
        }
        
        case QueryType::DEPENDENTS: {
            // Find what depends on an entity
            const EntityContext* entity = context.find_entity(query.entity_name);
            if (!entity) {
                result.success = false;
                result.error = "Entity not found: " + query.entity_name;
                return result;
            }
            
            result.success = true;
            result.entity_ids = entity->dependents;
            
            if (entity->dependents.empty()) {
                result.answer = "Nothing requires " + entity->id;
            } else {
                result.answer = entity->id + " is required by: " +
                    [&]() {
                        std::string deps;
                        for (size_t i = 0; i < entity->dependents.size(); i++) {
                            if (i > 0) deps += ", ";
                            deps += entity->dependents[i];
                        }
                        return deps;
                    }();
            }
            break;
        }
        
        case QueryType::PROPERTY: {
            const EntityContext* entity = context.find_entity(query.entity_name);
            if (!entity) {
                result.success = false;
                result.error = "Entity not found: " + query.entity_name;
                return result;
            }
            
            result.success = true;
            result.entity_ids.push_back(entity->id);
            
            if (query.property_name.empty()) {
                // Return all properties
                std::string props;
                for (const auto& [key, val] : entity->properties) {
                    if (!props.empty()) props += ", ";
                    props += key + ": " + val;
                }
                result.answer = entity->id + " properties: " + props;
            } else {
                // Return specific property
                auto it = entity->properties.find(query.property_name);
                if (it != entity->properties.end()) {
                    result.answer = entity->id + " " + query.property_name + ": " + it->second;
                } else {
                    result.answer = entity->id + " has no property '" + query.property_name + "'";
                }
            }
            break;
        }
        
        case QueryType::FIND_BY_PROPERTY: {
            std::vector<const EntityContext*> matches;
            
            for (const auto& entity : context.entities) {
                // Filter by type if specified
                if (!query.entity_type.empty() && entity.type != query.entity_type) {
                    continue;
                }
                
                // Check if property exists
                auto it = entity.properties.find(query.property_name);
                if (it != entity.properties.end()) {
                    // If value specified, check match
                    if (query.property_value.empty()) {
                        matches.push_back(&entity);
                    } else {
                        // Check if value contains the search term
                        if (it->second.find(query.property_value) != std::string::npos) {
                            matches.push_back(&entity);
                        }
                    }
                }
            }
            
            result.success = true;
            
            if (matches.empty()) {
                result.answer = "No entities found with property: " + query.property_name;
            } else {
                std::string answer;
                for (const auto* e : matches) {
                    result.entity_ids.push_back(e->id);
                    if (!answer.empty()) answer += "\n";
                    answer += e->id + " " + query.property_name + ": " + e->properties.at(query.property_name);
                }
                result.answer = answer;
            }
            break;
        }
        
        case QueryType::FIND_BY_TYPE: {
            auto entities = context.get_by_type(query.entity_type);
            
            result.success = true;
            
            if (entities.empty()) {
                result.answer = "No entities of type: " + query.entity_type;
            } else {
                std::string answer;
                for (const auto* e : entities) {
                    result.entity_ids.push_back(e->id);
                    if (!answer.empty()) answer += ", ";
                    answer += e->id;
                }
                result.answer = query.entity_type + "s: " + answer;
            }
            break;
        }
        
        case QueryType::COMPARE: {
            // Find entity with highest/lowest property value
            const EntityContext* best = nullptr;
            int64_t best_value = 0;
            bool find_max = !contains_word(tokenize(query.raw_query), "lowest") && 
                           !contains_word(tokenize(query.raw_query), "cheapest");
            
            for (const auto& entity : context.entities) {
                auto it = entity.properties.find(query.property_name);
                if (it != entity.properties.end()) {
                    // Try to extract numeric value from property
                    // Handle resource maps like "{Gold: 50, Wood: 20}"
                    std::string val = it->second;
                    
                    // Simple extraction: find first number
                    int64_t num = 0;
                    bool found = false;
                    for (size_t i = 0; i < val.size(); i++) {
                        if (std::isdigit(static_cast<unsigned char>(val[i]))) {
                            num = num * 10 + (val[i] - '0');
                            found = true;
                        } else if (found) {
                            break;
                        }
                    }
                    
                    if (found) {
                        if (!best || (find_max && num > best_value) || (!find_max && num < best_value)) {
                            best = &entity;
                            best_value = num;
                        }
                    }
                }
            }
            
            result.success = true;
            
            if (best) {
                result.entity_ids.push_back(best->id);
                result.answer = best->id + " has the " + 
                    (find_max ? "highest" : "lowest") + " " + query.property_name + ": " +
                    best->properties.at(query.property_name);
            } else {
                result.answer = "Could not compare " + query.property_name + " values";
            }
            break;
        }
        
        case QueryType::TREE: {
            // Build tree visualization
            std::ostringstream tree;
            
            // Group by era
            std::map<std::string, std::vector<const EntityContext*>> by_era;
            for (const auto& entity : context.entities) {
                if (entity.type == query.entity_type || query.entity_type.empty()) {
                    auto era_it = entity.properties.find("era");
                    std::string era = era_it != entity.properties.end() ? era_it->second : "Unknown";
                    by_era[era].push_back(&entity);
                }
            }
            
            for (const auto& [era, entities] : by_era) {
                tree << era << " Era:\n";
                
                for (const auto* e : entities) {
                    tree << "  " << e->id;
                    
                    // Show unlocks
                    auto unlocks_it = e->properties.find("unlocks");
                    if (unlocks_it != e->properties.end()) {
                        tree << " -> " << unlocks_it->second;
                    }
                    
                    tree << "\n";
                }
            }
            
            result.success = true;
            result.tree_output = tree.str();
            result.answer = result.tree_output;
            break;
        }
        
        case QueryType::UNKNOWN:
        default:
            result.success = false;
            result.error = "Could not understand query: " + query.raw_query;
            break;
    }
    
    return result;
}

QueryResult query(const std::string& query_str, const ContextResult& context) {
    auto parsed = parse_query(query_str);
    return execute_query(parsed, context);
}

// ============================================================================
// Query Formatter
// ============================================================================

std::string format_query_result(const QueryResult& result, bool verbose) {
    if (!result.success) {
        return "Error: " + result.error;
    }

    if (!verbose) {
        return result.answer;
    }

    // Verbose mode: include additional details
    std::ostringstream out;
    out << result.answer;

    if (!result.entity_ids.empty()) {
        out << "\n\nEntities: " << result.entity_ids.size();
        for (const auto& id : result.entity_ids) {
            out << "\n  - " << id;
        }
    }

    if (!result.tree_output.empty() && result.tree_output != result.answer) {
        out << "\n\n" << result.tree_output;
    }

    return out.str();
}

} // namespace lex
