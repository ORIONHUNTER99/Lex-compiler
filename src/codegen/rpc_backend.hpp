#pragma once

#include "backend.hpp"
#include <sstream>
#include <string>
#include <vector>
#include <map>

namespace lex {

/**
 * RPC Backend - Generates Python and Go code for JSON-RPC protocols.
 * 
 * Target names:
 * - "rpc" or "rpc_full" - Generates both Python and Go
 * - "rpc_python" - Generates only Python handlers and types
 * - "rpc_go" - Generates only Go types and client
 */
class RPCBackend : public Backend {
public:
    std::string name() const override { return "rpc"; }
    std::string file_extension() const override { return ".rpc"; }

    std::string generate(const std::vector<std::unique_ptr<Definition>>& ast) override;

private:
    // Parsed definitions
    struct MethodDef {
        std::string name;
        std::string input_type;
        std::string output_type;
    };
    
    struct StructDef {
        std::string name;
        std::vector<std::string> field_names;
        std::vector<std::string> field_types;
        std::vector<bool> field_optional;
    };
    
    std::vector<MethodDef> methods_;
    std::map<std::string, StructDef> structs_;
    
    void parse_definitions(const std::vector<std::unique_ptr<Definition>>& ast);
    void parse_method(const Definition& def);
    void parse_struct(const Definition& def);
    
    // Python generation
    std::string generate_python();
    std::string generate_python_types();
    std::string generate_python_handlers();
    std::string python_type(const std::string& lex_type);
    
    // Go generation
    std::string generate_go();
    std::string generate_go_types();
    std::string generate_go_client();
    std::string go_type(const std::string& lex_type);
    
    // Helpers
    std::string strip_optional(const std::string& type);
    std::string to_snake_case(const std::string& str);
    std::string to_pascal_case(const std::string& str);
};

} // namespace lex
