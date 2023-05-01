#pragma once

#include "binary_op.hpp"

namespace ast::tree
{

class LessExpr : public BinaryOpExpr {
 public:
    LessExpr(Expression* left, Expression* right) : BinaryOpExpr(left, right) {}

    void Visit(IVisitor& v) override {
        v.Visit(this);
    }
};

}