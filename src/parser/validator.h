#pragma once

#include <string>
#include <vector>
#include <memory>
#include "../ast/ast.h"

namespace lex {

class SemanticError {
public:
    std::string code;
    std::string message;
    std::string location;
};

class Validator {
public:
    bool validate(const std::vector<std::unique_ptr<Definition>>& definitions);

    const std::vector<SemanticError>& errors() const { return errors_; }
    bool has_errors() const { return !errors_.empty(); }

private:
    std::vector<SemanticError> errors_;
    std::map<std::string, std::string> symbol_table_;

    void register_symbols(const std::vector<std::unique_ptr<Definition>>& definitions);
    void validate_references(const std::vector<std::unique_ptr<Definition>>& definitions);
    void validate_required_properties(const std::vector<std::unique_ptr<Definition>>& definitions);
};

}
