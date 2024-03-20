/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_HOME_LINCONG_MCS_SRC_LAP_PARSER_PARSER_HPP_INCLUDED
# define YY_YY_HOME_LINCONG_MCS_SRC_LAP_PARSER_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "/home/lincong/桌面/MCS/src/LAP/parser/parser.y"

    #include "AST/nodes.h"

#line 53 "/home/lincong/桌面/MCS/src/LAP/parser/parser.hpp"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    BREAK = 258,                   /* BREAK  */
    CONST = 259,                   /* CONST  */
    CONTINUE = 260,                /* CONTINUE  */
    ELSE = 261,                    /* ELSE  */
    FLOAT = 262,                   /* FLOAT  */
    IF = 263,                      /* IF  */
    INT = 264,                     /* INT  */
    RETURN = 265,                  /* RETURN  */
    VOID = 266,                    /* VOID  */
    WHILE = 267,                   /* WHILE  */
    LE = 268,                      /* LE  */
    GE = 269,                      /* GE  */
    EQ = 270,                      /* EQ  */
    NE = 271,                      /* NE  */
    AND = 272,                     /* AND  */
    OR = 273,                      /* OR  */
    ID = 274,                      /* ID  */
    INT_CONST = 275,               /* INT_CONST  */
    FLOAT_CONST = 276              /* FLOAT_CONST  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 17 "/home/lincong/桌面/MCS/src/LAP/parser/parser.y"

    float           floatVal;
    int             intVal;
    mcs::BlockItem* blockItem;
    mcs::CompUnit*  compUnit;
    mcs::Node*      node;
    std::string*    strVal;

#line 100 "/home/lincong/桌面/MCS/src/LAP/parser/parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (std::unique_ptr<mcs::Node>& ast);


#endif /* !YY_YY_HOME_LINCONG_MCS_SRC_LAP_PARSER_PARSER_HPP_INCLUDED  */
