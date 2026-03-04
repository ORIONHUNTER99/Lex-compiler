#pragma once

#include <string>
#include <vector>
#include <optional>
#include "context.hpp"

namespace lex {

// ============================================================================
// Query Types
// ============================================================================

enum class QueryType {
    DEPENDENCIES,       // "What does X require?"
    DEPENDENTS,         // "What requires X?" / "What unlocks X?"
    PROPERTY,           // "What is X's era?" / "What is the cost of X?"
    FIND_BY_PROPERTY,   // "What produces Gold?" / "Which structures cost Gold?"
    FIND_BY_TYPE,       // "Show all structures" / "List technologies"
    COMPARE,            // "What costs the most?" / "Which is cheapest?"
    TREE,               // "Show technology tree" / "Show dependency tree"
    UNKNOWN
};

// ============================================================================
// Query Result
// ============================================================================

struct QueryResult {
    bool success = false;
    std::string answer;
    std::vector<std::string> entity_ids;  // Related entities
    std::string error;
    
    // For tree views
    std::string tree_output;
    
    bool has_answer() const { return !answer.empty(); }
};

// ============================================================================
// Query Parser
// ============================================================================

struct ParsedQuery {
    QueryType type = QueryType::UNKNOWN;
    std::string entity_name;           // Target entity (e.g., "Farm")
    std::string property_name;         // Property to query (e.g., "cost")
    std::string property_value;        // Value to match (e.g., "Gold")
    std::string entity_type;           // Type filter (e.g., "structure")
    std::string raw_query;             // Original query string
};

// Parse a natural language query
ParsedQuery parse_query(const std::string& query);

// ============================================================================
// Query Executor
// ============================================================================

// Execute a parsed query against a context
QueryResult execute_query(const ParsedQuery& query, const ContextResult& context);

// Convenience: parse and execute in one step
QueryResult query(const std::string& query_str, const ContextResult& context);

// ============================================================================
// Query Formatters
// ============================================================================

// Format query result for CLI output
std::string format_query_result(const QueryResult& result, bool verbose = false);

} // namespace lex
