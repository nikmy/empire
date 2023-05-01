#include "ir_builder.hpp"

namespace ast::visit
{

IRBuilder::IRBuilder() : builder_(new llvm::IRBuilder(context_)), module_("file", context_) {
}

llvm::Value* IRBuilder::unwrapIfPointer(llvm::Value* maybe_ptr) {
    if (maybe_ptr->getType() == llvm::Type::getInt32PtrTy(context_)) {
        return builder_->CreateLoad(llvm::Type::getInt32Ty(context_), maybe_ptr);
    }
    if (maybe_ptr->getType() == llvm::Type::getInt1PtrTy(context_)) {
        return builder_->CreateLoad(llvm::Type::getInt1Ty(context_), maybe_ptr);
    }
    return maybe_ptr;
}

decltype(auto) IRBuilder::getOperands(tree::BinaryOpExpr* expr) {
    auto left = unwrapIfPointer(Accept(expr->GetLeftExpression()));
    auto right = unwrapIfPointer(Accept(expr->GetRightExpression()));
    return std::make_pair(left, right);
}

void IRBuilder::Visit(ast::tree::Program* program) {
    program->GetMainFunc()->Visit(*this);
}

void IRBuilder::Visit(ast::tree::MainFunc* main_func) {
    auto function_type = llvm::FunctionType::get(
        llvm::Type::getVoidTy(context_), false
    );
    auto function_llvm = llvm::Function::Create(
        function_type,
        llvm::Function::ExternalLinkage,
        "main",
        module_
    );
    auto entry = llvm::BasicBlock::Create(context_, "entry", function_llvm);
    builder_->SetInsertPoint(entry);

    main_func->GetStatementList()->Visit(*this);

    builder_->CreateRetVoid();
}

void IRBuilder::Visit(ast::tree::ExpressionList* expr_list) {
    while (expr_list != nullptr && expr_list->GetHead() != nullptr) {
        expr_list->GetHead()->Visit(*this);
        expr_list = expr_list->GetTail();
    }
}

void IRBuilder::Visit(ast::tree::IntExpr* int_expr) {
    auto alloca = builder_->CreateAlloca(llvm::Type::getInt32Ty(context_));
    llvm::Value* value = builder_->getInt32(int_expr->GetValue());
    builder_->CreateStore(value, alloca);
    SetValue(alloca);
}

void IRBuilder::Visit(ast::tree::BoolExpr* bool_expr) {
    auto alloca = builder_->CreateAlloca(llvm::Type::getInt1Ty(context_));
    llvm::Value* value = builder_->getInt1(bool_expr->GetValue());
    builder_->CreateStore(value, alloca);
    SetValue(alloca);
}

void IRBuilder::Visit(ast::tree::IdentExpr* ident_expr) {
    SetValue(named_values_[ident_expr->GetIdentifier()]);
}

void IRBuilder::Visit(ast::tree::FuncCall* func_call) {

}

void IRBuilder::Visit(ast::tree::AddExpr* add_expr) {
    auto[left, right] = getOperands(add_expr);
    if (left->getType() != llvm::Type::getInt32Ty(context_) || left->getType() != right->getType()) {
        throw std::runtime_error("(+): operands have incompatible types");
    }
    auto result = builder_->CreateAdd(left, right);
    auto alloca = builder_->CreateAlloca(llvm::Type::getInt32Ty(context_));
    builder_->CreateStore(result, alloca);
    SetValue(alloca);
}

void IRBuilder::Visit(ast::tree::SubExpr* sub_expr) {
    auto[left, right] = getOperands(sub_expr);
    if (left->getType() != llvm::Type::getInt32Ty(context_) || left->getType() != right->getType()) {
        throw std::runtime_error("(-): operands have incompatible types");
    }
    auto result = builder_->CreateSub(left, right);
    auto alloca = builder_->CreateAlloca(llvm::Type::getInt32Ty(context_));
    builder_->CreateStore(result, alloca);
    SetValue(alloca);
}

void IRBuilder::Visit(ast::tree::MulExpr* mul_expr) {
    auto[left, right] = getOperands(mul_expr);
    if (left->getType() != llvm::Type::getInt32Ty(context_) || left->getType() != right->getType()) {
        throw std::runtime_error("(*): operands have incompatible types");
    }
    auto result = builder_->CreateMul(left, right);
    auto alloca = builder_->CreateAlloca(llvm::Type::getInt32Ty(context_));
    builder_->CreateStore(result, alloca);
    SetValue(alloca);
}

void IRBuilder::Visit(ast::tree::DivExpr* div_expr) {
    auto[left, right] = getOperands(div_expr);
    if (left->getType() != llvm::Type::getInt32Ty(context_) || left->getType() != right->getType()) {
        throw std::runtime_error("(/): operands have incompatible types");
    }
    auto result = builder_->CreateSDiv(left, right);
    auto alloca = builder_->CreateAlloca(llvm::Type::getInt32Ty(context_));
    builder_->CreateStore(result, alloca);
    SetValue(alloca);
}

void IRBuilder::Visit(ast::tree::ModExpr* mod_expr) {
    auto[left, right] = getOperands(mod_expr);
    if (left->getType() != llvm::Type::getInt32Ty(context_) || left->getType() != right->getType()) {
        throw std::runtime_error("(%): operands have incompatible types");
    }
    auto result = builder_->CreateSRem(left, right);
    auto alloca = builder_->CreateAlloca(llvm::Type::getInt32Ty(context_));
    builder_->CreateStore(result, alloca);
    SetValue(alloca);
}

void IRBuilder::Visit(ast::tree::AndExpr* and_expr) {
    auto[left, right] = getOperands(and_expr);
    if (left->getType() != llvm::Type::getInt1Ty(context_) || left->getType() != right->getType()) {
        throw std::runtime_error("(&&): operands have incompatible types");
    }
    auto result = builder_->CreateAnd(left, right);
    auto alloca = builder_->CreateAlloca(llvm::Type::getInt1Ty(context_));
    builder_->CreateStore(result, alloca);
    SetValue(alloca);
}

void IRBuilder::Visit(ast::tree::NotExpr* not_expr) {
    auto arg = Accept(not_expr->GetExpression());
    if (arg->getType() != llvm::Type::getInt1Ty(context_)) {
        throw std::runtime_error("not: operand must be of type bool");
    }
    auto result = builder_->CreateNot(arg);
    auto alloca = builder_->CreateAlloca(llvm::Type::getInt1Ty(context_));
    builder_->CreateStore(result, alloca);
    SetValue(alloca);
}

void IRBuilder::Visit(ast::tree::OrExpr* or_expr) {
    auto[left, right] = getOperands(or_expr);
    if (left->getType() != builder_->getInt1Ty() || left->getType() != right->getType()) {
        throw std::runtime_error("(||): operands have incompatible types");
    }
    auto result = builder_->CreateOr(left, right);
    auto alloca = builder_->CreateAlloca(llvm::Type::getInt1Ty(context_));
    builder_->CreateStore(result, alloca);
    SetValue(alloca);
}

void IRBuilder::Visit(ast::tree::GreaterEqExpr* greater_equal_expr) {
    auto[left, right] = getOperands(greater_equal_expr);
    if (left->getType() != llvm::Type::getInt32Ty(context_) || left->getType() != right->getType()) {
        throw std::runtime_error("(>=): operands have incompatible types");
    }
    auto result = builder_->CreateICmpSGE(left, right);
    auto alloca = builder_->CreateAlloca(llvm::Type::getInt1Ty(context_));
    builder_->CreateStore(result, alloca);
    SetValue(alloca);
}

void IRBuilder::Visit(ast::tree::GreaterExpr* greater_expr) {
    auto[left, right] = getOperands(greater_expr);
    if (left->getType() != llvm::Type::getInt32Ty(context_) || left->getType() != right->getType()) {
        throw std::runtime_error("(>): operands have incompatible types");
    }
    auto result = builder_->CreateICmpSGT(left, right);
    auto alloca = builder_->CreateAlloca(llvm::Type::getInt1Ty(context_));
    builder_->CreateStore(result, alloca);
    SetValue(alloca);
}

void IRBuilder::Visit(ast::tree::LessEqExpr* less_equal_expr) {
    auto[left, right] = getOperands(less_equal_expr);
    if (left->getType() != llvm::Type::getInt32Ty(context_) || left->getType() != right->getType()) {
        throw std::runtime_error("(<=): operands have incompatible types");
    }
    auto result = builder_->CreateICmpSLE(left, right);
    auto alloca = builder_->CreateAlloca(llvm::Type::getInt1Ty(context_));
    builder_->CreateStore(result, alloca);
    SetValue(alloca);
}

void IRBuilder::Visit(ast::tree::LessExpr* less_expr) {
    auto[left, right] = getOperands(less_expr);
    if (left->getType() != llvm::Type::getInt32Ty(context_) || left->getType() != right->getType()) {
        throw std::runtime_error("(<): operands have incompatible types");
    }
    auto result = builder_->CreateICmpSLT(left, right);
    auto alloca = builder_->CreateAlloca(llvm::Type::getInt1Ty(context_));
    builder_->CreateStore(result, alloca);
    SetValue(alloca);
}

void IRBuilder::Visit(ast::tree::EqExpr* equal_expr) {
    auto[left, right] = getOperands(equal_expr);
    if (left->getType() != llvm::Type::getInt32Ty(context_) || left->getType() != right->getType()) {
        throw std::runtime_error("(>=): operands have incompatible types");
    }
    auto result = builder_->CreateICmpEQ(left, right);
    auto alloca = builder_->CreateAlloca(llvm::Type::getInt1Ty(context_));
    builder_->CreateStore(result, alloca);
    SetValue(alloca);
}

void IRBuilder::Visit(ast::tree::StatementList* stmt_list) {
    while (stmt_list != nullptr && stmt_list->GetHead() != nullptr) {
        stmt_list->GetHead()->Visit(*this);
        stmt_list = stmt_list->GetTail();
    }
}

void IRBuilder::Visit(ast::tree::AssignStmt* assignment) {
    auto pointer = Accept(assignment->GetRValue());
    llvm::Value* value = unwrapIfPointer(pointer);
    auto var = named_values_[assignment->GetLValue()->GetName()];
    if (var->getAllocatedType() != value->getType()) {
        throw std::runtime_error("an attempt to assign wrong type");
    }
    builder_->CreateStore(value, var);
}

void IRBuilder::Visit(ast::tree::IfStmt* if_stmt) {
    auto func = builder_->GetInsertBlock()->getParent();
    llvm::BasicBlock* true_block = llvm::BasicBlock::Create(context_, "", func);
    llvm::BasicBlock* end_block = llvm::BasicBlock::Create(context_, "", func);

    llvm::Value* condition = unwrapIfPointer(Accept(if_stmt->GetCondition()));
    builder_->CreateCondBr(condition, true_block, end_block);

    builder_->SetInsertPoint(true_block);
    Accept(if_stmt->GetStatements());
    builder_->CreateBr(end_block);

    builder_->SetInsertPoint(end_block);
}

void IRBuilder::Visit(ast::tree::IfElseStmt* if_else_stmt) {
    auto func = builder_->GetInsertBlock()->getParent();
    llvm::BasicBlock* true_block = llvm::BasicBlock::Create(context_, "", func);
    llvm::BasicBlock* false_block = llvm::BasicBlock::Create(context_, "", func);
    llvm::BasicBlock* end_block = llvm::BasicBlock::Create(context_, "", func);

    llvm::Value* condition = unwrapIfPointer(Accept(if_else_stmt->GetCondition()));
    builder_->CreateCondBr(condition, true_block, false_block);

    builder_->SetInsertPoint(true_block);
    Accept(if_else_stmt->GetIfStatements());
    builder_->CreateBr(end_block);

    builder_->SetInsertPoint(false_block);
    Accept(if_else_stmt->GetElseStatements());
    builder_->CreateBr(end_block);

    builder_->SetInsertPoint(end_block);
}

void IRBuilder::Visit(ast::tree::PrintStmt* print_stmt) {
    std::vector<llvm::Value*> arg_values;
    std::vector<llvm::Type*> arg_types;

    std::string fmt_string;

    // Will be filled when format string is built
    arg_values.push_back(nullptr);

    for (auto list = print_stmt->GetExpressions(); list && list->GetHead(); list = list->GetTail()) {
        llvm::Value* arg = unwrapIfPointer(Accept(list->GetHead()));
        arg_values.push_back(arg);
        fmt_string += "%d ";
    }

    // Remove redundant space
    if (arg_values.size() > 1) {
        fmt_string.pop_back();
    }
    fmt_string += "\n";

    // Build string constant
    auto fmt_const = llvm::ConstantDataArray::getString(context_, fmt_string);
    auto alloca = builder_->CreateAlloca(fmt_const->getType());
    builder_->CreateStore(fmt_const, alloca);
    auto fmt = builder_->CreateBitCast(alloca, builder_->getInt8PtrTy());

    // Fill first argument
    arg_values[0] = fmt;

    auto printf_type = llvm::FunctionType::get(
        llvm::Type::getInt32Ty(context_), {fmt->getType()}, true
    );

    auto printf_callee = module_.getOrInsertFunction("printf", printf_type);

    SetValue(
        builder_->CreateCall(printf_callee, arg_values)
    );
}

void IRBuilder::Visit(ast::tree::VarDeclStmt* var_decl_stmt) {
    var_decl_stmt->GetVariableDeclaration()->Visit(*this);
}

void IRBuilder::Visit(ast::tree::WhileStmt* while_stmt) {
    auto func = builder_->GetInsertBlock()->getParent();
    llvm::BasicBlock* check = llvm::BasicBlock::Create(context_, "", func);
    llvm::BasicBlock* loop = llvm::BasicBlock::Create(context_, "", func);
    llvm::BasicBlock* end = llvm::BasicBlock::Create(context_, "", func);
    builder_->CreateBr(check);

    builder_->SetInsertPoint(check);
    llvm::Value* condition = unwrapIfPointer(Accept(while_stmt->GetCondition()));
    builder_->CreateCondBr(condition, loop, end);

    builder_->SetInsertPoint(loop);
    Accept(while_stmt->GetStatements());
    builder_->CreateBr(check);

    builder_->SetInsertPoint(end);
}

void IRBuilder::Visit(ast::tree::FuncCallStmt* func_call_stmt) {

}

void IRBuilder::Visit(ast::tree::LValue* lvalue) {

}

void IRBuilder::Visit(ast::tree::Reference* reference) {

}

void IRBuilder::Visit(ast::tree::Type* type) {

}

void IRBuilder::Visit(ast::tree::BasicType* basic_type) {

}

void IRBuilder::Visit(ast::tree::DeclarationList* decl_list) {

}

void IRBuilder::Visit(ast::tree::VarDecl* var_decl) {
    auto function = builder_->GetInsertBlock()->getParent();
    llvm::BasicBlock &block = function->getEntryBlock();

    llvm::IRBuilder<> tmp(&block, block.begin());

    llvm::AllocaInst* var = nullptr;

    if (var_decl->GetType()->GetIdentifier() == "bool") {
        var = tmp.CreateAlloca(llvm::Type::getInt1Ty(context_), nullptr, var_decl->GetVariableName());
    } else if (var_decl->GetType()->GetIdentifier() == "int") {
        var = tmp.CreateAlloca(llvm::Type::getInt32Ty(context_), nullptr, var_decl->GetVariableName());
    }

    named_values_[var_decl->GetVariableName()] = var;
}

void IRBuilder::Visit(ast::tree::FuncDecl* func_decl) {

}

void IRBuilder::Visit(ast::tree::FormalArg* arg) {

}

void IRBuilder::Visit(ast::tree::FormalArgList* arg_list) {

}

llvm::Module& IRBuilder::GetModule() {
    return module_;
}

}