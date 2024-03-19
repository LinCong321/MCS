%code requires {

#include "AST/nodes.h"

}

%{

#include <iostream>
#include "parser.hpp"
	
extern int yylex();
void yyerror(std::unique_ptr<mcs::Node>& ast, const char* s);

%}

%parse-param { std::unique_ptr<mcs::Node>& ast }

%union {
	float		    floatVal;
	int		        intVal;
	mcs::CompUnit*  compUnit;
	mcs::Node*		node;
	std::string*	strVal;
}

%token	BREAK CONST CONTINUE ELSE FLOAT
%token	IF INT RETURN VOID WHILE
%token	LE GE EQ NE AND OR

%token<strVal>		ID
%token<intVal>		INT_CONST
%token<floatVal>	FLOAT_CONST

%type<compUnit>		CompUnit
%type<node>         FuncDef Block Stmt
%type<strVal>		FuncType
%type<intVal>		Number

%%

Start       :   CompUnit { ast = std::unique_ptr<mcs::Node>($1); }

CompUnit	:   FuncDef { $$ = new mcs::CompUnit($1); }
            |   CompUnit FuncDef {
                    if ($1 == nullptr) {
                        yyerror(ast, "CompUnit is nullptr.");
                    }
                    $1->pushBack($2);
            }
		    ;
		
FuncDef		: 	FuncType ID '(' ')' Block { $$ = new mcs::FuncDef($1, $2, $5); }
		    ;
		
FuncType	: 	INT { $$ = new std::string("int"); }
		    ;
		
Block		: 	'{' Stmt '}' { $$ = new mcs::Block($2); }
		    ;
		
Stmt		: 	RETURN Number ';' { $$ = new mcs::RetStmt($2); }
		    ;
		
Number		: 	INT_CONST
		    ;
		
%%

void yyerror(std::unique_ptr<mcs::Node>& ast, const char* s) {
	std::cerr << "Error: " << s << std::endl;
}