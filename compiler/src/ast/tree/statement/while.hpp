#pragma once

#include "statement_list.hpp"
#include "expression.hpp"

namespace ast::tree
{

class WhileStmt : public Statement {
 public:
    WhileStmt(Expression* condition, StatementList* stmts) : cond_(condition), stmts_(stmts) {}

    Expression* GetCondition() {
        return cond_;
    }

    void SetCondition(Expression* expression) {
        cond_ = expression;
    }

    StatementList* GetStatements() {
        return stmts_;
    }

    void SetStatements(StatementList* stmts) {
        stmts_ = stmts;
    }

    void Visit(IVisitor& v) override {
        v.Visit(this);
    }

 private:
    Expression* cond_{nullptr};
    StatementList* stmts_{nullptr};
};

}