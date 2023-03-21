#pragma once

#include "expression.hpp"

namespace ast::tree
{

class NotExpr : public Expression {
 public:
    explicit NotExpr(Expression* expression) : expression_(expression) {}

    Expression* GetExpression() {
        return expression_;
    }

    void Visit(IVisitor& v) override {
        v.Visit(this);
    }

 private:
    Expression* expression_{nullptr};
};

}