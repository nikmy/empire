#pragma once

#include "expression.hpp"

namespace ast::tree
{

class BinaryOpExpr : public Expression {
 public:
    void Visit(IVisitor& v) override {
        Expression::Visit(v);
        left_->Visit(v);
        right_->Visit(v);
    }

    Expression* GetLeftExpression() {
        return left_;
    }

    Expression* GetRightExpression() {
        return right_;
    }

    void SetLeftExpression(Expression* left) {
        left_ = left;
    }

    void SetRightExpression(Expression* right) {
        right_ = right;
    }

 protected:
    BinaryOpExpr(Expression* left, Expression* right) : left_(left), right_(right) {}

 protected:
    Expression* left_{nullptr};
    Expression* right_{nullptr};
};

}