#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>
#include "../ast/ast.h"

namespace lex {

class Backend {
public:
    virtual ~Backend() = default;

    virtual std::string name() const = 0;
    virtual std::string file_extension() const = 0;
    virtual std::string generate(const std::vector<std::unique_ptr<Definition>>& ast) = 0;

protected:
    std::vector<std::string> errors_;
};

class BackendRegistry {
public:
    static BackendRegistry& instance();

    void register_backend(std::unique_ptr<Backend> backend);
    Backend* get_backend(const std::string& name);
    std::vector<std::string> available_backends() const;

private:
    std::map<std::string, std::unique_ptr<Backend>> backends_;
};

}
