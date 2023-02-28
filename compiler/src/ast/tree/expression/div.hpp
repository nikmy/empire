#pragma once

#include "binary_op.hpp"

namespace ast::tree
{

class DivExpr : public BinaryOpExpr {
 public:
    DivExpr(Expression* left, Expression* right) : BinaryOpExpr(left, right) {}

    void Visit(IVisitor& v) override {
        v.Visit(this);
    }
};

}