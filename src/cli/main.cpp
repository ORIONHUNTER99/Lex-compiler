#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include <set>

#include "../lex/lex.hpp"

namespace fs = std::filesystem;

void print_usage(const char* program) {
    std::cerr << "Lex Compiler v" << lex::version() << "\n\n";
    std::cerr << "Usage: " << program << " <input.lex> [options]\n\n";
    std::cerr << "Options:\n";
    std::cerr << "  -o, --output <dir>   Output directory (default: same as input)\n";
    std::cerr << "  -t, --target <fmt>   Output format(s): lua, json, gd, cs\n";
    std::cerr << "  --types <list>       Definition types (comma-separated)\n";
    std::cerr << "                       Default: Imperium types (era,structure,unit,...)\n";
    std::cerr << "  --no-validate        Skip semantic validation\n";
    std::cerr << "  --verbose            Show detailed output\n";
    std::cerr << "  -h, --help           Show this help\n";
}

void write_file(const std::string& path, const std::string& content) {
    std::ofstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot write file: " + path);
    }
    file << content;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }

    std::string input_file;
    std::string output_dir;
    std::string target_str = "lua";
    std::string types_str;
    bool validate = true;
    bool verbose = false;

    // Parse arguments
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--help") {
            print_usage(argv[0]);
            return 0;
        } else if (arg == "-o" || arg == "--output") {
            if (i + 1 >= argc) {
                std::cerr << "Error: --output requires a directory\n";
                return 1;
            }
            output_dir = argv[++i];
        } else if (arg == "-t" || arg == "--target") {
            if (i + 1 >= argc) {
                std::cerr << "Error: --target requires a format\n";
                return 1;
            }
            target_str = argv[++i];
        } else if (arg == "--types") {
            if (i + 1 >= argc) {
                std::cerr << "Error: --types requires a list\n";
                return 1;
            }
            types_str = argv[++i];
        } else if (arg == "--no-validate") {
            validate = false;
        } else if (arg == "--verbose") {
            verbose = true;
        } else if (arg[0] != '-') {
            input_file = arg;
        } else {
            std::cerr << "Unknown option: " << arg << "\n";
            return 1;
        }
    }

    if (input_file.empty()) {
        std::cerr << "Error: No input file specified\n";
        return 1;
    }

    // Default output dir to input file's directory
    if (output_dir.empty()) {
        output_dir = fs::path(input_file).parent_path().string();
    }

    // Configure compilation options
    lex::CompileOptions options;
    options.validate = validate;
    options.verbose = verbose;
    options.source_name = input_file;

    // Parse types
    if (!types_str.empty()) {
        std::stringstream ss(types_str);
        std::string type;
        while (std::getline(ss, type, ',')) {
            type.erase(0, type.find_first_not_of(" \t"));
            type.erase(type.find_last_not_of(" \t") + 1);
            if (!type.empty()) {
                options.types.push_back(type);
            }
        }
    }

    // Parse targets
    std::vector<std::string> target_names;
    {
        std::stringstream ts(target_str);
        std::string t;
        while (std::getline(ts, t, ',')) {
            t.erase(0, t.find_first_not_of(" \t"));
            t.erase(t.find_last_not_of(" \t") + 1);
            if (!t.empty()) {
                target_names.push_back(t);
                if (t == "lua") options.targets.push_back(lex::Target::Lua);
                else if (t == "json") options.targets.push_back(lex::Target::JSON);
                else if (t == "gd" || t == "godot") options.targets.push_back(lex::Target::Godot);
                else if (t == "cs" || t == "unity" || t == "csharp") options.targets.push_back(lex::Target::Unity);
            }
        }
    }

    // Compile
    lex::CompileResult result = lex::compile_file(input_file, options);

    // Show warnings
    if (result.has_warnings()) {
        std::cerr << "Warnings:\n";
        for (const auto& warn : result.warnings) {
            std::cerr << "  [" << warn.code << "] " << warn.message;
            if (!warn.location.empty()) std::cerr << " at " << warn.location;
            std::cerr << "\n";
        }
    }

    // Show errors
    if (result.has_errors()) {
        std::cerr << "Errors:\n";
        for (const auto& err : result.errors) {
            std::cerr << "  [" << err.code << "] " << err.message;
            if (!err.location.empty()) std::cerr << " at " << err.location;
            if (!err.suggestion.empty()) std::cerr << "\n    Suggestion: " << err.suggestion;
            std::cerr << "\n";
        }
        return 1;
    }

    // Write output files
    fs::path input_path(input_file);
    std::string base_name = input_path.stem().string();

    for (const auto& [target_name, output] : result.outputs) {
        std::string extension = lex::target_extension(target_name);
        fs::path output_path = fs::path(output_dir) / (base_name + extension);

        try {
            write_file(output_path.string(), output);
            std::cout << "Generated: " << output_path.string() << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
            return 1;
        }
    }

    if (verbose) {
        std::cerr << "Compilation successful\n";
        std::cerr << "  Targets: " << target_names.size() << "\n";
        std::cerr << "  Warnings: " << result.warnings.size() << "\n";
    }

    return 0;
}
