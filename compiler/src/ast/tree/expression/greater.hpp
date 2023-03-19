#pragma once

#include "binary_op.hpp"

namespace ast::tree
{

class GreaterExpr : public BinaryOpExpr {
 public:
    GreaterExpr(Expression* left, Expression* right) : BinaryOpExpr(left, right) {}

    void Visit(IVisitor& v) override {
        v.Visit(this);
    }
};

}