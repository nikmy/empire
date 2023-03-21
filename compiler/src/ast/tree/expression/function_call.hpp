#pragma once

#include "expression.hpp"

#include <string>

namespace ast::tree
{

class FuncCall : public Expression {
 public:
    FuncCall(std::string func_name, ExpressionList* expr_list)
        : func_name_(std::move(func_name)), args_(expr_list) {}

    const std::string& GetFuncName() const {
        return func_name_;
    }

    ExpressionList* GetArguments() {
        return args_;
    }

    void Visit(IVisitor& v) override {
        v.Visit(this);
    }

 private:
    std::string func_name_;
    ExpressionList* args_;
};

}