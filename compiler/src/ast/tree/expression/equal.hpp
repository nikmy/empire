#pragma once

#include "binary_op.hpp"

namespace ast::tree
{

class EqExpr : public BinaryOpExpr {
 public:
    EqExpr(Expression* left, Expression* right) : BinaryOpExpr(left, right) {}

    void Visit(IVisitor& v) override {
        v.Visit(this);
    }
};

}