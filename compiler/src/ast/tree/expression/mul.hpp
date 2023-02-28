#pragma once

#include "binary_op.hpp"

namespace ast::tree
{

class MulExpr : public BinaryOpExpr {
 public:
    MulExpr(Expression* left, Expression* right) : BinaryOpExpr(left, right) {}

    void Visit(IVisitor& v) override {
        v.Visit(this);
    }
};

}