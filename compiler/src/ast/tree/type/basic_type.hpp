#pragma once

#include "type.hpp"

namespace ast::tree {

class BasicType : public Type {
 public:
    explicit BasicType(const std::string& identifier) {
        this->identifier_ = identifier;
    }

    bool IsLiteral() const override {
        return true;
    }

    void Visit(IVisitor& v) override {
        v.Visit(this);
    }
};

}