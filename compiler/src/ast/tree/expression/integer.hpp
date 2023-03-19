#pragma once

#include "expression.hpp"

namespace ast::tree
{

class IntExpr : public Expression {
 public:
    explicit IntExpr(const int value) : value_(value) {}

    int GetValue() const {
        return value_;
    }

    void Visit(IVisitor& v) override {
        v.Visit(this);
    }

 private:
    int value_{0};
};

}