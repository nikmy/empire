#include "printer.hpp"

namespace ast::visit
{

void PrintVisitor::visitBinaryOp(const char* op, tree::BinaryOpExpr* expr) {
    makeIndent();
    out_ << op << ":\n";
    ++indent_;

    auto was_in_list = in_list_;
    in_list_ = false;

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

    in_list_ = was_in_list;
}

void PrintVisitor::makeIndent() {
    out_ << std::string(indent_, '\t');
    if (in_list_) {
        out_ << "- ";
    }
}

PrintVisitor::~PrintVisitor() {
    out_.close();
}

void PrintVisitor::Visit(tree::Program* program) {
    program->GetMainFunc()->Visit(*this);
}

void PrintVisitor::Visit(tree::MainFunc* main_func) {
    out_ << "- io_func_def(main):\n";
    ++indent_;
    main_func->GetStatementList()->Visit(*this);
    --indent_;
}

void PrintVisitor::Visit(tree::StatementList* stmt_list) {
    in_list_ = true;
    while (stmt_list != nullptr && stmt_list->GetHead() != nullptr) {
        stmt_list->GetHead()->Visit(*this);
        stmt_list = stmt_list->GetTail();
    }
    in_list_ = false;
}

void PrintVisitor::Visit(tree::AssignStmt* assignment_stmt) {
    makeIndent();
    out_ << "assignment:\n";
    ++indent_;

    auto was_in_list = in_list_;
    in_list_ = false;

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

    in_list_ = was_in_list;
}

void PrintVisitor::Visit(tree::IfStmt* if_stmt) {
    makeIndent();
    out_ << "if:\n";
    ++indent_;

    auto was_in_list = in_list_;
    in_list_ = false;

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

    in_list_ = was_in_list;
}

void PrintVisitor::Visit(tree::IfElseStmt* if_else_stmt) {
    makeIndent();
    out_ << "if:\n";
    ++indent_;

    auto was_in_list = in_list_;
    in_list_ = false;

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

    in_list_ = was_in_list;
}

void PrintVisitor::Visit(tree::PrintStmt* print_stmt) {
    makeIndent();
    out_ << "print:\n";
    ++indent_;
    print_stmt->GetExpressions()->Visit(*this);
    --indent_;
}

void PrintVisitor::Visit(tree::VarDeclStmt* var_decl_stmt) {
    var_decl_stmt->GetVariableDeclaration()->Visit(*this);
}

void PrintVisitor::Visit(tree::VarDecl* var_decl) {
    makeIndent();
    out_ << "variable declaration:\n";
    ++indent_;

    auto was_in_list = in_list_;
    in_list_ = false;

    makeIndent();
    out_ << "id: " << var_decl->GetVariableName() << "\n";
    makeIndent();
    out_ << "type:\n";
    ++indent_;
    var_decl->GetType()->Visit(*this);
    indent_ -= 2;

    in_list_ = was_in_list;
}

void PrintVisitor::Visit(tree::WhileStmt* while_stmt) {
    makeIndent();
    out_ << "while loop:\n";
    ++indent_;

    auto was_in_list = in_list_;
    in_list_ = false;

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

    in_list_ = was_in_list;
}

void PrintVisitor::Visit(tree::ExpressionList* expr_list) {
    in_list_ = true;
    while (expr_list != nullptr && expr_list->GetHead() != nullptr) {
        expr_list->GetHead()->Visit(*this);
        expr_list = expr_list->GetTail();
    }
    in_list_ = false;
}

void PrintVisitor::Visit(tree::IntExpr* int_expr) {
    makeIndent();
    out_ << "int(" + std::to_string(int_expr->GetValue()) + ")\n";
}

void PrintVisitor::Visit(tree::BoolExpr* bool_expr) {
    std::string val = bool_expr->GetValue() ? "true" : "false";
    makeIndent();
    out_ << "bool(" + val + ")\n";
}

void PrintVisitor::Visit(tree::IdentExpr* ident_expr) {
    makeIndent();
    out_ << "var(" << ident_expr->GetIdentifier() << ")\n";
}

void PrintVisitor::Visit(tree::AddExpr* add_expr) {
    visitBinaryOp("(+)", add_expr);
}

void PrintVisitor::Visit(tree::SubExpr* sub_expr) {
    visitBinaryOp("(-)", sub_expr);
}

void PrintVisitor::Visit(tree::MulExpr* mul_expr) {
    visitBinaryOp("(*)", mul_expr);
}

void PrintVisitor::Visit(tree::DivExpr* div_expr) {
    visitBinaryOp("div", div_expr);
}

void PrintVisitor::Visit(tree::ModExpr* mod_expr) {
    visitBinaryOp("mod", mod_expr);
}

void PrintVisitor::Visit(tree::AndExpr* and_expr) {
    visitBinaryOp("and", and_expr);
}

void PrintVisitor::Visit(tree::NotExpr* not_expr) {
    makeIndent();
    out_ << "not:\n";
    ++indent_;
    not_expr->GetExpression()->Visit(*this);
    --indent_;
}

void PrintVisitor::Visit(tree::OrExpr* or_expr) {
    visitBinaryOp("or", or_expr);
}

void PrintVisitor::Visit(tree::GreaterEqExpr* greater_equal_expr) {
    visitBinaryOp("(>=)", greater_equal_expr);
}

void PrintVisitor::Visit(tree::GreaterExpr* greater_expr) {
    visitBinaryOp("(>)", greater_expr);
}

void PrintVisitor::Visit(tree::LessEqExpr* less_equal_expr) {
    visitBinaryOp("(<=)", less_equal_expr);
}

void PrintVisitor::Visit(tree::LessExpr* less_expr) {
    visitBinaryOp("(<)", less_expr);
}

void PrintVisitor::Visit(tree::EqExpr* equal_expr) {
    visitBinaryOp("(==)", equal_expr);
}

void PrintVisitor::Visit(tree::Reference* reference) {
    makeIndent();
    out_ << "var(" << reference->GetName() << ")\n";
}

void PrintVisitor::Visit(tree::BasicType* basic_type) {
    makeIndent();
    out_ << basic_type->GetIdentifier() << '\n';
}

}