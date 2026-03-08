#include <iostream>
#include <filesystem>
#include <set>
#include <csignal>

#include <CLI/CLI.hpp>

#include "color.hpp"
#include "commands.hpp"
#include "../lex/lex.hpp"
#include "../license/license.hpp"

// Lex-Plus premium backends (conditional include)
#if __has_include("lex_plus.hpp")
#include "lex_plus.hpp"
#endif

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    CLI::App app{"Lex Compiler - Declarative multi-target transpiler for game content", "lexc"};

    std::string input_file;
    app.add_option("input", input_file, "Input .lex file or directory")
       ->required()
       ->check(CLI::ExistingPath);

    std::string output_dir;
    app.add_option("-o,--output", output_dir, "Output directory");

    std::string target_str = "lua";
    app.add_option("-t,--target", target_str,
        "Output format(s): lua,json,gd,cs,love2d,defold\n"
        "  Free: lua, json, godot, unity, love2d, defold\n"
        "  Premium (Lex-Plus): unreal, gamemaker, construct, bevy, pygame, raylib, cpp, rust, python, rpc");

    std::string context_str;
    app.add_option("--context", context_str, "Generate AI context: json,md,minimal,all");

    std::string query_str;
    app.add_option("--query", query_str, "Query game data in natural language");

    std::string types_str;
    app.add_option("--types", types_str, "Custom definition types (comma-separated)");

    std::string mode_str = "modder";
    app.add_option("--mode", mode_str, "Visibility mode: modder or developer");

    bool watch_mode = false;
    app.add_flag("--watch", watch_mode, "Watch for file changes and recompile");

    bool no_validate = false;
    app.add_flag("--no-validate", no_validate, "Skip semantic validation");

    bool verbose = false;
    app.add_flag("--verbose", verbose, "Show detailed output");

    bool show_version = false;
    app.add_flag("-v,--version", show_version, "Show version");

    std::string license_key;
    app.add_option("--license", license_key, "License key (or set LEX_LICENSE env)");

    CLI11_PARSE(app, argc, argv);

    // Register premium backends if Lex-Plus is available
#if __has_include("lex_plus.hpp")
    lex::register_premium_backends();
#endif

    // Show version with animated logo
    if (show_version) {
        std::cout << lex::cli::color::logo();
        return 0;
    }

    // Set default output directory
    if (output_dir.empty()) {
        output_dir = fs::path(input_file).parent_path().string();
        if (output_dir.empty()) output_dir = ".";
    }

    // Parse options
    lex::CompileOptions options;
    options.validate = !no_validate;
    options.verbose = verbose;
    options.source_name = input_file;
    options.allow_internal = (mode_str == "developer" || mode_str == "dev");

    if (!types_str.empty()) {
        std::stringstream ss(types_str);
        std::string type;
        while (std::getline(ss, type, ',')) {
            type.erase(0, type.find_first_not_of(" \t"));
            type.erase(type.find_last_not_of(" \t") + 1);
            if (!type.empty()) options.types.push_back(type);
        }
    }

    std::vector<std::string> target_names = lex::cli::parse_target_names(target_str);
    std::vector<lex::Target> targets = lex::cli::parse_targets(target_str);
    options.targets = targets;
    
    // Add custom targets (names not in the standard enum)
    std::set<std::string> standard_targets = {"lua", "json", "gd", "godot", "cs", "unity", "love2d", "love", "defold", "ts", "typescript"};
    for (const auto& name : target_names) {
        if (standard_targets.find(name) == standard_targets.end()) {
            options.custom_targets.push_back(name);
        }
    }

    // ========================================================================
    // License Verification
    // ========================================================================

    std::optional<lex::license::License> license;

    // Check --license flag first, then LEX_LICENSE env
    if (!license_key.empty()) {
        license = lex::license::LicenseManager::parse(license_key);
        if (!license) {
            std::cerr << lex::cli::color::red << "✗ Invalid license key format" << lex::cli::color::reset << "\n";
            return 1;
        }
    } else {
        license = lex::license::LicenseManager::from_env();
    }

    // Check for premium backends without license
    if (!license) {
        // Free tier: only free backends allowed
        for (const auto& target_name : target_names) {
            if (lex::license::CORE_BACKENDS.count(target_name) > 0) {
                std::cerr << lex::cli::color::red << "✗ Backend '" << target_name
                          << "' requires a license" << lex::cli::color::reset << "\n";
                std::cerr << lex::cli::color::yellow << "  Get a license: https://github.com/sponsors/David-Imperium"
                          << lex::cli::color::reset << "\n";
                std::cerr << lex::cli::color::dim << "  Free backends: lua, json, godot, unity, love2d, defold"
                          << lex::cli::color::reset << "\n";
                return 1;
            }
        }
    } else {
        // Licensed: check tier access
        auto available_backends = license->get_available_backends();
        for (const auto& target_name : target_names) {
            if (available_backends.count(target_name) == 0) {
                std::cerr << lex::cli::color::red << "✗ Your " << license->tier_name()
                          << " license doesn't include '" << target_name << "'" << lex::cli::color::reset << "\n";
                std::cerr << lex::cli::color::yellow << "  Upgrade: https://github.com/sponsors/David-Imperium"
                          << lex::cli::color::reset << "\n";
                return 1;
            }
        }

        if (verbose) {
            std::cout << lex::cli::color::green << "✓ License: " << license->tier_name()
                      << " (" << (license->is_lifetime ? "lifetime" : "subscription") << ")"
                      << lex::cli::color::reset << "\n";
        }
    }

    // ========================================================================
    // Command Dispatch
    // ========================================================================

    // Watch mode
    if (watch_mode) {
        auto result = lex::cli::run_watch_mode(input_file, output_dir, targets, target_names, options);
        return result.exit_code;
    }

    // Compile
    auto compile_result = lex::cli::run_compile(input_file, output_dir, targets, target_names, options, verbose);
    if (compile_result.exit_code != 0) {
        return compile_result.exit_code;
    }

    // Context generation (optional)
    if (!context_str.empty()) {
        auto ctx_result = lex::cli::run_context(input_file, output_dir, context_str);
        if (ctx_result.exit_code != 0) {
            return ctx_result.exit_code;
        }
    }

    // Query (optional)
    if (!query_str.empty()) {
        auto query_result = lex::cli::run_query(input_file, query_str);
        return query_result.exit_code;
    }

    return 0;
}
