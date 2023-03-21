#pragma once

#include "node.hpp"

namespace ast::tree
{

class ExpressionList : public INode {
 public:
    ExpressionList() = default;

    ExpressionList(Expression* first_item, ExpressionList* tail)
        : head_(first_item), tail_(tail) {}

    Expression* GetHead() {
        return head_;
    }

    void SetHead(Expression* head) {
        head_ = head;
    }

    ExpressionList* GetTail() {
        return tail_;
    }

    void SetTail(ExpressionList* tail) {
        tail_ = tail;
    }

    void Visit(IVisitor& v) override {
        v.Visit(this);
    }

 private:
    Expression* head_{nullptr};
    ExpressionList* tail_{nullptr};
};

}