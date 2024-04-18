%code requires {
    #include "AST/nodes.h"
}

%{
    #include <iostream>
    #include "parser.hpp"

    extern int yylex();
    extern int yylineno;
    extern const char* yytext;

    void yyerror(std::unique_ptr<mcs::Node>& ast, const char* s);
%}

%parse-param { std::unique_ptr<mcs::Node>& ast }

%union {
    float               floatVal;
    int                 intVal;
    mcs::BlockItem*     blockItem;
    mcs::CompUnit*      compUnit;
    mcs::FuncParam*     funcParam;
    mcs::FuncParams*    funcParams;
    mcs::LValue*        lValue;
    mcs::Node*          node;
    mcs::VarDef*        varDef;
    mcs::VarDefList*    varDefList;
    std::string*        strVal;
}

%token  BREAK CONST CONTINUE ELSE FLOAT
%token  IF INT RETURN VOID WHILE
%token  LE GE EQ NE AND OR

%token<strVal>      ID
%token<intVal>      INT_CONST
%token<floatVal>    FLOAT_CONST

%type<compUnit>     CompUnit
%type<node>         Decl ConstDecl ConstInitVal
%type<strVal>       BType VOID
%type<varDefList>   ConstDefList VarDefList
%type<varDef>       ConstDef VarDef
%type<node>         ConstExp AddExp MulExp UnaryExp PrimaryExp Exp
%type<lValue>       LVal
%type<node>         Number VarDecl InitVal FuncDef Block Stmt BStmt
%type<funcParams>   FuncFParams
%type<funcParam>    FuncFParam
%type<blockItem>    BlockItem
%type<node>         Cond LOrExp LAndExp EqExp RelExp WithElse

%%

Start           :   CompUnit    { ast = std::make_unique<mcs::Start>($1); }

CompUnit        :   Decl { $$ = new mcs::CompUnit($1); }
                |   CompUnit Decl {
                        if ($1 == nullptr) {
                            yyerror(ast, "CompUnit is nullptr.");
                            return 0;
                        }
                        $1->pushBack($2);
                    }
                |   FuncDef { $$ = new mcs::CompUnit($1); }
                |   CompUnit FuncDef {
                            if ($1 == nullptr) {
                            yyerror(ast, "CompUnit is nullptr.");
                            return 0;
                        }
                        $1->pushBack($2);
                    }
                ;

Decl            :   ConstDecl   { $$ = $1; }
                |   VarDecl     { $$ = $1; }
                ;

ConstDecl       :   CONST BType ConstDefList ';' {
                        if ($3 == nullptr) {
                            yyerror(ast, "VarDefList is nullptr.");
                            return 0;
                        }
                        $3->setAttribute($2, true);
                        $$ = $3;
                    }
                ;

BType           :   INT     { $$ = new std::string("int"); }
                |   FLOAT   { $$ = new std::string("float"); }
                ;

ConstDefList    :   ConstDef    { $$ = new mcs::VarDefList($1); }
                |   ConstDefList ',' ConstDef {
                        if ($1 == nullptr) {
                            yyerror(ast, "VarDefList is nullptr.");
                            return 0;
                        }
                        $1->pushBack($3);
                    }
                ;

ConstDef        :   ID '=' ConstInitVal { $$ = new mcs::VarDef($1, $3); }
                ;

ConstInitVal    :   ConstExp    { $$ = $1; }
                ;

ConstExp        :   AddExp  { $$ = $1; }
                ;

AddExp          :   MulExp              { $$ = $1; }
                |   AddExp '+' MulExp   { $$ = new mcs::ArithExp($1, '+', $3); }
                |   AddExp '-' MulExp   { $$ = new mcs::ArithExp($1, '-', $3); }
                ;

MulExp          :   UnaryExp            { $$ = $1; }
                |   MulExp '*' UnaryExp { $$ = new mcs::ArithExp($1, '*', $3); }
                |   MulExp '/' UnaryExp { $$ = new mcs::ArithExp($1, '/', $3); }
                |   MulExp '%' UnaryExp { $$ = new mcs::ArithExp($1, '%', $3); }
                ;

UnaryExp        :   PrimaryExp      { $$ = $1; }
                |   ID '(' ')'      { $$ = new mcs::FuncCallExp($1); }
                |   '+' UnaryExp    { $$ = new mcs::UnaryExp('+', $2); }
                |   '-' UnaryExp    { $$ = new mcs::UnaryExp('-', $2); }
                |   '!' UnaryExp    { $$ = new mcs::UnaryExp('!', $2); }
                ;

PrimaryExp      :   '(' Exp ')' { $$ = $2; }
                |   LVal        { $$ = new mcs::VarExp($1); }
                |   Number      { $$ = $1; }
                ;

Exp             :   AddExp  { $$ = $1; }
                ;

LVal            :   ID  { $$ = new mcs::LValue($1); }
                ;

Number          :   INT_CONST   { $$ = new mcs::IntNum($1); }
                |   FLOAT_CONST { $$ = new mcs::FloatNum($1); }
                ;

VarDecl         :   BType VarDefList ';' {
                        if ($2 == nullptr) {
                            yyerror(ast, "VarDefList is nullptr.");
                            return 0;
                        }
                        $2->setAttribute($1);
                        $$ = $2;
                    }
                ;

VarDefList      :   VarDef  { $$ = new mcs::VarDefList($1); }
                |   VarDefList ',' VarDef {
                        if ($1 == nullptr) {
                            yyerror(ast, "VarDefList is nullptr.");
                            return 0;
                        }
                        $1->pushBack($3);
                    }
                ;

VarDef          :   ID              { $$ = new mcs::VarDef($1); }
                |   ID '=' InitVal  { $$ = new mcs::VarDef($1, $3); }

InitVal         :   Exp { $$ = $1; }
                ;

FuncDef         :   BType ID '(' ')' Block              { $$ = new mcs::FuncDef($1, $2, $5); }
                |   BType ID '(' FuncFParams ')' Block  { $$ = new mcs::FuncDef($1, $2, $4, $6); }
                |   VOID ID '(' ')' Block               { $$ = new mcs::FuncDef(new std::string("void"), $2, $5); }
                |   VOID ID '(' FuncFParams ')' Block   { $$ = new mcs::FuncDef(new std::string("void"), $2, $4, $6); }
                ;

FuncFParams     :   FuncFParam  { $$ = new mcs::FuncParams($1); }
                |   FuncFParams ',' FuncFParam {
                        if ($1 == nullptr) {
                            yyerror(ast, "FuncFParams is nullptr.");
                            return 0;
                        }
                        $1->pushBack($3);
                    }
                ;

FuncFParam      :   BType ID    { $$ = new mcs::FuncParam($1, $2); }
                ;

Block           :   '{' '}'             { $$ = new mcs::BlockItem();}
                |   '{' BlockItem '}'   { $$ = $2; }
                ;

BlockItem       :   Decl { $$ = new mcs::BlockItem($1); }
                |   BlockItem Decl {
                        if ($1 == nullptr) {
                            yyerror(ast, "BlockItem is nullptr.");
                            return 0;
                        }
                        $1->pushBack($2);
                    }
                |   Stmt    { $$ = new mcs::BlockItem($1); }
                |   BlockItem Stmt {
                        if ($1 == nullptr) {
                            yyerror(ast, "BlockItem is nullptr.");
                            return 0;
                        }
                        $1->pushBack($2);
                    }
                ;

Stmt            :   BStmt                               { $$ = $1; }
                |   IF '(' Cond ')' Stmt                { $$ = new mcs::IfElseStmt($3, $5); }
                |   IF '(' Cond ')' WithElse ELSE Stmt  { $$ = new mcs::IfElseStmt($3, $5, $7); }
                |   WHILE '(' Cond ')' Stmt             { $$ = new mcs::WhileStmt($3, $5); }
                ;

BStmt           :   LVal '=' Exp ';'    { $$ = new mcs::AssignStmt($1, $3); }
                |   ';'                 { $$ = new mcs::NullStmt(); }
                |   Exp ';'             { $$ = $1; }
                |   Block               { $$ = new mcs::BlockStmt($1); }
                |   BREAK ';'           { $$ = new mcs::BreakStmt(); }
                |   CONTINUE ';'        { $$ = new mcs::ContinueStmt(); }
                |   RETURN ';'          { $$ = new mcs::RetStmt(); }
                |   RETURN Exp ';'      { $$ = new mcs::RetStmt($2); }
                ;

Cond            :   LOrExp  { $$ = $1; }
                ;

LOrExp          :   LAndExp             { $$ = $1; }
                |   LOrExp OR LAndExp   { $$ = new mcs::LogicExp($1, '|', $3); }
                ;

LAndExp         :   EqExp               { $$ = $1; }
                |   LAndExp AND EqExp   { $$ = new mcs::LogicExp($1, '&', $3); }
                ;

EqExp           :   RelExp          { $$ = $1; }
                |   EqExp EQ RelExp { $$ = new mcs::RelExp($1, new std::string("=="), $3); }
                |   EqExp NE RelExp { $$ = new mcs::RelExp($1, new std::string("!="), $3); }
                ;

RelExp          :   AddExp              { $$ = $1; }
                |   RelExp '<' AddExp   { $$ = new mcs::RelExp($1, new std::string("<"), $3); }
                |   RelExp '>' AddExp   { $$ = new mcs::RelExp($1, new std::string(">"), $3); }
                |   RelExp LE AddExp    { $$ = new mcs::RelExp($1, new std::string("<="), $3); }
                |   RelExp GE AddExp    { $$ = new mcs::RelExp($1, new std::string(">="), $3); }
                ;

WithElse        :   IF '(' Cond ')' WithElse ELSE WithElse  { $$ = new mcs::IfElseStmt($3, $5, $7); }
                |   WHILE '(' Cond ')' WithElse             { $$ = new mcs::WhileStmt($3, $5); }
                |   BStmt                                   { $$ = $1; }
                ;

%%

void yyerror(std::unique_ptr<mcs::Node>& ast, const char* s) {
    std::cerr << "Error: \"" << s << "\" occurs at line " << yylineno
              << " on symbol \"" << yytext << "\"." << std::endl;
}