#pragma once

#include "node.hpp"

#include <string>

namespace ast::tree
{

class FormalArg : public INode {
 public:
    FormalArg(Type* type, std::string name) : type_(type), name_(std::move(name)) {}

    Type* GetType() {
        return type_;
    }

    const std::string& GetVariableName() const {
        return name_;
    }

    void Visit(IVisitor& v) override {
        v.Visit(this);
    }

 private:
    Type* type_;
    std::string name_;
};

}