%option noyywrap yylineno

%{
    #include "parser/parser.hpp"
    void yyerror(const char* s);
%}

%s          COMMENT

IDENTIFIER  [a-zA-Z_][a-zA-Z0-9_]*
INT_CONST   [1-9][0-9]*|0[0-7]*|0[xX][0-9a-fA-F]+
FLOAT_CONST [0-9]*\.?[0-9]+([Ee][+-]?[0-9]+)?

%%

[ \t\n\r]*              {}
"//".*                  {}
"/*"                    { BEGIN(COMMENT); }
<COMMENT>"*/"           { BEGIN(INITIAL); }
<COMMENT>([^*]|\n)+|.   {}
<COMMENT><<EOF>>        { return 0; }

"break"         { return BREAK; }
"const"         { return CONST; }
"continue"      { return CONTINUE; }
"else"          { return ELSE; }
"float"         { return FLOAT; }
"if"            { return IF; }
"int"           { return INT; }
"return"        { return RETURN; }
"void"          { return VOID; }
"while"         { return WHILE; }

"<="            { return LE; }
">="            { return GE; }
"=="            { return EQ; }
"!="            { return NE; }
"&&"            { return AND; }
"||"            { return OR; }

{IDENTIFIER}    { yylval.strVal = new std::string(yytext); return ID; }
{INT_CONST}     { yylval.intVal = std::stoi(yytext, nullptr, 0); return INT_CONST; }
{FLOAT_CONST}   { yylval.floatVal = std::stof(yytext); return FLOAT_CONST; }


[-*<>=!+/%,;()\[\]{}]   { return yytext[0]; }
.                       { yyerror("Unknown character"); return 0; }

%%

void yyerror(const char* s) {
    fprintf(stderr, "Error: %s at line %d on symbol \'%s\'\n", s, yylineno, yytext);
    exit(1);
}