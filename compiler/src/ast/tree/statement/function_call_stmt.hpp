#pragma once

#include "statement.hpp"

namespace ast::tree
{

class FuncCallStmt : public Statement {
 public:
    explicit FuncCallStmt(FuncCall* func_call) : func_call_(func_call) {}

    FuncCall* GetFuncCall() {
        return func_call_;
    }

    void Visit(IVisitor& v) override {
        v.Visit(this);
    }

 private:
    FuncCall* func_call_;
};

}