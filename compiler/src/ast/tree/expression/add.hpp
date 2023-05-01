#pragma once

#include "binary_op.hpp"

namespace ast::tree
{

class AddExpr : public BinaryOpExpr {
 public:
    AddExpr(Expression* left, Expression* right) : BinaryOpExpr(left, right) {}

    void Visit(IVisitor& v) override {
        v.Visit(this);
    }
};

}