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
	mcs::Node*		node;
	std::string*	strVal;
}

%token	BREAK CONST CONTINUE ELSE FLOAT
%token	IF INT RETURN VOID WHILE
%token	LE GE EQ NE AND OR

%token<strVal>		ID
%token<intVal>		INT_CONST
%token<floatVal>	FLOAT_CONST

%type<node>		    FuncDef Block Stmt
%type<strVal>		FuncType
%type<intVal>		Number

%%

CompUnit	: 	FuncDef { ast = std::make_unique<mcs::CompUnit>($1); }
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