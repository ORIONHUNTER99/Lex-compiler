# Lex API Reference

This document describes the public C++ API for programmatic use of the Lex compiler.

## Installation

### As a Library

Include Lex in your CMake project:

```cmake
add_subdirectory(lex)
target_link_libraries(your_target PRIVATE lex)
```

### Header

```cpp
#include <lex/lex.hpp>
```

## Namespace

All types and functions are in the `lex` namespace.

---

## Compilation

### compile()

Main entry point for compiling Lex source code.

```cpp
CompileResult compile(const std::string& source, const CompileOptions& options = {});
```

**Parameters:**
- `source`: Lex source code as a string
- `options`: Compilation options (optional)

**Returns:** `CompileResult` with outputs and errors

**Example:**
```cpp
#include <lex/lex.hpp>

int main() {
    std::string source = R"(
        era Ancient { name: "Ancient Age" }
        
        resource Gold {
            name: "Gold"
            category: currency
        }
    )";
    
    auto result = lex::compile(source);
    
    if (result.success) {
        // Get Lua output
        auto lua = result.get_output("lua");
        if (lua) {
            std::cout << *lua << std::endl;
        }
        
        // Get JSON output
        auto json = result.get_output("json");
        if (json) {
            std::cout << *json << std::endl;
        }
    } else {
        for (const auto& error : result.errors) {
            std::cerr << error.code << ": " << error.message << std::endl;
        }
    }
    
    return 0;
}
```

---

### compile_file()

Compile a Lex file from disk (with module support).

```cpp
CompileResult compile_file(const std::string& filepath, const CompileOptions& options = {});
```

**Parameters:**
- `filepath`: Path to the .lex file
- `options`: Compilation options (optional)

**Example:**
```cpp
auto result = lex::compile_file("game/main.lex");
```

---

### compile_modules()

Compile multiple files as a module tree.

```cpp
CompileResult compile_modules(const std::string& entry_file, const CompileOptions& options = {});
```

**Parameters:**
- `entry_file`: Entry point file that imports other modules
- `options`: Compilation options (optional)

**Example:**
```cpp
lex::CompileOptions options;
options.base_path = "game/";
auto result = lex::compile_modules("game/main.lex", options);
```

---

## CompileOptions

Configuration for compilation.

```cpp
struct CompileOptions {
    // Custom definition types (empty = default Imperium schema)
    std::vector<std::string> types;
    
    // Output targets (default: Lua and JSON)
    std::vector<Target> targets = {Target::Lua, Target::JSON};
    
    // Enable validation (default: true)
    bool validate = true;
    
    // Verbose output (default: false)
    bool verbose = false;
    
    // Allow internal definitions (default: true)
    // Set to false for modder mode
    bool allow_internal = true;
    
    // Base path for resolving imports
    std::string base_path;
    
    // Source name for error messages
    std::string source_name = "input.lex";
    
    // Factory methods
    static CompileOptions defaults();
    static CompileOptions lua_only();
    static CompileOptions json_only();
    static CompileOptions for_modder();
};
```

---

## CompileResult

Result of a compilation.

```cpp
struct CompileResult {
    // Success status
    bool success = false;
    
    // Generated outputs by target name
    std::map<std::string, std::string> outputs;
    
    // Errors and warnings
    std::vector<CompileError> errors;
    std::vector<CompileError> warnings;
    
    // Convenience methods
    bool has_errors() const;
    bool has_warnings() const;
    std::optional<std::string> get_output(const std::string& target) const;
};
```

---

## Target Enum

Available output targets.

```cpp
enum class Target {
    Lua,        // Generic Lua tables
    JSON,       // Universal JSON
    Godot,      // GDScript Resource (Godot 4.x)
    Unity,      // C# ScriptableObject
    Love2D,     // LÖVE2D framework module
    Defold,     // Defold engine module
    TypeScript  // Planned
};
```

---

## Error Handling

### CompileError

```cpp
enum class CompileErrorSeverity {
    Error,
    Warning,
    Info
};

struct CompileError {
    std::string message;            // Human-readable error
    std::string location;            // "line:column" format
    CompileErrorSeverity severity;
    std::string code;               // Error code (e.g., "E001")
    std::string suggestion;          // Optional fix suggestion
};
```

---

## Utility Functions

### available_targets()

Get list of supported target names.

```cpp
std::vector<std::string> available_targets();
// Returns: {"lua", "json", "gd", "cs", "love2d", "defold"}
```

### default_types()

Get default schema types (Imperium).

```cpp
std::vector<std::string> default_types();
// Returns: {"era", "resource", "structure", "unit", "technology", ...}
```

### version()

Get compiler version string.

```cpp
std::string version();
// Returns: "1.0.0"
```

### target_extension()

Get file extension for a target.

```cpp
std::string target_extension(Target target);
std::string target_extension(const std::string& target_name);

// Examples:
// target_extension(Target::Lua) → ".lua"
// target_extension("gd") → ".gd"
```

---

## AI Context API

### generate_context_from_source()

Generate AI-friendly context from source code.

```cpp
ContextResult generate_context_from_source(
    const std::string& source,
    const ContextOptions& options = {}
);
```

**Parameters:**
- `source`: Lex source code
- `options`: Context generation options

**Returns:** `ContextResult` with structured entity information

**Example:**
```cpp
auto context = lex::generate_context_from_source(source);
for (const auto& entity : context.entities) {
    std::cout << entity.id << " (" << entity.type << "): " 
              << entity.summary << std::endl;
}
```

---

### generate_context_from_file()

Generate context from a file.

```cpp
ContextResult generate_context_from_file(
    const std::string& filepath,
    const ContextOptions& options = {}
);
```

---

## Query API

### query_context()

Execute a natural language query against generated context.

```cpp
QueryResult query_context(
    const std::string& query_str,
    const ContextResult& context
);
```

**Example:**
```cpp
auto context = lex::generate_context_from_file("game.lex");
auto result = lex::query_context("What costs the most?", context);
std::cout << result.answer << std::endl;
```

### query_file()

Convenience: compile and query in one step.

```cpp
QueryResult query_file(
    const std::string& filepath,
    const std::string& query_str,
    const ContextOptions& options = {}
);
```

---

## Complete Example

```cpp
#include <lex/lex.hpp>
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    // 1. Basic compilation
    std::string source = R"(
        era Ancient { name: "Ancient Age" }
        
        structure Farm {
            era: Ancient
            name: "Farm"
            cost: { Gold: 50 }
        }
    )";
    
    // 2. Configure options
    lex::CompileOptions options;
    options.targets = {lex::Target::Lua, lex::Target::JSON};
    options.validate = true;
    
    // 3. Compile
    auto result = lex::compile(source, options);
    
    // 4. Handle errors
    if (!result.success) {
        for (const auto& error : result.errors) {
            std::cerr << "[" << error.code << "] " 
                      << error.location << ": " 
                      << error.message << std::endl;
            if (!error.suggestion.empty()) {
                std::cerr << "  Suggestion: " << error.suggestion << std::endl;
            }
        }
        return 1;
    }
    
    // 5. Use outputs
    if (auto lua = result.get_output("lua")) {
        std::ofstream out("game.lua");
        out << *lua;
    }
    
    if (auto json = result.get_output("json")) {
        std::ofstream out("game.json");
        out << *json;
    }
    
    // 6. Generate AI context
    auto context = lex::generate_context_from_source(source);
    
    // 7. Query the context
    auto query = lex::query_context("What does Farm cost?", context);
    std::cout << "Answer: " << query.answer << std::endl;
    
    return 0;
}
```

---

## Version Compatibility

- **v1.0.0**: Stable API
- All public types in `lex` namespace are guaranteed stable
- Internal types may change between minor versions
- Breaking changes only in major versions

## License

MIT License - see LICENSE file for details.
