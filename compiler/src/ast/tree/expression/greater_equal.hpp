#pragma once

#include "binary_op.hpp"

namespace ast::tree
{

class GreaterEqExpr : public BinaryOpExpr {
 public:
    GreaterEqExpr(Expression* left, Expression* right) : BinaryOpExpr(left, right) {}

    void Visit(IVisitor& v) override {
        v.Visit(this);
    }
};

}