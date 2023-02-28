#pragma once

#include "include_list.hpp"

namespace ast::visit
{

class PrintVisitor : public IVisitor {
 private:
    std::ofstream out_;
    int indent_;

    void visitBinaryOp(const char* op, tree::BinaryOpExpr* expr) {
        makeIndent();
        out_ << op << ":\n";
        ++indent_;

        makeIndent();
        out_ << "left:\n";
        ++indent_;
        expr->GetLeftExpression()->Visit(*this);
        --indent_;

        makeIndent();
        out_ << "right:\n";
        ++indent_;
        expr->GetRightExpression()->Visit(*this);
        indent_ -= 2;
    }

 private:

    void makeIndent() {
        out_ << std::string(indent_, '\t');
    }

 public:
    explicit PrintVisitor(const std::string& filename) : out_(filename), indent_(0) {}

    ~PrintVisitor() {
        out_.close();
    }

    void Visit(tree::Program* program) override {
        program->GetMainFunc()->Visit(*this);
    }

    void Visit(tree::MainFunc* main_func) override {
        out_ << "__main__:\n";
        ++indent_;
        main_func->GetStatementList()->Visit(*this);
        --indent_;
    }

    void Visit(tree::StatementList* stmt_list) override {
        while (stmt_list != nullptr && stmt_list->GetHead() != nullptr) {
            stmt_list->GetHead()->Visit(*this);
            stmt_list = stmt_list->GetTail();
        }
    }

    void Visit(tree::AssignStmt* assignment_stmt) override {
        makeIndent();
        out_ << "assignment:\n";
        ++indent_;

        makeIndent();
        out_ << "lvalue:\n";
        ++indent_;
        if (assignment_stmt->GetLValue()->IsVariable()) {
            assignment_stmt->GetLValue()->Visit(*this);
        }
        --indent_;

        makeIndent();
        out_ << "rvalue:\n";
        ++indent_;
        assignment_stmt->GetRValue()->Visit(*this);
        indent_ -= 2;
    }

    void Visit(tree::IfStmt* if_stmt) override {
        makeIndent();
        out_ << "if:\n";
        ++indent_;

        makeIndent();
        out_ << "condition:\n";
        ++indent_;
        if_stmt->GetCondition()->Visit(*this);
        --indent_;

        makeIndent();
        out_ << "statements:\n";
        ++indent_;
        if_stmt->GetStatements()->Visit(*this);
        indent_ -= 2;
    }

    void Visit(tree::IfElseStmt* if_else_stmt) override {
        makeIndent();
        out_ << "if:\n";
        ++indent_;

        makeIndent();
        out_ << "condition:\n";
        ++indent_;
        if_else_stmt->GetCondition()->Visit(*this);
        --indent_;

        makeIndent();
        out_ << "if true statements:\n";
        ++indent_;
        if_else_stmt->GetIfStatements()->Visit(*this);
        --indent_;

        makeIndent();
        out_ << "otherwise statements:\n";
        ++indent_;
        if_else_stmt->GetElseStatements()->Visit(*this);
        indent_ -= 2;
    }

    void Visit(tree::PrintStmt* print_stmt) override {
        makeIndent();
        out_ << "print:\n";
        ++indent_;
        print_stmt->GetExpressions()->Visit(*this);
        --indent_;
    }

    void Visit(tree::VarDeclStmt* var_decl_stmt) override {
        var_decl_stmt->GetVariableDeclaration()->Visit(*this);
    }

    void Visit(tree::VarDecl* var_decl) override {
        makeIndent();
        out_ << "variable declaration:\n";
        ++indent_;
        makeIndent();
        out_ << "id: " << var_decl->GetVariableName() << "\n";
        makeIndent();
        out_ << "type:\n";
        ++indent_;
        var_decl->GetType()->Visit(*this);
        indent_ -= 2;
    }

    void Visit(tree::WhileStmt* while_stmt) override {
        makeIndent();
        out_ << "while loop:\n";
        ++indent_;

        makeIndent();
        out_ << "condition:\n";
        ++indent_;
        while_stmt->GetCondition()->Visit(*this);
        --indent_;

        makeIndent();
        out_ << "statements:\n";
        ++indent_;
        while_stmt->GetStatements()->Visit(*this);
        indent_ -= 2;
    }

    void Visit(tree::ExpressionList* expr_list) override {
        while (expr_list != nullptr && expr_list->GetHead() != nullptr) {
            expr_list->GetHead()->Visit(*this);
            expr_list = expr_list->GetTail();
        }
    }

    void Visit(tree::IntExpr* int_expr) override {
        makeIndent();
        out_ << "int(" + std::to_string(int_expr->GetValue()) + ")\n";
    }

    void Visit(tree::BoolExpr* bool_expr) override {
        std::string val = bool_expr->GetValue() ? "true" : "false";
        makeIndent();
        out_ << "bool(" + val + ")\n";
    }

    void Visit(tree::IdentExpr* ident_expr) override {
        makeIndent();
        out_ << "var(" << ident_expr->GetIdentifier() << ")\n";
    }

    void Visit(tree::AddExpr* add_expr) override {
        visitBinaryOp("(+)", add_expr);
    }

    void Visit(tree::SubExpr* sub_expr) override {
        visitBinaryOp("(-)", sub_expr);
    }

    void Visit(tree::MulExpr* mul_expr) override {
        visitBinaryOp("(*)", mul_expr);
    }

    void Visit(tree::DivExpr* div_expr) override {
        visitBinaryOp("div", div_expr);
    }

    void Visit(tree::ModExpr* mod_expr) override {
        visitBinaryOp("mod", mod_expr);
    }

    void Visit(tree::AndExpr* and_expr) override {
        visitBinaryOp("and", and_expr);
    }

    void Visit(tree::NotExpr* not_expr) override {
        makeIndent();
        out_ << "not:\n";
        ++indent_;
        not_expr->GetExpression()->Visit(*this);
        --indent_;
    }

    void Visit(tree::OrExpr* or_expr) override {
        visitBinaryOp("or", or_expr);
    }

    void Visit(tree::GreaterEqExpr* greater_equal_expr) override {
        visitBinaryOp("(>=)", greater_equal_expr);
    }

    void Visit(tree::GreaterExpr* greater_expr) override {
        visitBinaryOp("(>)", greater_expr);
    }

    void Visit(tree::LessEqExpr* less_equal_expr) override {
        visitBinaryOp("(<=)", less_equal_expr);
    }

    void Visit(tree::LessExpr* less_expr) override {
        visitBinaryOp("(<)", less_expr);
    }

    void Visit(tree::EqExpr* equal_expr) override {
        visitBinaryOp("(==)", equal_expr);
    }


    void Visit(tree::LValue* lvalue) override {
    }

    void Visit(tree::Reference* reference) override {
        makeIndent();
        out_ << "var(" << reference->GetName() << ")\n";
    }

    void Visit(tree::Type* type) override {
    }

    void Visit(tree::BasicType* basic_type) override {
        makeIndent();
        out_ << basic_type->GetIdentifier() << '\n';
    }
};

}