#pragma once

#include "node.hpp"

#include "visitor.hpp"

namespace ast::tree
{

// Can be on the left side of assignment (lvalue)
class LValue : public INode {
 public:
    virtual const std::string& GetName() const = 0;
    virtual bool IsVariable() const = 0;
};

}