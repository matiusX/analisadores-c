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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOK_SETA = 258,                /* TOK_SETA  */
    TOK_IGUAL = 259,               /* TOK_IGUAL  */
    TOK_DIFERENTE = 260,           /* TOK_DIFERENTE  */
    TOK_MENOR_IGUAL = 261,         /* TOK_MENOR_IGUAL  */
    TOK_MAIOR_IGUAL = 262,         /* TOK_MAIOR_IGUAL  */
    TOK_ATRIB_SOMA = 263,          /* TOK_ATRIB_SOMA  */
    TOK_ATRIB_SUB = 264,           /* TOK_ATRIB_SUB  */
    TOK_ATRIB_MULT = 265,          /* TOK_ATRIB_MULT  */
    TOK_ATRIB_DIV = 266,           /* TOK_ATRIB_DIV  */
    TOK_ATRIB_MOD = 267,           /* TOK_ATRIB_MOD  */
    TOK_INC = 268,                 /* TOK_INC  */
    TOK_DEC = 269,                 /* TOK_DEC  */
    TOK_AND = 270,                 /* TOK_AND  */
    TOK_OR = 271,                  /* TOK_OR  */
    TOK_VOID = 272,                /* TOK_VOID  */
    TOK_INT = 273,                 /* TOK_INT  */
    TOK_FLOAT = 274,               /* TOK_FLOAT  */
    TOK_CHAR = 275,                /* TOK_CHAR  */
    TOK_BOOL = 276,                /* TOK_BOOL  */
    TOK_IF = 277,                  /* TOK_IF  */
    TOK_ELSE = 278,                /* TOK_ELSE  */
    TOK_FOR = 279,                 /* TOK_FOR  */
    TOK_WHILE = 280,               /* TOK_WHILE  */
    TOK_DO = 281,                  /* TOK_DO  */
    TOK_RETURN = 282,              /* TOK_RETURN  */
    TOK_BREAK = 283,               /* TOK_BREAK  */
    TOK_CONTINUE = 284,            /* TOK_CONTINUE  */
    TOK_GOTO = 285,                /* TOK_GOTO  */
    TOK_TRUE = 286,                /* TOK_TRUE  */
    TOK_FALSE = 287,               /* TOK_FALSE  */
    TOK_DOUBLE = 288,              /* TOK_DOUBLE  */
    TOK_IDENTIFICADOR = 289,       /* TOK_IDENTIFICADOR  */
    TOK_NUMERO = 290,              /* TOK_NUMERO  */
    TOK_CARACTERE = 291,           /* TOK_CARACTERE  */
    TOK_STRING = 292,              /* TOK_STRING  */
    TOK_NUMERO_DECIMAL = 293       /* TOK_NUMERO_DECIMAL  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define TOK_SETA 258
#define TOK_IGUAL 259
#define TOK_DIFERENTE 260
#define TOK_MENOR_IGUAL 261
#define TOK_MAIOR_IGUAL 262
#define TOK_ATRIB_SOMA 263
#define TOK_ATRIB_SUB 264
#define TOK_ATRIB_MULT 265
#define TOK_ATRIB_DIV 266
#define TOK_ATRIB_MOD 267
#define TOK_INC 268
#define TOK_DEC 269
#define TOK_AND 270
#define TOK_OR 271
#define TOK_VOID 272
#define TOK_INT 273
#define TOK_FLOAT 274
#define TOK_CHAR 275
#define TOK_BOOL 276
#define TOK_IF 277
#define TOK_ELSE 278
#define TOK_FOR 279
#define TOK_WHILE 280
#define TOK_DO 281
#define TOK_RETURN 282
#define TOK_BREAK 283
#define TOK_CONTINUE 284
#define TOK_GOTO 285
#define TOK_TRUE 286
#define TOK_FALSE 287
#define TOK_DOUBLE 288
#define TOK_IDENTIFICADOR 289
#define TOK_NUMERO 290
#define TOK_CARACTERE 291
#define TOK_STRING 292
#define TOK_NUMERO_DECIMAL 293

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
