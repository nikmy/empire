#pragma once

#include "include_list.hpp"

#include <unordered_map>

namespace ast::visit
{

class EvalVisitor : public IVisitor {
 private:
    decltype(auto) getOperands(tree::BinaryOpExpr* expr) {
        expr->GetLeftExpression()->Visit(*this);
        auto left = tos_value_;
        expr->GetRightExpression()->Visit(*this);
        auto right = tos_value_;
        return std::make_pair(left, right);
    }

 public:
    EvalVisitor() = default;

    void Visit(tree::Program* program) override {
        program->GetMainFunc()->Visit(*this);
    }

    void Visit(tree::MainFunc* main_func) override {
        main_func->GetStatementList()->Visit(*this);
    }

    void Visit(tree::IntExpr* int_expr) override {
        auto intObj = runtime::Object(int_expr->GetValue());
        std::swap(tos_value_, intObj);
    }

    void Visit(tree::BoolExpr* bool_expr) override {
        auto boolObj = runtime::Object(bool_expr->GetValue());
        std::swap(tos_value_, boolObj);
    }

    void Visit(tree::IdentExpr* ident_expr) override {
        last_id_ = ident_expr->GetIdentifier();
        if (symbols_.contains(last_id_)) {
            tos_value_ = symbols_[last_id_];
        }
    }

    void Visit(tree::AddExpr* add_expr) override {
        auto[left, right] = getOperands(add_expr);
        if (left.GetType() != right.GetType() || !left.GetType().IsInt()) {
            throw std::runtime_error("(+): operands have incompatible types");
        }
        tos_value_ = runtime::Object(left.Int() + right.Int());
    }

    void Visit(tree::SubExpr* sub_expr) override {
        auto[left, right] = getOperands(sub_expr);
        if (left.GetType() != right.GetType() || !left.GetType().IsInt()) {
            throw std::runtime_error("(-): operands have incompatible types");
        }
        tos_value_ = runtime::Object(left.Int() - right.Int());
    }

    void Visit(tree::MulExpr* mul_expr) override {
        auto[left, right] = getOperands(mul_expr);
        if (left.GetType() != right.GetType() || !left.GetType().IsInt()) {
            throw std::runtime_error("(*): operands have incompatible types");
        }
        tos_value_ = runtime::Object(left.Int() * right.Int());
    }

    void Visit(tree::DivExpr* div_expr) override {
        auto[left, right] = getOperands(div_expr);
        if (left.GetType() != right.GetType() || !left.GetType().IsInt()) {
            throw std::runtime_error("div: operands have incompatible types");
        }
        if (right.Int() == 0) {
            throw std::runtime_error("division by zero");
        }
        tos_value_ = runtime::Object(left.Int() / right.Int());
    }

    void Visit(tree::ModExpr* mod_expr) override {
        auto[left, right] = getOperands(mod_expr);
        if (left.GetType() != right.GetType() || !left.GetType().IsInt()) {
            throw std::runtime_error("div: operands have incompatible types");
        }
        if (right.Int() == 0) {
            throw std::runtime_error("division by zero");
        }
        tos_value_ = runtime::Object(left.Int() % right.Int());
    }

    void Visit(tree::AndExpr* and_expr) override {
        auto[left, right] = getOperands(and_expr);
        if (left.GetType() != right.GetType() || !left.GetType().IsBool()) {
            throw std::runtime_error("(&&): operands have incompatible types");
        }
        tos_value_ = runtime::Object(left.Bool() && right.Bool());
    }

    void Visit(tree::OrExpr* or_expr) override {
        auto[left, right] = getOperands(or_expr);
        if (left.GetType() != right.GetType() || !left.GetType().IsBool()) {
            throw std::runtime_error("(||): operands have incompatible types");
        }
        tos_value_ = runtime::Object(left.Bool() || right.Bool());
    }

    void Visit(tree::NotExpr* not_expr) override {
        not_expr->GetExpression()->Visit(*this);
        if (!tos_value_.GetType().IsBool()) {
            throw std::runtime_error("not: operand must be of type bool");
        }
        tos_value_ = runtime::Object(!tos_value_.Bool());
    }

    void Visit(tree::GreaterEqExpr* greater_equal_expr) override {
        auto[left, right] = getOperands(greater_equal_expr);
        if (left.GetType() != right.GetType()) {
            throw std::runtime_error("(==): operands have incompatible types");
        }
        if (left.GetType().IsInt()) {
            tos_value_ = runtime::Object(left.Int() >= right.Int());
            return;
        }
        if (left.GetType().IsBool()) {
            tos_value_ = runtime::Object(left.Bool() >= right.Bool());
            return;
        }
    }

    void Visit(tree::GreaterExpr* greater_expr) override {
        auto[left, right] = getOperands(greater_expr);
        if (left.GetType() != right.GetType()) {
            throw std::runtime_error("(==): operands have incompatible types");
        }
        if (left.GetType().IsInt()) {
            tos_value_ = runtime::Object(left.Int() > right.Int());
            return;
        }
        if (left.GetType().IsBool()) {
            tos_value_ = runtime::Object(left.Bool() > right.Bool());
            return;
        }
    }

    void Visit(tree::LessEqExpr* less_equal_expr) override {
        auto[left, right] = getOperands(less_equal_expr);
        if (left.GetType() != right.GetType()) {
            throw std::runtime_error("(==): operands have incompatible types");
        }
        if (left.GetType().IsInt()) {
            tos_value_ = runtime::Object(left.Int() <= right.Int());
            return;
        }
        if (left.GetType().IsBool()) {
            tos_value_ = runtime::Object(left.Bool() <= right.Bool());
            return;
        }
    }

    void Visit(tree::LessExpr* less_expr) override {
        auto[left, right] = getOperands(less_expr);
        if (left.GetType() != right.GetType()) {
            throw std::runtime_error("(==): operands have incompatible types");
        }
        if (left.GetType().IsInt()) {
            tos_value_ = runtime::Object(left.Int() < right.Int());
            return;
        }
        if (left.GetType().IsBool()) {
            tos_value_ = runtime::Object(left.Bool() < right.Bool());
            return;
        }
    }

    void Visit(tree::EqExpr* equal_expr) override {
        auto[left, right] = getOperands(equal_expr);
        if (left.GetType() != right.GetType()) {
            throw std::runtime_error("(==): operands have incompatible types");
        }
        if (left.GetType().IsInt()) {
            tos_value_ = runtime::Object(left.Int() == right.Int());
            return;
        }
        if (left.GetType().IsBool()) {
            tos_value_ = runtime::Object(left.Bool() == right.Bool());
            return;
        }
    }

    void Visit(tree::StatementList* stmt_list) override {
        while (stmt_list != nullptr && stmt_list->GetHead() != nullptr) {
            stmt_list->GetHead()->Visit(*this);
            stmt_list = stmt_list->GetTail();
        }
    }

    void Visit(tree::AssignStmt* assignment_stmt) override {
        assignment_stmt->GetLValue()->Visit(*this);
        if (!symbols_.contains(last_id_)) {
            throw std::runtime_error("cannot assign to undeclared identifier " + last_id_);
        }
        assignment_stmt->GetRValue()->Visit(*this);
        symbols_[last_id_] = tos_value_;
    }

    void Visit(tree::IfStmt* if_stmt) override {
        if_stmt->GetCondition()->Visit(*this);
        if (!tos_value_.GetType().IsBool()) {
            throw std::runtime_error("expression in if condition must have bool type");
        }
        if (tos_value_.Bool()) {
            if_stmt->GetStatements()->Visit(*this);
        }
    }

    void Visit(tree::IfElseStmt* if_else_stmt) override {
        if_else_stmt->GetCondition()->Visit(*this);
        if (!tos_value_.GetType().IsBool()) {
            throw std::runtime_error("expression in if condition must have bool type");
        }
        if (tos_value_.Bool()) {
            if_else_stmt->GetIfStatements()->Visit(*this);
            return;
        }
        if_else_stmt->GetElseStatements()->Visit(*this);
    }

    void Visit(tree::PrintStmt* print_stmt) override {
        auto args = print_stmt->GetExpressions();
        while (args != nullptr && args->GetHead() != nullptr) {
            args->GetHead()->Visit(*this);
            std::cout << tos_value_.Show() << ' ';
            args = args->GetTail();
        }
    }

    void Visit(tree::ExpressionList* expr_list) override {
        while (expr_list != nullptr && expr_list->GetHead() != nullptr) {
            expr_list->GetHead()->Visit(*this);
            expr_list = expr_list->GetTail();
        }
    }

    void Visit(tree::VarDeclStmt* var_decl_stmt) override {
        var_decl_stmt->GetVariableDeclaration()->Visit(*this);
    }

    void Visit(tree::WhileStmt* while_stmt) override {
        while_stmt->GetCondition()->Visit(*this);
        if (!tos_value_.GetType().IsBool()) {
            throw std::runtime_error("expression in while condition must have bool type");
        }
        bool loop = tos_value_.Bool();
        while (loop) {
            while_stmt->GetStatements()->Visit(*this);
            while_stmt->GetCondition()->Visit(*this);
            loop = tos_value_.Bool();
        }
    }

    void Visit(tree::LValue* lvalue) override {
    }

    void Visit(tree::Reference* reference) override {
        last_id_ = reference->GetName();
    }

    void Visit(tree::Type* type) override {
    }

    void Visit(tree::BasicType* basic_type) override {
    }

    void Visit(tree::VarDecl* var_decl) override {
        auto typeName = var_decl->GetType()->GetIdentifier();
        auto varName = var_decl->GetVariableName();
        if (symbols_.contains(varName)) {
            throw std::runtime_error("redefinition of " + varName);
        }
        symbols_.insert_or_assign(varName, runtime::Object(runtime::TypeInfo(typeName)));
        last_id_ = varName;
    }

 private:
    std::unordered_map<std::string, runtime::Object> symbols_;
    std::string last_id_;
    runtime::Object tos_value_;
};

}