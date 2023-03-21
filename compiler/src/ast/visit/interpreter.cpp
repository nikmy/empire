#include "interpreter.hpp"

namespace ast::visit
{

decltype(auto) EvalVisitor::getOperands(tree::BinaryOpExpr* expr) {
    expr->GetLeftExpression()->Visit(*this);
    auto left = tos_value_;
    expr->GetRightExpression()->Visit(*this);
    auto right = tos_value_;
    return std::make_pair(left, right);
}

void EvalVisitor::Visit(tree::Program* program) {
    program->GetMainFunc()->Visit(*this);
}

void EvalVisitor::Visit(tree::MainFunc* main_func) {
    main_func->GetStatementList()->Visit(*this);
}

void EvalVisitor::Visit(tree::IntExpr* int_expr) {
    auto intObj = runtime::Object(int_expr->GetValue());
    std::swap(tos_value_, intObj);
}

void EvalVisitor::Visit(tree::BoolExpr* bool_expr) {
    auto boolObj = runtime::Object(bool_expr->GetValue());
    std::swap(tos_value_, boolObj);
}

void EvalVisitor::Visit(tree::IdentExpr* ident_expr) {
    last_id_ = ident_expr->GetIdentifier();
    if (symbols_.contains(last_id_)) {
        tos_value_ = symbols_[last_id_];
    }
}

void EvalVisitor::Visit(tree::AddExpr* add_expr) {
    auto[left, right] = getOperands(add_expr);
    if (left.GetType() != right.GetType() || !left.GetType().IsInt()) {
        throw std::runtime_error("(+): operands have incompatible types");
    }
    tos_value_ = runtime::Object(left.Int() + right.Int());
}

void EvalVisitor::Visit(tree::SubExpr* sub_expr) {
    auto[left, right] = getOperands(sub_expr);
    if (left.GetType() != right.GetType() || !left.GetType().IsInt()) {
        throw std::runtime_error("(-): operands have incompatible types");
    }
    tos_value_ = runtime::Object(left.Int() - right.Int());
}

void EvalVisitor::Visit(tree::MulExpr* mul_expr) {
    auto[left, right] = getOperands(mul_expr);
    if (left.GetType() != right.GetType() || !left.GetType().IsInt()) {
        throw std::runtime_error("(*): operands have incompatible types");
    }
    tos_value_ = runtime::Object(left.Int() * right.Int());
}

void EvalVisitor::Visit(tree::DivExpr* div_expr) {
    auto[left, right] = getOperands(div_expr);
    if (left.GetType() != right.GetType() || !left.GetType().IsInt()) {
        throw std::runtime_error("div: operands have incompatible types");
    }
    if (right.Int() == 0) {
        throw std::runtime_error("division by zero");
    }
    tos_value_ = runtime::Object(left.Int() / right.Int());
}

void EvalVisitor::Visit(tree::ModExpr* mod_expr) {
    auto[left, right] = getOperands(mod_expr);
    if (left.GetType() != right.GetType() || !left.GetType().IsInt()) {
        throw std::runtime_error("div: operands have incompatible types");
    }
    if (right.Int() == 0) {
        throw std::runtime_error("division by zero");
    }
    tos_value_ = runtime::Object(left.Int() % right.Int());
}

void EvalVisitor::Visit(tree::AndExpr* and_expr) {
    auto[left, right] = getOperands(and_expr);
    if (left.GetType() != right.GetType() || !left.GetType().IsBool()) {
        throw std::runtime_error("(&&): operands have incompatible types");
    }
    tos_value_ = runtime::Object(left.Bool() && right.Bool());
}

void EvalVisitor::Visit(tree::OrExpr* or_expr) {
    auto[left, right] = getOperands(or_expr);
    if (left.GetType() != right.GetType() || !left.GetType().IsBool()) {
        throw std::runtime_error("(||): operands have incompatible types");
    }
    tos_value_ = runtime::Object(left.Bool() || right.Bool());
}

void EvalVisitor::Visit(tree::NotExpr* not_expr) {
    not_expr->GetExpression()->Visit(*this);
    if (!tos_value_.GetType().IsBool()) {
        throw std::runtime_error("not: operand must be of type bool");
    }
    tos_value_ = runtime::Object(!tos_value_.Bool());
}

void EvalVisitor::Visit(tree::GreaterEqExpr* greater_equal_expr) {
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

void EvalVisitor::Visit(tree::GreaterExpr* greater_expr) {
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

void EvalVisitor::Visit(tree::LessEqExpr* less_equal_expr) {
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

void EvalVisitor::Visit(tree::LessExpr* less_expr) {
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

void EvalVisitor::Visit(tree::EqExpr* equal_expr) {
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

void EvalVisitor::Visit(tree::StatementList* stmt_list) {
    while (stmt_list != nullptr && stmt_list->GetHead() != nullptr) {
        stmt_list->GetHead()->Visit(*this);
        stmt_list = stmt_list->GetTail();
    }
}

void EvalVisitor::Visit(tree::AssignStmt* assignment_stmt) {
    assignment_stmt->GetLValue()->Visit(*this);
    if (!symbols_.contains(last_id_)) {
        throw std::runtime_error("cannot assign to undeclared identifier " + last_id_);
    }
    assignment_stmt->GetRValue()->Visit(*this);
    symbols_[last_id_] = tos_value_;
}

void EvalVisitor::Visit(tree::IfStmt* if_stmt) {
    if_stmt->GetCondition()->Visit(*this);
    if (!tos_value_.GetType().IsBool()) {
        throw std::runtime_error("expression in if condition must have bool type");
    }
    if (tos_value_.Bool()) {
        if_stmt->GetStatements()->Visit(*this);
    }
}

void EvalVisitor::Visit(tree::IfElseStmt* if_else_stmt) {
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

void EvalVisitor::Visit(tree::PrintStmt* print_stmt) {
    auto args = print_stmt->GetExpressions();
    while (args != nullptr && args->GetHead() != nullptr) {
        args->GetHead()->Visit(*this);
        std::cout << tos_value_.Show() << ' ';
        args = args->GetTail();
    }
}

void EvalVisitor::Visit(tree::ExpressionList* expr_list) {
    while (expr_list != nullptr && expr_list->GetHead() != nullptr) {
        expr_list->GetHead()->Visit(*this);
        expr_list = expr_list->GetTail();
    }
}

void EvalVisitor::Visit(tree::VarDeclStmt* var_decl_stmt) {
    var_decl_stmt->GetVariableDeclaration()->Visit(*this);
}

void EvalVisitor::Visit(tree::WhileStmt* while_stmt) {
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

void EvalVisitor::Visit(tree::Reference* reference) {
    last_id_ = reference->GetName();
}

void EvalVisitor::Visit(tree::VarDecl* var_decl) {
    auto typeName = var_decl->GetType()->GetIdentifier();
    auto varName = var_decl->GetVariableName();
    if (symbols_.contains(varName)) {
        throw std::runtime_error("redefinition of " + varName);
    }
    symbols_.insert_or_assign(varName, runtime::Object(runtime::TypeInfo(typeName)));
    last_id_ = varName;
}

void EvalVisitor::Visit(tree::FuncCall* func_call) {

}

void EvalVisitor::Visit(tree::FuncCallStmt* func_call_stmt) {

}

void EvalVisitor::Visit(tree::DeclarationList* decl_list) {

}

void EvalVisitor::Visit(tree::FuncDecl* func_decl) {

}

void EvalVisitor::Visit(tree::FormalArg* arg) {

}

void EvalVisitor::Visit(tree::FormalArgList* arg_list) {

}

}