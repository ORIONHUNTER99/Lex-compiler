#include "lex.hpp"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "parser/validator.h"
#include "semantic/type_checker.h"
#include "codegen/lua_backend.h"
#include "codegen/json_backend.h"
#include "codegen/godot_backend.h"
#include "codegen/unity_backend.h"
#include "schema/schema.h"

#include <fstream>
#include <sstream>

namespace lex {

// ============================================================================
// Version Info
// ============================================================================

std::string version() {
    return "0.3.1";
}

// ============================================================================
// Utility Functions
// ============================================================================

std::vector<std::string> available_targets() {
    return {"lua", "json", "gd", "cs"};
}

std::vector<std::string> default_types() {
    return {"era", "structure", "unit", "technology", "resource", 
            "choice", "ending", "event", "secret"};
}

std::string target_extension(Target target) {
    switch (target) {
        case Target::Lua: return ".lua";
        case Target::JSON: return ".json";
        case Target::TypeScript: return ".ts";
        default: return "";
    }
}

std::string target_extension(const std::string& target_name) {
    if (target_name == "lua") return ".lua";
    if (target_name == "json") return ".json";
    if (target_name == "gd" || target_name == "godot") return ".gd";
    if (target_name == "cs" || target_name == "unity" || target_name == "csharp") return ".cs";
    if (target_name == "ts" || target_name == "typescript") return ".ts";
    return "";
}

// ============================================================================
// Helper: Convert internal errors to public API format
// ============================================================================

static std::vector<CompileError> convert_lexer_errors(const std::vector<std::string>& errors) {
    std::vector<CompileError> result;
    for (const auto& err : errors) {
        result.push_back({
            .message = err,
            .location = "",
            .severity = CompileErrorSeverity::Error,
            .code = "L001",
            .suggestion = ""
        });
    }
    return result;
}

static std::vector<CompileError> convert_parser_errors(const std::vector<std::string>& errors) {
    std::vector<CompileError> result;
    for (const auto& err : errors) {
        result.push_back({
            .message = err,
            .location = "",
            .severity = CompileErrorSeverity::Error,
            .code = "P001",
            .suggestion = ""
        });
    }
    return result;
}

static std::vector<CompileError> convert_validation_errors(const std::vector<SemanticError>& errors) {
    std::vector<CompileError> result;
    for (const auto& err : errors) {
        result.push_back({
            .message = err.message,
            .location = err.location,
            .severity = err.severity == ErrorSeverity::ERROR ? CompileErrorSeverity::Error : CompileErrorSeverity::Warning,
            .code = err.code,
            .suggestion = ""
        });
    }
    return result;
}

// ============================================================================
// Main Compile Function
// ============================================================================

CompileResult compile(const std::string& source, const CompileOptions& options) {
    CompileResult result;
    
    // Initialize schema registry
    auto& schema = SchemaRegistry::instance();
    if (options.types.empty()) {
        schema.load_imperium_default();
    } else {
        std::string types_str;
        for (size_t i = 0; i < options.types.size(); i++) {
            if (i > 0) types_str += ",";
            types_str += options.types[i];
        }
        schema.load_from_cli(types_str);
    }
    
    // Phase 1: Lexical Analysis
    Lexer lexer(source, options.source_name);
    auto tokens = lexer.tokenize();
    if (lexer.has_errors()) {
        result.errors = convert_lexer_errors(lexer.errors());
        result.success = false;
        return result;
    }
    
    // Phase 2: Parsing
    Parser parser(tokens);
    auto ast = parser.parse();
    if (parser.has_errors()) {
        result.errors = convert_parser_errors(parser.errors());
        result.success = false;
        return result;
    }
    
    // Phase 3: Semantic Validation (optional)
    if (options.validate) {
        Validator validator;
        validator.validate(ast);
        
        if (validator.has_warnings()) {
            result.warnings = convert_validation_errors(validator.warnings());
        }
        
        if (validator.has_errors()) {
            result.errors = convert_validation_errors(validator.errors());
            result.success = false;
            return result;
        }
    }
    
    // Phase 4: Code Generation
    for (const auto& target : options.targets) {
        std::string output;
        std::string target_name;
        
        switch (target) {
            case Target::Lua: {
                LuaBackend backend;
                output = backend.generate(ast);
                target_name = "lua";
                break;
            }
            case Target::JSON: {
                JsonBackend backend;
                output = backend.generate(ast);
                target_name = "json";
                break;
            }
            case Target::Godot: {
                GodotBackend backend;
                output = backend.generate(ast);
                target_name = "gd";
                break;
            }
            case Target::Unity: {
                UnityBackend backend;
                output = backend.generate(ast);
                target_name = "cs";
                break;
            }
            case Target::TypeScript: {
                // Planned - not yet implemented
                result.warnings.push_back({
                    .message = "TypeScript backend not yet implemented",
                    .location = "",
                    .severity = CompileErrorSeverity::Warning,
                    .code = "W001",
                    .suggestion = "Use Lua, JSON, GD or CS backend for now"
                });
                continue;
            }
        }
        
        result.outputs[target_name] = output;
    }
    
    result.success = true;
    return result;
}

// ============================================================================
// Compile from File
// ============================================================================

CompileResult compile_file(const std::string& filepath, const CompileOptions& options) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        CompileResult result;
        result.success = false;
        result.errors.push_back({
            .message = "Cannot open file: " + filepath,
            .location = "",
            .severity = CompileErrorSeverity::Error,
            .code = "F001",
            .suggestion = "Check that the file exists and is readable"
        });
        return result;
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    
    auto new_options = options;
    new_options.source_name = filepath;
    
    return compile(buffer.str(), new_options);
}

// ============================================================================
// Validate Only
// ============================================================================

CompileResult validate(const std::string& source, const CompileOptions& options) {
    auto validate_options = options;
    validate_options.targets = {};  // No code generation
    return compile(source, validate_options);
}

} // namespace lex
