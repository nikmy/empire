#pragma once

#include "node.hpp"

namespace ast::tree
{

class DeclarationList : public INode {
 public:
    DeclarationList(Declaration* head, DeclarationList* tail) : head_(head), tail_(tail) {}

    Declaration* GetHead() {
        return head_;
    }

    DeclarationList* GetTail() {
        return tail_;
    }

    void Visit(IVisitor& v) override {
        v.Visit(this);
    }

 private:
    Declaration* head_;
    DeclarationList* tail_;
};

}