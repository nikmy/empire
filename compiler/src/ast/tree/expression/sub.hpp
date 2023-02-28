#pragma once

#include "binary_op.hpp"

namespace ast::tree
{

class SubExpr : public BinaryOpExpr {
 public:
    SubExpr(Expression* left, Expression* right) : BinaryOpExpr(left, right) {}

    void Visit(IVisitor& v) override {
        v.Visit(this);
    }
};

}