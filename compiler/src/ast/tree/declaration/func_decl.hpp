#pragma once

#include "declaration.hpp"

#include <string>
#include <utility>

namespace ast::tree
{

class FuncDecl : public Declaration {
 public:
    FuncDecl(
        bool has_side_effects,
        std::string  name,
        FormalArgList* args,
        Type* return_type,
        StatementList* stmt_list
    ) : return_type_(return_type),
        args_(args),
        body_(stmt_list),
        name_(std::move(name)),
        can_io_(has_side_effects)
    {}

    void Visit(IVisitor& v) override {
        v.Visit(this);
    }

    Type* GetReturnType() const {
        return return_type_;
    }

    FormalArgList* GetArgs() const {
        return args_;
    }

    StatementList* GetBody() const {
        return body_;
    }

    const std::string& GetName() const {
        return name_;
    }

    bool CanIO() const {
        return can_io_;
    }

 private:
    Type* return_type_;

 private:
    FormalArgList* args_;
    StatementList* body_;
    std::string name_;
    bool can_io_;
};

}