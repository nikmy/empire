#pragma once

#include "declaration.hpp"
#include "visitor.hpp"

#include <string>
#include <utility>

namespace ast::tree
{

class VarDecl : public Declaration {
 public:
    VarDecl(Type* type, std::string identifier) : type_(type), var_name_(std::move(identifier)) {}

    void Visit(IVisitor& v) override {
        v.Visit(this);
    }

    Type* GetType() {
        return type_;
    }

    void SetType(Type* type) {
        type_ = type;
    }

    const std::string& GetVariableName() const {
        return var_name_;
    }

    void SetVariableName(const std::string& variable_name) {
        var_name_ = variable_name;
    }

 private:
    Type* type_;
    std::string var_name_;
};

}