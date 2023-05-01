#pragma once

#include "statement.hpp"
#include "var_decl.hpp"

namespace ast::tree
{

class VarDeclStmt : public Statement {
 public:
    explicit VarDeclStmt(VarDecl* var_decl) : var_decl_(var_decl) {}

    VarDecl* GetVariableDeclaration() {
        return var_decl_;
    }

    void SetVariableDeclaration(VarDecl* variable_declaration) {
        var_decl_ = variable_declaration;
    }

    void Visit(IVisitor& v) override {
        v.Visit(this);
    }

 private:
    VarDecl* var_decl_;
};

}