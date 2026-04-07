/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 251,
     INTCONST = 252,
     CHARCONST = 253,
     STRCONST = 254,
     KWD_IF = 255,
     KWD_ELSE = 256,
     KWD_WHILE = 257,
     KWD_INT = 258,
     KWD_STRING = 259,
     KWD_CHAR = 260,
     KWD_RETURN = 261,
     KWD_VOID = 262,
     OPER_ADD = 263,
     OPER_SUB = 264,
     OPER_MUL = 265,
     OPER_DIV = 266,
     OPER_LT = 267,
     OPER_GT = 268,
     OPER_GTE = 269,
     OPER_LTE = 270,
     OPER_EQ = 271,
     OPER_NEQ = 272,
     OPER_ASGN = 273,
     LSQ_BRKT = 274,
     RSQ_BRKT = 275,
     LCRLY_BRKT = 276,
     RCRLY_BRKT = 277,
     LPAREN = 278,
     RPAREN = 279,
     COMMA = 280,
     SEMICLN = 281,
     OPER_NEG = 282,
     OPER_MOD = 283,
     OPER_AT = 284,
     OPER_INC = 285,
     OPER_DEC = 286,
     OPER_AND = 287,
     OPER_OR = 288,
     OPER_NOT = 289,
     ERROR = 290,
     ILLEGAL_TOK = 291,
     COMMENT = 292,
     NEWLINE = 293,
     WHITESPACE = 294,
     MULTLNCOMMENT = 295,
     LOWER_THAN_ELSE = 298
   };
#endif
/* Tokens.  */
#define ID 251
#define INTCONST 252
#define CHARCONST 253
#define STRCONST 254
#define KWD_IF 255
#define KWD_ELSE 256
#define KWD_WHILE 257
#define KWD_INT 258
#define KWD_STRING 259
#define KWD_CHAR 260
#define KWD_RETURN 261
#define KWD_VOID 262
#define OPER_ADD 263
#define OPER_SUB 264
#define OPER_MUL 265
#define OPER_DIV 266
#define OPER_LT 267
#define OPER_GT 268
#define OPER_GTE 269
#define OPER_LTE 270
#define OPER_EQ 271
#define OPER_NEQ 272
#define OPER_ASGN 273
#define LSQ_BRKT 274
#define RSQ_BRKT 275
#define LCRLY_BRKT 276
#define RCRLY_BRKT 277
#define LPAREN 278
#define RPAREN 279
#define COMMA 280
#define SEMICLN 281
#define OPER_NEG 282
#define OPER_MOD 283
#define OPER_AT 284
#define OPER_INC 285
#define OPER_DEC 286
#define OPER_AND 287
#define OPER_OR 288
#define OPER_NOT 289
#define ERROR 290
#define ILLEGAL_TOK 291
#define COMMENT 292
#define NEWLINE 293
#define WHITESPACE 294
#define MULTLNCOMMENT 295
#define LOWER_THAN_ELSE 298




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 53 "src/parser.y"
{
    int value;
    struct treenode *node;
    char *strval;
    struct {
      char *text;
      int line;
    } id;
}
/* Line 1529 of yacc.c.  */
#line 155 "obj/y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

