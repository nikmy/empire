#pragma once

#include "include_list.hpp"

#include <iostream>
#include <unordered_map>

namespace ast::visit
{

class EvalVisitor : public IVisitor {
 private:
    decltype(auto) getOperands(tree::BinaryOpExpr* expr);

 public:
    EvalVisitor() = default;

    void Visit(tree::Program* program) override;

    void Visit(tree::MainFunc* main_func) override;

    void Visit(tree::IntExpr* int_expr) override;

    void Visit(tree::BoolExpr* bool_expr) override;

    void Visit(tree::IdentExpr* ident_expr) override;

    void Visit(tree::AddExpr* add_expr) override;

    void Visit(tree::SubExpr* sub_expr) override;

    void Visit(tree::MulExpr* mul_expr) override;

    void Visit(tree::DivExpr* div_expr) override;

    void Visit(tree::ModExpr* mod_expr) override;

    void Visit(tree::AndExpr* and_expr) override;

    void Visit(tree::OrExpr* or_expr) override;

    void Visit(tree::NotExpr* not_expr) override;

    void Visit(tree::GreaterEqExpr* greater_equal_expr) override;

    void Visit(tree::GreaterExpr* greater_expr) override;

    void Visit(tree::LessEqExpr* less_equal_expr) override;

    void Visit(tree::LessExpr* less_expr) override;

    void Visit(tree::EqExpr* equal_expr) override;

    void Visit(tree::StatementList* stmt_list) override;

    void Visit(tree::AssignStmt* assignment_stmt) override;

    void Visit(tree::IfStmt* if_stmt) override;

    void Visit(tree::IfElseStmt* if_else_stmt) override;

    void Visit(tree::PrintStmt* print_stmt) override;

    void Visit(tree::ExpressionList* expr_list) override;

    void Visit(tree::VarDeclStmt* var_decl_stmt) override;

    void Visit(tree::WhileStmt* while_stmt) override;

    void Visit(tree::LValue* lvalue) override {
    }

    void Visit(tree::Reference* reference) override;

    void Visit(tree::Type* type) override {
    }

    void Visit(tree::BasicType* basic_type) override {
    }

    void Visit(tree::VarDecl* var_decl) override;
    void Visit(tree::FuncCall* func_call) override;
    void Visit(tree::FuncCallStmt* func_call_stmt) override;
    void Visit(tree::DeclarationList* decl_list) override;
    void Visit(tree::FuncDecl* func_decl) override;
    void Visit(tree::FormalArg* arg) override;
    void Visit(tree::FormalArgList* arg_list) override;

 private:
    std::unordered_map<std::string, runtime::Object> symbols_;
    std::string last_id_;
    runtime::Object tos_value_;
};

}