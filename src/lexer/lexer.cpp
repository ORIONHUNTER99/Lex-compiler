#include "lexer.h"
#include "keywords.h"
#include <cctype>

namespace lex {

Lexer::Lexer(const std::string& source, const std::string& filename)
    : source_(source), filename_(filename) {}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    Token token = scan_token();
    while (token.type != TokenType::END_OF_FILE) {
        tokens.push_back(token);
        token = scan_token();
    }
    tokens.push_back(token);
    return tokens;
}

Token Lexer::next_token() {
    return scan_token();
}

Token Lexer::peek_token() {
    size_t saved_pos = pos_;
    int saved_line = line_;
    int saved_col = column_;
    Token token = scan_token();
    pos_ = saved_pos;
    line_ = saved_line;
    column_ = saved_col;
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
        advance();
        advance();
        while (!(current() == '*' && peek() == '/') && current() != '\0') {
            advance();
        }
        if (current() != '\0') {
            advance();
            advance();
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
    char c = current();

    if (c == '"') return scan_string();
    if (c == '#') return scan_hex_color();
    if (std::isdigit(c)) return scan_number();
    if (std::isalpha(c) || c == '_') return scan_identifier();

    if (c == '=' && peek() == '=') { advance(); advance(); return {TokenType::EQ, "==", loc}; }
    if (c == '!' && peek() == '=') { advance(); advance(); return {TokenType::NE, "!=", loc}; }
    if (c == '>' && peek() == '=') { advance(); advance(); return {TokenType::GE, ">=", loc}; }
    if (c == '<' && peek() == '=') { advance(); advance(); return {TokenType::LE, "<=", loc}; }
    if (c == '+' && peek() == '=') { advance(); advance(); return {TokenType::PLUS_ASSIGN, "+=", loc}; }
    if (c == '-' && peek() == '=') { advance(); advance(); return {TokenType::MINUS_ASSIGN, "-=", loc}; }
    if (c == '-' && peek() == '>') { advance(); advance(); return {TokenType::ARROW, "->", loc}; }
    if (c == '.' && peek() == '.') { advance(); advance(); return {TokenType::RANGE, "..", loc}; }

    advance();
    switch (c) {
        case '+': return {TokenType::PLUS, "+", loc};
        case '-': return {TokenType::MINUS, "-", loc};
        case '*': return {TokenType::STAR, "*", loc};
        case '/': return {TokenType::SLASH, "/", loc};
        case '%': return {TokenType::PERCENT, "%", loc};
        case '=': return {TokenType::ASSIGN, "=", loc};
        case '>': return {TokenType::GT, ">", loc};
        case '<': return {TokenType::LT, "<", loc};
        case '{': return {TokenType::LEFT_BRACE, "{", loc};
        case '}': return {TokenType::RIGHT_BRACE, "}", loc};
        case '[': return {TokenType::LEFT_BRACKET, "[", loc};
        case ']': return {TokenType::RIGHT_BRACKET, "]", loc};
        case '(': return {TokenType::LEFT_PAREN, "(", loc};
        case ')': return {TokenType::RIGHT_PAREN, ")", loc};
        case ':': return {TokenType::COLON, ":", loc};
        case ',': return {TokenType::COMMA, ",", loc};
        case '.': return {TokenType::DOT, ".", loc};
        case ';': return {TokenType::SEMICOLON, ";", loc};
        default:
            errors_.push_back("Unexpected character: " + std::string(1, c));
            return {TokenType::ERROR, std::string(1, c), loc};
    }
}

Token Lexer::scan_identifier() {
    Location loc{filename_, line_, column_, static_cast<int>(pos_)};
    std::string text;

    while (std::isalnum(current()) || current() == '_') {
        text += current();
        advance();
    }

    auto it = KEYWORDS.find(text);
    if (it != KEYWORDS.end()) {
        Token token{it->second, text, loc};
        if (it->second == TokenType::TRUE) token.value = true;
        else if (it->second == TokenType::FALSE) token.value = false;
        else if (it->second == TokenType::NULL_LIT) token.value = std::string{"null"};
        return token;
    }

    return {TokenType::IDENTIFIER, text, loc};
}

Token Lexer::scan_number() {
    Location loc{filename_, line_, column_, static_cast<int>(pos_)};
    std::string text;
    bool is_float = false;

    while (std::isdigit(current())) {
        text += current();
        advance();
    }

    if (current() == '.' && std::isdigit(peek())) {
        is_float = true;
        text += current();
        advance();
        while (std::isdigit(current())) {
            text += current();
            advance();
        }
    }

    if (is_float) {
        return {TokenType::FLOAT, text, loc, std::stod(text)};
    }
    return {TokenType::INTEGER, text, loc, static_cast<int64_t>(std::stoll(text))};
}

Token Lexer::scan_string() {
    Location loc{filename_, line_, column_, static_cast<int>(pos_)};
    std::string text;

    advance();

    while (current() != '"' && current() != '\0') {
        if (current() == '\\') {
            advance();
            switch (current()) {
                case 'n': text += '\n'; break;
                case 't': text += '\t'; break;
                case '"': text += '"'; break;
                case '\\': text += '\\'; break;
                default:
                    errors_.push_back("Unknown escape sequence: \\" + std::string(1, current()));
                    text += current();
            }
        } else {
            text += current();
        }
        advance();
    }

    if (current() == '\0') {
        errors_.push_back("Unterminated string");
        return {TokenType::ERROR, text, loc};
    }

    advance();
    return {TokenType::STRING, text, loc, text};
}

Token Lexer::scan_hex_color() {
    Location loc{filename_, line_, column_, static_cast<int>(pos_)};
    std::string text;

    text += current();
    advance();

    for (int i = 0; i < 6; i++) {
        if (!std::isxdigit(current())) {
            errors_.push_back("Invalid hex color format");
            return {TokenType::ERROR, text, loc};
        }
        text += current();
        advance();
    }

    return {TokenType::HEX_COLOR, text, loc, text};
}

}
