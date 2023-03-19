#pragma once

#include "binary_op.hpp"

namespace ast::tree
{

class ModExpr : public BinaryOpExpr {
 public:
    ModExpr(Expression* left, Expression* right) : BinaryOpExpr(left, right) {}

    void Visit(IVisitor& v) override {
        v.Visit(this);
    }
};

}