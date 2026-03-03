#pragma once

#include "backend.h"
#include <set>

namespace lex {

class GodotBackend : public Backend {
public:
    std::string name() const override { return "gd"; }
    std::string file_extension() const override { return ".gd"; }

    std::string generate(const std::vector<std::unique_ptr<Definition>>& ast) override;

private:
    std::set<std::string> seen_types_;

    std::string type_to_var_name(const std::string& type) const;

    std::string generate_definition(const Definition& def);
    std::string generate_property_value(const Property& prop);
    std::string generate_resource_map(const ResourceMap& map);
    std::string generate_reference_list(const ReferenceList& list);
    std::string generate_expression(const Expression* expr);

    std::string escape_string(const std::string& s) const;
};

}
