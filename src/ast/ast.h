#pragma once

#include <memory>
#include <vector>
#include <string>
#include <map>

namespace lex {

class ASTNode {
public:
    virtual ~ASTNode() = default;
    std::string location;
};

class ASTVisitor {
public:
    virtual ~ASTVisitor() = default;
};

class Definition : public ASTNode {
public:
    std::string identifier;
};

class Expression : public ASTNode {
public:
    enum class Type { INTEGER, FLOAT, STRING, BOOLEAN, COLOR, NULL_VAL, REFERENCE };
    Type inferred_type = Type::NULL_VAL;
};

class Property : public ASTNode {
public:
    std::string name;
    std::unique_ptr<Expression> value;
};

class ResourceMap : public ASTNode {
public:
    std::map<std::string, double> resources;
};

class ReferenceList : public ASTNode {
public:
    std::vector<std::string> references;
};

class StructureDefinition : public Definition {
public:
    std::string era_ref;
    std::string name;
    std::string description;
    std::unique_ptr<ResourceMap> cost;
    std::unique_ptr<ResourceMap> production;
    std::unique_ptr<ResourceMap> maintenance;
};

class UnitDefinition : public Definition {
public:
    std::string era_ref;
    std::string type;
    std::unique_ptr<ResourceMap> cost;
};

class TechnologyDefinition : public Definition {
public:
    std::string era_ref;
    double research_cost = 0;
};

class EraDefinition : public Definition {
public:
    std::string name;
    std::string period;
};

class ChoiceDefinition : public Definition {
public:
    std::string era_ref;
    std::string text;
};

class EndingDefinition : public Definition {
public:
    std::string type;
    std::string text;
};

}
