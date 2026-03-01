#pragma once

#include "backend.h"

namespace lex {

class LuaBackend : public Backend {
public:
    std::string name() const override { return "lua"; }
    std::string file_extension() const override { return ".lua"; }

    std::string generate(const std::vector<std::unique_ptr<Definition>>& ast) override;

private:
    std::string generate_structure(const StructureDefinition& structure);
    std::string generate_resource_map(const ResourceMap& map);
    std::string generate_header();
};

}
