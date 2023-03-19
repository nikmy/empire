#pragma once

#include "statement_list.hpp"
#include "expression.hpp"

namespace ast::tree
{

class IfElseStmt : public Statement {
 public:
    IfElseStmt(Expression* condition, StatementList* if_stmts, StatementList* else_stmts) :
        condition_(condition), if_stmts_(if_stmts), else_stmts_(else_stmts) {}

    Expression* GetCondition() {
        return condition_;
    }

    void SetCondition(Expression* condition) {
        condition_ = condition;
    }

    StatementList* GetIfStatements() {
        return if_stmts_;
    }

    void SetIfStatements(StatementList* if_stmts) {
        if_stmts_ = if_stmts;
    }

    StatementList* GetElseStatements() {
        return else_stmts_;
    }

    void SetElseStatements(StatementList* else_stmts) {
        else_stmts_ = else_stmts;
    }

    void Visit(IVisitor& v) override {
        v.Visit(this);
    }

 private:
    Expression* condition_;
    StatementList* if_stmts_;
    StatementList* else_stmts_;
};

}