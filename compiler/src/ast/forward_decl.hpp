#pragma once

namespace ast
{

// Interfaces

class INode;
class IVisitor;

// Node Types, : public INode

namespace tree
{

// Program

class Program;
class MainFunc;

// TODO: functions
// class Function;
// class IOFunc;
// class PureFunc;

// TODO: struct types & methods

// Declarations

class Declaration;
class VarDecl;

// Statements

class Statement;
class StatementList;

class VarDeclStmt;
class AssignStmt;
class IfStmt;
class IfElseStmt;
class WhileStmt;
class PrintStmt;

// Expressions

class Expression;
class ExpressionList;

class IntExpr;
class BoolExpr;
class IdentExpr;

class BinaryOpExpr;

class AddExpr;
class SubExpr;
class MulExpr;
class DivExpr;
class ModExpr;

class AndExpr;
class NotExpr;
class OrExpr;

class EqExpr;
class LessExpr;
class LessEqExpr;
class GreaterExpr;
class GreaterEqExpr;

// Type

class Type;
class BasicType;

// LValue

class LValue;
class Reference;
}

}