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
    float           floatVal;
    int             intVal;
    mcs::BlockItem* blockItem;
    mcs::CompUnit*  compUnit;
    mcs::Node*      node;
    std::string*    strVal;
}

%token  BREAK CONST CONTINUE ELSE FLOAT
%token  IF INT RETURN VOID WHILE
%token  LE GE EQ NE AND OR

%token<strVal>      ID
%token<intVal>      INT_CONST
%token<floatVal>    FLOAT_CONST

%type<compUnit>     CompUnit
%type<node>         FuncDef Block Stmt Exp AddExp MulExp UnaryExp Number
%type<strVal>       BType
%type<blockItem>    BlockItem

%%

Start       :   CompUnit { ast = std::unique_ptr<mcs::Node>($1); }

CompUnit    :   FuncDef { $$ = new mcs::CompUnit($1); }
            |   CompUnit FuncDef {
                    if ($1 == nullptr) {
                        yyerror(ast, "CompUnit is nullptr.");
                        return 0;
                    }
                    $1->pushBack($2);
                }
            ;
		
FuncDef     :   BType ID '(' ')' Block { $$ = new mcs::FuncDef($1, $2, $5); }
            ;
		
BType       :   INT { $$ = new std::string("int"); }
            ;
		
Block       :   '{' BlockItem '}' { $$ = $2; }
            ;

BlockItem   :   Stmt { $$ = new mcs::BlockItem($1); }
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
            |   RETURN Exp ';'  { $$ = new mcs::RetStmt($2); }
            ;

Exp         :   AddExp { $$ = $1; }
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

UnaryExp    :   Number { $$ = $1; }
            ;
		
Number      :   INT_CONST   { $$ = new mcs::IntNum($1); }
            |   FLOAT_CONST { $$ = new mcs::FloatNum($1); }
            ;

%%

void yyerror(std::unique_ptr<mcs::Node>& ast, const char* s) {
    std::cerr << "Error: \"" << s << "\" occurs at line " << yylineno
              << " on symbol \"" << yytext << "\"." << std::endl;
}