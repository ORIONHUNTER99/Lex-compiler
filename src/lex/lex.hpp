#pragma once

#include <string>
#include <vector>
#include <map>
#include <optional>
#include <functional>

namespace lex {

// ============================================================================
// Public API - Lex Compiler Library
// ============================================================================

// Forward declarations
class Lexer;
class Parser;
class TypeChecker;
class Validator;
class Backend;
class SchemaRegistry;

// ============================================================================
// Error Handling
// ============================================================================

enum class CompileErrorSeverity {
    Error,
    Warning,
    Info
};

struct CompileError {
    std::string message;
    std::string location;       // "line:column" format
    CompileErrorSeverity severity;
    std::string code;           // Error code (e.g., "E001")
    std::string suggestion;     // Optional fix suggestion
};

// ============================================================================
// Configuration
// ============================================================================

enum class Target {
    Lua,
    JSON,
    TypeScript  // Planned
};

struct CompileOptions {
    // Schema configuration
    std::vector<std::string> types;     // Custom definition types (empty = default)
    
    // Output targets
    std::vector<Target> targets = {Target::Lua, Target::JSON};
    
    // Validation
    bool validate = true;
    bool verbose = false;
    
    // Source info (for error messages)
    std::string source_name = "input.lex";
    
    // Convenience factory methods
    static CompileOptions defaults() { return {}; }
    static CompileOptions lua_only() { return {.targets = {Target::Lua}}; }
    static CompileOptions json_only() { return {.targets = {Target::JSON}}; }
};

// ============================================================================
// Compilation Result
// ============================================================================

struct CompileResult {
    // Success status
    bool success = false;
    
    // Generated output by target name ("lua", "json", "ts")
    std::map<std::string, std::string> outputs;
    
    // Errors and warnings
    std::vector<CompileError> errors;
    std::vector<CompileError> warnings;
    
    // Convenience
    bool has_errors() const { return !errors.empty(); }
    bool has_warnings() const { return !warnings.empty(); }
    
    // Get specific output
    std::optional<std::string> get_output(const std::string& target) const {
        auto it = outputs.find(target);
        if (it != outputs.end()) return it->second;
        return std::nullopt;
    }
};

// ============================================================================
// Main API Functions
// ============================================================================

// Compile from string (main entry point)
CompileResult compile(const std::string& source, const CompileOptions& options = {});

// Compile from file
CompileResult compile_file(const std::string& filepath, const CompileOptions& options = {});

// ============================================================================
// Low-Level API (for advanced use)
// ============================================================================

// Get list of available targets
std::vector<std::string> available_targets();

// Get default schema types (Imperium)
std::vector<std::string> default_types();

// Validate source without generating output
CompileResult validate(const std::string& source, const CompileOptions& options = {});

// ============================================================================
// Utility Functions
// ============================================================================

// Get version string
std::string version();

// Get target file extension
std::string target_extension(Target target);
std::string target_extension(const std::string& target_name);

} // namespace lex
