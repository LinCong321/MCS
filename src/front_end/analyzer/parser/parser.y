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

%token<strVal>      IDENTIFIER
%token<intVal>      INT_CONST
%token<floatVal>    FLOAT_CONST

%type<compUnit>     CompUnit
%type<node>         Decl ConstDecl ConstInitVal
%type<strVal>       BType VOID
%type<varDefList>   ConstDefList VarDefList
%type<varDef>       ConstDef VarDef
%type<node>         ConstExp AddExp MulExp UnaryExp PrimaryExp Exp
%type<node>         LVal Number VarDecl InitVal FuncDef Block Stmt
%type<blockItem>    BlockItem

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

ConstDef        :   IDENTIFIER '=' ConstInitVal { $$ = new mcs::VarDef($1, $3); }
                ;

ConstInitVal    :   ConstExp    { $$ = $1; }
                ;

ConstExp        :   AddExp  { $$ = $1; }
                ;

AddExp          :   MulExp              { $$ = $1; }
                |   AddExp '+' MulExp   { $$ = new mcs::BinaryExp($1, '+', $3); }
                |   AddExp '-' MulExp   { $$ = new mcs::BinaryExp($1, '-', $3); }
                ;

MulExp          :   UnaryExp            { $$ = $1; }
                |   MulExp '*' UnaryExp { $$ = new mcs::BinaryExp($1, '*', $3); }
                |   MulExp '/' UnaryExp { $$ = new mcs::BinaryExp($1, '/', $3); }
                |   MulExp '%' UnaryExp { $$ = new mcs::BinaryExp($1, '%', $3); }
                ;

UnaryExp        :   PrimaryExp  { $$ = $1; }
                ;

PrimaryExp      :   '(' Exp ')' { $$ = $2; }
                |   LVal        { $$ = $1; }
                |   Number      { $$ = $1; }
                ;

Exp             :   AddExp  { $$ = $1; }
                ;

LVal            :   IDENTIFIER  { $$ =  new mcs::LVal($1); }
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

VarDef          :   IDENTIFIER              { $$ = new mcs::VarDef($1); }
                |   IDENTIFIER '=' InitVal  { $$ = new mcs::VarDef($1, $3); }

InitVal         :   Exp { $$ = $1; }
                ;

FuncDef         :   BType IDENTIFIER '(' ')' Block  { $$ = new mcs::FuncDef($1, $2, $5); }
                |   VOID IDENTIFIER '(' ')' Block   { $$ = new mcs::FuncDef(new std::string("void"), $2, $5); }
                ;

Block           :   '{' BlockItem '}'   { $$ = $2; }
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

Stmt            :   ';'             { $$ = new mcs::Stmt(); }
                |   Exp ';'         { $$ = $1; }
                |   Block           { $$ = new mcs::BlockStmt($1); }
                |   RETURN ';'      { $$ = new mcs::RetStmt(); }
                |   RETURN Exp ';'  { $$ = new mcs::RetStmt($2); }
                ;

%%

void yyerror(std::unique_ptr<mcs::Node>& ast, const char* s) {
    std::cerr << "Error: \"" << s << "\" occurs at line " << yylineno
              << " on symbol \"" << yytext << "\"." << std::endl;
}