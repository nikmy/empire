#pragma once

#include "node.hpp"

#include "visitor.hpp"

#include "main_func.hpp"

namespace ast::tree {

class Program : public INode {
 public:
    explicit Program(MainFunc* main_func)
        : main_func_(main_func) {}

    void Visit(IVisitor& v) override {
        v.Visit(this);
    }

    MainFunc* GetMainFunc() {
        return main_func_;
    }

 private:
    MainFunc* main_func_;
};

} // namespace ast