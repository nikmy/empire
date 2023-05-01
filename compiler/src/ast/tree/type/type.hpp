#pragma once

#include "node.hpp"

#include "visitor.hpp"

#include <string>

namespace ast::tree {

class Type : public INode {
 public:
    Type() = default;
    explicit Type(std::string identifier) = delete;

    virtual bool IsLiteral() const = 0;

    const std::string& GetIdentifier() const {
        return identifier_;
    }

 protected:
    std::string identifier_;
};

}