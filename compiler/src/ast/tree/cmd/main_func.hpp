#pragma once

#include "statement_list.hpp"

#include "visitor.hpp"

#include <string>

namespace ast::tree
{

class MainFunc : public INode {
 public:
    explicit MainFunc(StatementList* statement_list)
        : statement_list_(statement_list) {}

    StatementList* GetStatementList() {
        return statement_list_;
    }

    void Visit(IVisitor& v) override {
        v.Visit(this);
    }

 private:
    StatementList* statement_list_{nullptr};
};

}