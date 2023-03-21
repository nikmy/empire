#pragma once

#include "expression.hpp"

#include <string>

namespace ast::tree
{

class IdentExpr : public Expression {
 public:
    explicit IdentExpr(std::string identifier) : identifier_(std::move(identifier)) {}

    const std::string& GetIdentifier() const {
        return identifier_;
    }

    void Visit(IVisitor& v) override {
        v.Visit(this);
    }

 private:
    std::string identifier_;
};

}