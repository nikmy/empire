#pragma once

#include "expression.hpp"

namespace ast::tree
{

class BoolExpr : public Expression {
 public:
    explicit BoolExpr(const bool& value) : value_(value) {}

    bool GetValue() {
        return value_;
    }

    void Visit(IVisitor& v) override {
        v.Visit(this);
    }

 private:
    bool value_{false};
};

}