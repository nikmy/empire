#pragma once

#include "expression.hpp"
#include "statement.hpp"
#include "lvalue.hpp"

namespace ast::tree
{

class AssignStmt : public Statement {
 public:
    AssignStmt(LValue* lvalue, Expression* rvalue) : lvalue_(lvalue), rvalue_(rvalue) {}

    LValue* GetLValue() {
        return lvalue_;
    }

    void SetLValue(LValue* lvalue) {
        lvalue_ = lvalue;
    }

    Expression* GetRValue() {
        return rvalue_;
    }

    void SetRValue(Expression* expression) {
        rvalue_ = expression;
    }

    void Visit(IVisitor& v) override {
        v.Visit(this);
    }

 private:
    LValue* lvalue_;
    Expression* rvalue_;
};

}