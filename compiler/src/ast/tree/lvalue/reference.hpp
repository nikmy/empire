#pragma once

#include "lvalue.hpp"

#include <string>

namespace ast::tree {

class Reference : public LValue {
 public:
    explicit Reference(std::string name) : name_(std::move(name)) {}

    const std::string& GetName() const override {
        return name_;
    }

    bool IsVariable() const override {
        return true;
    }

    void Visit(IVisitor& v) override {
        v.Visit(this);
    }

 private:
    std::string name_;
};

}