#include "lexer.h"
#include <cctype>

namespace lex {

Lexer::Lexer(const std::string& source, const std::string& filename)
    : source_(source), filename_(filename) {}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (pos_ < source_.size()) {
        tokens.push_back(scan_token());
    }

    tokens.push_back({TokenType::END_OF_FILE, "", {filename_, line_, column_}});
    return tokens;
}

Token Lexer::next_token() {
    return scan_token();
}

Token Lexer::peek_token() {
    size_t saved_pos = pos_;
    Token token = scan_token();
    pos_ = saved_pos;
    return token;
}

char Lexer::current() const {
    return pos_ < source_.size() ? source_[pos_] : '\0';
}

char Lexer::peek() const {
    return (pos_ + 1) < source_.size() ? source_[pos_ + 1] : '\0';
}

void Lexer::advance() {
    if (pos_ < source_.size()) {
        if (source_[pos_] == '\n') {
            line_++;
            column_ = 1;
        } else {
            column_++;
        }
        pos_++;
    }
}

void Lexer::skip_whitespace() {
    while (std::isspace(current())) {
        advance();
    }
}

void Lexer::skip_comment() {
    if (current() == '/' && peek() == '/') {
        while (current() != '\n' && current() != '\0') {
            advance();
        }
    } else if (current() == '/' && peek() == '*') {
        advance(); advance();
        while (!(current() == '*' && peek() == '/') && current() != '\0') {
            advance();
        }
        if (current() != '\0') {
            advance(); advance();
        }
    }
}

Token Lexer::scan_token() {
    skip_whitespace();

    if (current() == '/' && (peek() == '/' || peek() == '*')) {
        skip_comment();
        return scan_token();
    }

    if (pos_ >= source_.size()) {
        return {TokenType::END_OF_FILE, "", {filename_, line_, column_}};
    }

    Location loc{filename_, line_, column_, static_cast<int>(pos_)};

    Token token;
    token.location = loc;
    token.type = TokenType::ERROR;
    token.lexeme = current();

    advance();
    return token;
}

Token Lexer::scan_string() {
    return {};
}

Token Lexer::scan_number() {
    return {};
}

Token Lexer::scan_identifier() {
    return {};
}

Token Lexer::scan_hex_color() {
    return {};
}

}
