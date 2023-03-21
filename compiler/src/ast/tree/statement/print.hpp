#pragma once

#include "statement.hpp"
#include "expression.hpp"

namespace ast::tree
{

class PrintStmt : public Statement {
 public:
    explicit PrintStmt(ExpressionList* exprs) : exprs_(exprs) {}

    ExpressionList* GetExpressions() {
        return exprs_;
    }

    void SetExpression(ExpressionList* expressions) {
        exprs_ = expressions;
    }

    void Visit(IVisitor& v) override {
        v.Visit(this);
    }

 private:
    ExpressionList* exprs_;
};

}