#pragma once

#include "binary_op.hpp"

namespace ast::tree
{

class AndExpr : public BinaryOpExpr {
 public:
    AndExpr(Expression* left, Expression* right) : BinaryOpExpr(left, right) {}

    void Visit(IVisitor& v) override {
        v.Visit(this);
    }
};

}