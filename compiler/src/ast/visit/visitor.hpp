#pragma once

#include "forward_decl.hpp"

namespace ast
{

class IVisitor {
 public:
    virtual void Visit(tree::Program* program) = 0;
    virtual void Visit(tree::MainFunc* main_func) = 0;

    virtual void Visit(tree::ExpressionList* expr_list) = 0;

    virtual void Visit(tree::IntExpr* int_expr) = 0;
    virtual void Visit(tree::BoolExpr* bool_expr) = 0;
    virtual void Visit(tree::IdentExpr* ident_expr) = 0;
    virtual void Visit(tree::FuncCall* func_call) = 0;

    virtual void Visit(tree::AddExpr* add_expr) = 0;
    virtual void Visit(tree::SubExpr* sub_expr) = 0;
    virtual void Visit(tree::MulExpr* mul_expr) = 0;
    virtual void Visit(tree::DivExpr* div_expr) = 0;
    virtual void Visit(tree::ModExpr* mod_expr) = 0;

    virtual void Visit(tree::AndExpr* and_expr) = 0;
    virtual void Visit(tree::NotExpr* not_expr) = 0;
    virtual void Visit(tree::OrExpr* or_expr) = 0;

    virtual void Visit(tree::GreaterEqExpr* greater_equal_expr) = 0;
    virtual void Visit(tree::GreaterExpr* greater_expr) = 0;
    virtual void Visit(tree::LessEqExpr* less_equal_expr) = 0;
    virtual void Visit(tree::LessExpr* less_expr) = 0;
    virtual void Visit(tree::EqExpr* equal_expr) = 0;

    virtual void Visit(tree::StatementList* stmt_list) = 0;
    virtual void Visit(tree::AssignStmt* assignment_stmt) = 0;
    virtual void Visit(tree::IfStmt* if_stmt) = 0;
    virtual void Visit(tree::IfElseStmt* if_else_stmt) = 0;
    virtual void Visit(tree::PrintStmt* print_stmt) = 0;
    virtual void Visit(tree::VarDeclStmt* var_decl_stmt) = 0;
    virtual void Visit(tree::WhileStmt* while_stmt) = 0;
    virtual void Visit(tree::FuncCallStmt* func_call_stmt) = 0;

    virtual void Visit(tree::LValue* lvalue) = 0;
    virtual void Visit(tree::Reference* reference) = 0;

    virtual void Visit(tree::Type* type) = 0;
    virtual void Visit(tree::BasicType* basic_type) = 0;

    virtual void Visit(tree::DeclarationList* decl_list) = 0;

    virtual void Visit(tree::VarDecl* var_decl) = 0;
    virtual void Visit(tree::FuncDecl* func_decl) = 0;

    virtual void Visit(tree::FormalArg* arg) = 0;
    virtual void Visit(tree::FormalArgList* arg_list) = 0;
};

}