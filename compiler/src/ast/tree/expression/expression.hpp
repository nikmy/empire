#pragma once

#include "node.hpp"

#include "visitor.hpp"

namespace ast::tree
{

class Expression : public INode {
 public:
    virtual void Visit(IVisitor& v) {

    }
};

}