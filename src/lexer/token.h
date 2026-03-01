#pragma once

#include <string>
#include <variant>
#include <cstdint>

namespace lex {

enum class TokenType {
    END_OF_FILE,
    ERROR
};

struct Location {
    std::string file;
    int line = 0;
    int column = 0;
    int start = 0;
    int end = 0;
};

struct Token {
    TokenType type = TokenType::ERROR;
    std::string lexeme;
    Location location;
    std::variant<int64_t, double, std::string, bool> value;
};

}
