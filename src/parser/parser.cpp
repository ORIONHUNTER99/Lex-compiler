#include "parser.h"

namespace lex {

Parser::Parser(const std::vector<Token>& tokens)
    : tokens_(tokens) {}

std::vector<std::unique_ptr<Definition>> Parser::parse_file() {
    std::vector<std::unique_ptr<Definition>> definitions;

    while (pos_ < tokens_.size() && current().type != TokenType::END_OF_FILE) {
        auto def = parse_definition();
        if (def) {
            definitions.push_back(std::move(def));
        }
    }

    return definitions;
}

Token& Parser::current() {
    return tokens_[pos_];
}

Token& Parser::peek(int offset) {
    size_t idx = pos_ + offset;
    return idx < tokens_.size() ? tokens_[idx] : tokens_.back();
}

bool Parser::check(TokenType type) {
    return current().type == type;
}

bool Parser::match(TokenType type) {
    if (check(type)) {
        pos_++;
        return true;
    }
    return false;
}

Token Parser::consume(TokenType type, const std::string& message) {
    if (check(type)) {
        return tokens_[pos_++];
    }
    errors_.push_back(message);
    return current();
}

std::unique_ptr<Definition> Parser::parse_definition() {
    return nullptr;
}

std::unique_ptr<StructureDefinition> Parser::parse_structure() {
    return nullptr;
}

std::unique_ptr<UnitDefinition> Parser::parse_unit() {
    return nullptr;
}

std::unique_ptr<TechnologyDefinition> Parser::parse_technology() {
    return nullptr;
}

std::unique_ptr<EraDefinition> Parser::parse_era() {
    return nullptr;
}

std::unique_ptr<ChoiceDefinition> Parser::parse_choice() {
    return nullptr;
}

std::unique_ptr<EndingDefinition> Parser::parse_ending() {
    return nullptr;
}

std::unique_ptr<Property> Parser::parse_property() {
    return nullptr;
}

std::unique_ptr<Expression> Parser::parse_expression() {
    return nullptr;
}

std::unique_ptr<ResourceMap> Parser::parse_resource_map() {
    return nullptr;
}

std::unique_ptr<ReferenceList> Parser::parse_reference_list() {
    return nullptr;
}

}
