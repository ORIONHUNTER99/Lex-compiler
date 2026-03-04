#pragma once

#include "backend.h"
#include <set>

namespace lex {

class DefoldBackend : public Backend {
public:
    std::string name() const override { return "defold"; }
    std::string file_extension() const override { return ".lua"; }

    std::string generate(const std::vector<std::unique_ptr<Definition>>& ast) override;

private:
    std::set<std::string> seen_types_;

    std::string generate_definition(const Definition& def);
    std::string generate_generic(const Definition& def);
    std::string generate_resource_map(const ResourceMap& map);
    std::string generate_reference_list(const ReferenceList& list);

    // Convert definition type to Defold table name (snake_case, plural)
    std::string type_to_table_name(const std::string& type) const;

    // Expression code generation
    std::string generate_expression(const Expression* expr, bool in_condition = false);
    std::string generate_binary_expression(const Expression* expr, bool in_condition = false);
    std::string generate_unary_expression(const Expression* expr, bool in_condition = false);
    std::string generate_call_expression(const Expression* expr, bool in_condition = false);
    std::string generate_member_expression(const Expression* expr, bool in_condition = false);

    // Condition code generation
    std::string generate_condition(const Condition* cond);

    // Helpers
    std::string get_string_property(const Definition& def, const std::string& name);
    int64_t get_int_property(const Definition& def, const std::string& name, int64_t default_val = 0);
    const ResourceMap* get_resource_map_property(const Definition& def, const std::string& name);

    // Operator mapping
    std::string binary_op_to_lua(Expression::BinaryOp op) const;
    std::string unary_op_to_lua(Expression::UnaryOp op) const;

    // Generate a property value as Lua
    std::string generate_property_value(const Property& prop);
};

}
