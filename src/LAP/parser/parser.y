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
%type<node>         VarDecl InitVal FuncDef Block Stmt Exp AddExp MulExp UnaryExp PrimaryExp LVal Number
%type<varDefList>   VarDefList
%type<varDef>       VarDef
%type<strVal>       BType
%type<blockItem>    BlockItem

%%

Start       :   CompUnit    { ast = std::unique_ptr<mcs::Node>($1); }

CompUnit    :   VarDecl { $$ = new mcs::CompUnit($1); }
            |   CompUnit VarDecl {
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

VarDecl     :   BType VarDefList ';' {
                    if ($2 == nullptr) {
                        yyerror(ast, "VarDefList is nullptr.");
                        return 0;
                    }
                    $2->setType($1);
                    $$ = $2;
                }
            ;

VarDefList  :   VarDef  { $$ = new mcs::VarDefList($1); }
            |   VarDefList ',' VarDef {
                    if ($1 == nullptr) {
                        yyerror(ast, "VarDefList is nullptr.");
                        return 0;
                    }
                    $1->pushBack($3);
                }
            ;

VarDef      :   ID              { $$ = new mcs::VarDef($1); }
            |   ID '=' InitVal  { $$ = new mcs::VarDef($1, $3); }

InitVal     :   Exp { $$ = $1; }
            ;

FuncDef     :   BType ID '(' ')' Block  { $$ = new mcs::FuncDef($1, $2, $5); }
            ;

BType       :   INT     { $$ = new std::string("int"); }
            |   FLOAT   { $$ = new std::string("float"); }
            ;

Block       :   '{' BlockItem '}'   { $$ = $2; }
            ;

BlockItem   :   VarDecl { $$ = new mcs::BlockItem($1); }
            |   BlockItem VarDecl {
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

Stmt        :   ';'             { $$ = new mcs::Stmt(); }
            |   Exp ';'         { $$ = $1; }
            |   Block           { $$ = new mcs::BlockStmt($1); }
            |   RETURN Exp ';'  { $$ = new mcs::RetStmt($2); }
            ;

Exp         :   AddExp  { $$ = $1; }
            ;

AddExp      :   MulExp              { $$ = $1; }
            |   AddExp '+' MulExp   { $$ = new mcs::BinaryExp($1, '+', $3); }
            |   AddExp '-' MulExp   { $$ = new mcs::BinaryExp($1, '-', $3); }
            ;

MulExp      :   UnaryExp            { $$ = $1; }
            |   MulExp '*' UnaryExp { $$ = new mcs::BinaryExp($1, '*', $3); }
            |   MulExp '/' UnaryExp { $$ = new mcs::BinaryExp($1, '/', $3); }
            |   MulExp '%' UnaryExp { $$ = new mcs::BinaryExp($1, '%', $3); }
            ;

UnaryExp    :   PrimaryExp  { $$ = $1; }
            ;

PrimaryExp  :   '(' Exp ')' { $$ = $2; }
            |   LVal        { $$ = $1; }
            |   Number      { $$ = $1; }
            ;

LVal        :   ID  { $$ =  new mcs::LVal($1); }
            ;

Number      :   INT_CONST   { $$ = new mcs::IntNum($1); }
            |   FLOAT_CONST { $$ = new mcs::FloatNum($1); }
            ;

%%

void yyerror(std::unique_ptr<mcs::Node>& ast, const char* s) {
    std::cerr << "Error: \"" << s << "\" occurs at line " << yylineno
              << " on symbol \"" << yytext << "\"." << std::endl;
}