#pragma once

#include "forward_decl.hpp"

namespace ast
{

class INode {
 public:
    virtual void Visit(IVisitor& v) = 0;
};

}