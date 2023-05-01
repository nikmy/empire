#pragma once

#include "node.hpp"

namespace ast::tree
{

class FormalArgList : public INode {
 public:
    FormalArgList(FormalArg* head, FormalArgList* tail) : head_(head), tail_(tail) {}

    FormalArg* GetHead() {
        return head_;
    }

    FormalArgList* GetTail() {
        return tail_;
    }

    void Visit(IVisitor& v) override {
        v.Visit(this);
    }

 private:
    FormalArg* head_;
    FormalArgList* tail_;
};

}