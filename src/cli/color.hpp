#pragma once

#include <string>

namespace lex::cli {

// ANSI color codes for terminal output
namespace color {
    constexpr const char* reset = "\033[0m";
    constexpr const char* bold = "\033[1m";
    constexpr const char* dim = "\033[2m";
    constexpr const char* red = "\033[31m";
    constexpr const char* green = "\033[32m";
    constexpr const char* yellow = "\033[33m";
    constexpr const char* blue = "\033[34m";
    constexpr const char* magenta = "\033[35m";
    constexpr const char* cyan = "\033[36m";
    constexpr const char* white = "\033[37m";

    inline std::string logo() {
        return std::string(green) + bold + R"(
    ╔═══════════════════════════════════╗
    ║  )" + cyan + "Lex" + green + R"( Compiler v)" + white + "1.0.0" + green + R"(              ║
    ║  Declarative Game Content        ║
    ╚═══════════════════════════════════╝
)" + reset;
    }
}

} // namespace lex::cli
