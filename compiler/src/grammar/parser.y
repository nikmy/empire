%skeleton "lalr1.cc"
%require "3.5"

%defines
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
    #include <string>
    #include <memory>

    class Scanner;
    class Driver;

    #include "forward_decl.hpp"
    using namespace ast::tree;
}

// %param { Driver &drv }

%define parse.trace
%define parse.error verbose

%code {
    #include "driver.hh"
    #include "location.hh"
    #include "scanner.hpp"

    #include "include_list.hpp"

    static yy::parser::symbol_type yylex(Scanner &scanner, Driver& driver) {
        return scanner.ScanToken();
    }
}

%lex-param { Scanner &scanner }
%lex-param { Driver &driver }
%parse-param { Scanner &scanner }
%parse-param { Driver &driver }

%locations

%define api.token.prefix {TOK_}

%token
    END 0 "end of file"
    ASSIGN "="
    MINUS "-"
    PLUS "+"
    STAR "*"
    SLASH "/"
    PERCENT "%"
    LPAREN "("
    RPAREN ")"
    AND "&&"
    OR "||"
    NOT "!"
    LT "<"
    LE "<="
    GT ">"
    GE ">="
    EQUAL "=="
    TRUE "true"
    FALSE "false"
    INT "int"
    BOOL "bool"
    SEMICOLON ";"
    IO "io"
    PURE "pure"
    MAIN "main"
    LSBRACKET "["
    RSBRACKET "]"
    SBRACKETS "[]"
    LCBRACKET "{"
    RCBRACKET "}"
    PRINT "println"
    IF "if"
    ELSE "else"
    WHILE "while"
    COMMA ","
;

%token <std::string> IDENTIFIER "identifier";
%token <int> NUMBER "number";

%nterm <Program*> program;
%nterm <MainFunc*> main_func;

%nterm <Statement*> statement;
%nterm <StatementList*> statement_list;

%nterm <Expression*> expression;
%nterm <ExpressionList*> expression_list;

%nterm <FuncCall*> func_call;

%nterm <Type*> type;
%nterm <BasicType*> basic_type;
%nterm <Type*> io_return_type;

%nterm <LValue*> lvalue;

%nterm <Declaration*> declaration;
%nterm <DeclarationList*> declaration_list;

%nterm <VarDecl*> variable_declaration;
%nterm <FuncDecl*> func_declaration;
%nterm <FormalArg*> formal;
%nterm <FormalArgList*> formal_list;

// %printer { yyo << $$; } <*>;

%%

%start program;

program:
    main_func
        {
            $$ = new Program($1);
            driver.program_ = $$;
        }
    ;

main_func:
    "io" "main" "(" ")" "{" statement_list "}"
        { $$ = new MainFunc($6); }
    ;

statement_list:
    %empty                     { $$ = nullptr; }
    | statement statement_list { $$ = new StatementList($1, $2); }
    ;

statement:
    variable_declaration
        { $$ = new VarDeclStmt($1); }
    | "if" expression "{" statement_list "}"
        { $$ = new IfStmt($2, $4); }
    | "if" expression "{" statement_list "}" "else" "{" statement_list "}"
        { $$ = new IfElseStmt($2, $4, $8); }
    | "while" expression "{" statement_list "}"
        { $$ = new WhileStmt($2, $4); }
    | lvalue "=" expression ";"
        { $$ = new AssignStmt($1, $3); }
    | "println" "(" expression_list ")" ";"
        { $$ = new PrintStmt($3); }
    | func_call ";"
        { $$ = new FuncCallStmt($1); }
    ;

type:
    basic_type  { $$ = $1; }
    ;

basic_type:
    "int"          { $$ = new BasicType("int"); }
    | "bool"       { $$ = new BasicType("bool"); }
    ;

// Can be on the left side of assignment
lvalue:
    "identifier" { $$ = new Reference($1); }
    ;

%left "||";
%left "&&";
%left "<" "<=" ">" ">=" "==";

%left "+" "-";
%left "*" "/" "%";

%left "!";

expression:
    "number"                               { $$ = new IntExpr($1); }
    | "-" "number"                         { $$ = new IntExpr(-$2); }
    | "true"                               { $$ = new BoolExpr(true); }
    | "false"                              { $$ = new BoolExpr(false); }
    | "identifier"                         { $$ = new IdentExpr($1); }
    | expression "*" expression            { $$ = new MulExpr($1, $3); }
    | expression "/" expression            { $$ = new DivExpr($1, $3); }
    | expression "%" expression            { $$ = new ModExpr($1, $3); }
    | expression "+" expression            { $$ = new AddExpr($1, $3); }
    | expression "-" expression            { $$ = new SubExpr($1, $3); }
    | "!" expression                       { $$ = new NotExpr($2); }
    | expression "<" expression            { $$ = new LessExpr($1, $3); }
    | expression "<=" expression           { $$ = new LessEqExpr($1, $3); }
    | expression ">" expression            { $$ = new GreaterExpr($1, $3); }
    | expression ">=" expression           { $$ = new GreaterEqExpr($1, $3); }
    | expression "&&" expression           { $$ = new AndExpr($1, $3); }
    | expression "||" expression           { $$ = new OrExpr($1, $3); }
    | expression "==" expression           { $$ = new EqExpr($1, $3); }
    | "(" expression ")"                   { $$ = $2; }
    | func_call                            { $$ = $1; }
    ;

declaration_list:
    %empty                         { $$ = nullptr; }
    | declaration declaration_list { $$ = new DeclarationList($1, $2); }
    ;

declaration:
    variable_declaration { $$ = $1; }
    | func_declaration   { $$ = $1; }
    ;

variable_declaration:
    type IDENTIFIER ";" { $$ = new VarDecl($1, $2); }
    ;

func_declaration:
    "io" IDENTIFIER "(" formal_list ")" io_return_type "{" statement_list "}"
        { $$ = new FuncDecl(true, $2, $4, $6, $8); }
    | "pure" IDENTIFIER "(" formal_list ")" type "{" statement_list "}"
        { $$ = new FuncDecl(false, $2, $4, $6, $8); }
    ;

formal_list:
    %empty               { $$ = nullptr; }
    | formal             { $$ = new FormalArgList($1, nullptr); }
    | formal formal_list { $$ = new FormalArgList($1, $2); }
    ;

formal:
    type IDENTIFIER { $$ = new FormalArg($1, $2); }
    ;

io_return_type:
    %empty { $$ = nullptr; }
    | type { $$ = $1; }
    ;

func_call:
    IDENTIFIER "(" expression_list ")" { $$ = new FuncCall($1, $3); }
    ;

expression_list:
    %empty                           { $$ = nullptr; }
    | expression                     { $$ = new ExpressionList($1, nullptr); }
    | expression "," expression_list { $$ = new ExpressionList($1, $3); }
    ;

%%

void yy::parser::error(const location_type& l, const std::string& m) {
  std::cerr << l << ": " << m << '\n';
}