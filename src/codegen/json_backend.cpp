#include "json_backend.h"
#include "lex/version.h"
#include <sstream>

namespace lex {

std::string JsonBackend::generate(const std::vector<std::unique_ptr<Definition>>& ast) {
    std::stringstream output;

    output << "{\n";
    output << "  \"version\": \"1.0\",\n";
    output << "  \"generated_by\": \"Lex Compiler v" LEX_VERSION "\",\n";

    // Group definitions by type (dynamic)
    std::map<std::string, std::vector<const Definition*>> definitions_by_type;

    for (const auto& def : ast) {
        definitions_by_type[def->definition_type].push_back(def.get());
    }

    bool needComma = false;

    // Generate each type group
    for (const auto& [type_name, defs] : definitions_by_type) {
        if (needComma) output << ",\n";

        output << "  \"" << type_name << "s\": {\n";

        for (size_t i = 0; i < defs.size(); i++) {
            output << generate_generic(*defs[i]);
            if (i < defs.size() - 1) output << ",\n";
            else output << "\n";
        }

        output << "  }";
        needComma = true;
    }

    output << "\n}\n";

    return output.str();
}

std::string JsonBackend::escape_string(const std::string& s) {
    std::string result;
    for (char c : s) {
        switch (c) {
            case '"': result += "\\\""; break;
            case '\\': result += "\\\\"; break;
            case '\n': result += "\\n"; break;
            case '\t': result += "\\t"; break;
            default: result += c;
        }
    }
    return result;
}

std::string JsonBackend::generate_generic(const Definition& def) {
    std::stringstream json;
    json << "    \"" << def.identifier << "\": {\n";

    std::vector<std::string> props;
    props.push_back("\"id\": \"" + def.identifier + "\"");
    props.push_back("\"type\": \"" + def.definition_type + "\"");

    // Generate all properties dynamically
    for (const auto& prop : def.properties) {
        if (prop->value) {
            props.push_back(generate_property_value(*prop));
        }
    }

    // Output with proper comma handling
    for (size_t i = 0; i < props.size(); i++) {
        json << "      " << props[i];
        if (i < props.size() - 1) json << ",";
        json << "\n";
    }

    json << "    }";
    return json.str();
}

std::string JsonBackend::generate_property_value(const Property& prop) {
    std::stringstream result;

    if (!prop.value) return "";

    switch (prop.value->type) {
        case PropertyValue::Type::EXPRESSION:
            if (prop.value->expression) {
                auto& expr = prop.value->expression;
                switch (expr->type) {
                    case Expression::Type::STRING:
                        result << "\"" << prop.name << "\": \""
                               << escape_string(std::get<std::string>(expr->value)) << "\"";
                        break;
                    case Expression::Type::INTEGER:
                        result << "\"" << prop.name << "\": "
                               << std::get<int64_t>(expr->value);
                        break;
                    case Expression::Type::FLOAT:
                        result << "\"" << prop.name << "\": "
                               << std::get<double>(expr->value);
                        break;
                    case Expression::Type::BOOLEAN:
                        result << "\"" << prop.name << "\": "
                               << (std::get<bool>(expr->value) ? "true" : "false");
                        break;
                    case Expression::Type::REFERENCE:
                        result << "\"" << prop.name << "\": \""
                               << expr->reference << "\"";
                        break;
                    default:
                        // For complex expressions, output as string representation
                        result << "\"" << prop.name << "\": \"(expression)\"";
                }
            }
            break;
        case PropertyValue::Type::RESOURCE_MAP:
            if (prop.value->resource_map) {
                result << "\"" << prop.name << "\": "
                       << generate_resource_map(*prop.value->resource_map);
            }
            break;
        case PropertyValue::Type::REFERENCE_LIST:
            if (prop.value->reference_list) {
                result << "\"" << prop.name << "\": "
                       << generate_reference_list(*prop.value->reference_list);
            }
            break;
    }

    return result.str();
}

std::string JsonBackend::generate_resource_map(const ResourceMap& map) {
    std::string json = "{";
    bool first = true;
    for (const auto& [name, value] : map.resources) {
        if (!first) json += ", ";
        json += "\"" + name + "\": " + std::to_string(value);
        first = false;
    }
    json += "}";
    return json;
}

std::string JsonBackend::generate_reference_list(const ReferenceList& list) {
    std::string json = "[";
    for (size_t i = 0; i < list.references.size(); i++) {
        if (i > 0) json += ", ";
        json += "\"" + list.references[i] + "\"";
    }
    json += "]";
    return json;
}

} // namespace lex
