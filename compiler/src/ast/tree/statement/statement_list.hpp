#pragma once

#include "node.hpp"
#include "statement.hpp"

namespace ast::tree
{

class StatementList : public INode {
 public:
    StatementList() = default;

    StatementList(Statement* head, StatementList* tail) : head_(head), tail_(tail) {}

    Statement* GetHead() {
        return head_;
    }

    StatementList* GetTail() {
        return tail_;
    }

    void Visit(IVisitor& v) override {
        v.Visit(this);
    }

 private:
    Statement* head_{nullptr};
    StatementList* tail_{nullptr};
};

}