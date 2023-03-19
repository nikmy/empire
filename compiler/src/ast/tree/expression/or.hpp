#pragma once

#include "binary_op.hpp"

namespace ast::tree
{

class OrExpr : public BinaryOpExpr {
 public:
    OrExpr(Expression* left, Expression* right) : BinaryOpExpr(left, right) {}

    void Visit(IVisitor& v) override {
        v.Visit(this);
    }
};

}