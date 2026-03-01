#pragma once

#include "backend.h"

namespace lex {

class LuaBackend : public Backend {
public:
    std::string name() const override { return "lua"; }
    std::string file_extension() const override { return ".lua"; }
    
    std::string generate(const std::vector<std::unique_ptr<Definition>>& ast) override;

private:
    std::string generate_structure(const Definition& structure);
    std::string generate_resource_map(const ResourceMap& map);
    
    // Helpers to extract values from generic properties
    std::string get_string_property(const Definition& def, const std::string& name);
    int64_t get_int_property(const Definition& def, const std::string& name, int64_t default_val = 0);
    const ResourceMap* get_resource_map_property(const Definition& def, const std::string& name);
};

}
