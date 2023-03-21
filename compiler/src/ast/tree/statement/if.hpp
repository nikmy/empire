#pragma once

#include "statement_list.hpp"
#include "expression.hpp"

namespace ast::tree
{

class IfStmt : public Statement {
 public:
    IfStmt(Expression* expression, StatementList* stmts) : condition_(expression), stmts_(stmts) {}

    Expression* GetCondition() const {
        return condition_;
    }

    void SetCondition(Expression* condition) {
        condition_ = condition;
    }

    StatementList* GetStatements() const {
        return stmts_;
    }

    void SetStatements(StatementList* statements) {
        stmts_ = statements;
    }

    void Visit(IVisitor& v) override {
        v.Visit(this);
    }

 private:
    Expression* condition_;
    StatementList* stmts_;
};

}