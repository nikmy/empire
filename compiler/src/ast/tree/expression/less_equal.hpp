#pragma once

#include "binary_op.hpp"

namespace ast::tree
{

class LessEqExpr : public BinaryOpExpr {
 public:
    LessEqExpr(Expression* left, Expression* right) : BinaryOpExpr(left, right) {}

    void Visit(IVisitor& v) override {
        v.Visit(this);
    }
};

}