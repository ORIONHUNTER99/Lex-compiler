#pragma once

#include "codegen/backend.hpp"
#include <memory>

namespace lex {

class UnrealBackend : public Backend {
public:
    std::string name() const override;
    std::string file_extension() const override;
    std::string generate(const std::vector<std::unique_ptr<Definition>>& ast) override;
};

} // namespace lex
