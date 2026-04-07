/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 1 "src/parser.y"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<../src/tree.h>
#include<../src/strtab.h>

extern int yylineno;
extern int yylex(void);

int yywarning(char *msg);
int yyerror(char *msg);

extern tree *ast;
extern struct strEntry strTable[MAXIDS];
extern symEntry *ST_lookup_global(char *id);

enum nodeTypes {PROGRAM, DECLLIST, DECL, VARDECL, TYPESPEC, FUNDECL,
                FORMALDECLLIST, FORMALDECL, FUNBODY, LOCALDECLLIST,
                STATEMENTLIST, STATEMENT, COMPOUNDSTMT, ASSIGNSTMT,
                CONDSTMT, LOOPSTMT, RETURNSTMT, EXPRESSION, RELOP,
                ADDEXPR, ADDOP, TERM, MULOP, FACTOR, FUNCCALLEXPR,
                ARGLIST, INTEGER, IDENTIFIER, VAR, ARRAYDECL, CHAR,
                FUNCTYPENAME};

enum opType {ADD, SUB, MUL, DIV, LT, LTE, EQ, GTE, GT, NEQ};

char* scope = "";

static int entry_index(symEntry *e) {
  if (!e) return -1;
  return (int)((struct strEntry *)e - strTable);
}

static int lookup_var(char *id) {
  if (!id) return -1;
  return entry_index(ST_lookup(id));
}

static int lookup_fun(char *id) {
  if (!id) return -1;
  return entry_index(ST_lookup_global(id));
}



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 48 "src/parser.y"
{
    int value;
    struct treenode *node;
    char *strval;
}
/* Line 193 of yacc.c.  */
#line 244 "obj/y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 257 "obj/y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   144

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  62
/* YYNRULES -- Number of states.  */
#define YYNSTATES  111

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   298

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,     1,     2,    48
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    12,    14,    16,    18,
      20,    24,    31,    34,    36,    40,    43,    48,    57,    65,
      66,    69,    70,    73,    75,    77,    79,    81,    83,    87,
      92,    95,   101,   109,   115,   118,   122,   124,   128,   130,
     132,   134,   136,   138,   140,   142,   146,   148,   150,   152,
     156,   158,   160,   164,   166,   168,   170,   172,   174,   179,
     183,   188,   190
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      50,     0,    -1,    51,    -1,    52,    -1,    51,    52,    -1,
      54,    -1,    58,    -1,    10,    -1,    12,    -1,    14,    -1,
      53,     3,    33,    -1,    53,     3,    26,     4,    27,    33,
      -1,    53,     3,    -1,    57,    -1,    57,    32,    56,    -1,
      53,     3,    -1,    53,     3,    26,    27,    -1,    55,    30,
      56,    31,    28,    59,    60,    29,    -1,    55,    30,    31,
      28,    59,    60,    29,    -1,    -1,    54,    59,    -1,    -1,
      61,    60,    -1,    62,    -1,    63,    -1,    64,    -1,    65,
      -1,    66,    -1,    28,    60,    29,    -1,    74,    25,    67,
      33,    -1,    67,    33,    -1,     7,    30,    67,    31,    61,
      -1,     7,    30,    67,    31,    61,     8,    61,    -1,     9,
      30,    67,    31,    61,    -1,    13,    33,    -1,    13,    67,
      33,    -1,    69,    -1,    67,    68,    69,    -1,    22,    -1,
      19,    -1,    20,    -1,    21,    -1,    23,    -1,    24,    -1,
      71,    -1,    69,    70,    71,    -1,    15,    -1,    16,    -1,
      73,    -1,    71,    72,    73,    -1,    17,    -1,    18,    -1,
      30,    67,    31,    -1,    74,    -1,    75,    -1,     4,    -1,
       5,    -1,     3,    -1,     3,    26,    69,    27,    -1,     3,
      30,    31,    -1,     3,    30,    76,    31,    -1,    67,    -1,
      76,    32,    67,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   118,   118,   126,   132,   141,   147,   155,   157,   159,
     163,   171,   182,   193,   199,   208,   216,   227,   239,   252,
     253,   268,   269,   284,   286,   288,   290,   292,   296,   304,
     311,   319,   326,   336,   345,   347,   355,   361,   371,   372,
     373,   374,   375,   376,   379,   385,   395,   396,   399,   405,
     415,   416,   419,   425,   431,   437,   443,   451,   458,   468,
     475,   485,   491
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "INTCONST", "CHARCONST",
  "STRCONST", "KWD_IF", "KWD_ELSE", "KWD_WHILE", "KWD_INT", "KWD_STRING",
  "KWD_CHAR", "KWD_RETURN", "KWD_VOID", "OPER_ADD", "OPER_SUB", "OPER_MUL",
  "OPER_DIV", "OPER_LT", "OPER_GT", "OPER_GTE", "OPER_LTE", "OPER_EQ",
  "OPER_NEQ", "OPER_ASGN", "LSQ_BRKT", "RSQ_BRKT", "LCRLY_BRKT",
  "RCRLY_BRKT", "LPAREN", "RPAREN", "COMMA", "SEMICLN", "OPER_NEG",
  "OPER_MOD", "OPER_AT", "OPER_INC", "OPER_DEC", "OPER_AND", "OPER_OR",
  "OPER_NOT", "ERROR", "ILLEGAL_TOK", "COMMENT", "NEWLINE", "WHITESPACE",
  "MULTLNCOMMENT", "LOWER_THAN_ELSE", "$accept", "program", "declList",
  "decl", "typeSpecifier", "varDecl", "funcTypeName", "formalDeclList",
  "formalDecl", "funDecl", "localDeclList", "statementList", "statement",
  "compoundStmt", "assignStmt", "condStmt", "loopStmt", "returnStmt",
  "expression", "relop", "addExpr", "addop", "term", "mulop", "factor",
  "var", "funCallExpr", "argList", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   296,   297,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   298
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    51,    51,    52,    52,    53,    53,    53,
      54,    54,    55,    56,    56,    57,    57,    58,    58,    59,
      59,    60,    60,    61,    61,    61,    61,    61,    62,    63,
      63,    64,    64,    65,    66,    66,    67,    67,    68,    68,
      68,    68,    68,    68,    69,    69,    70,    70,    71,    71,
      72,    72,    73,    73,    73,    73,    73,    74,    74,    75,
      75,    76,    76
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       3,     6,     2,     1,     3,     2,     4,     8,     7,     0,
       2,     0,     2,     1,     1,     1,     1,     1,     3,     4,
       2,     5,     7,     5,     2,     3,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     1,     1,     3,
       1,     1,     3,     1,     1,     1,     1,     1,     4,     3,
       4,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     7,     8,     9,     0,     2,     3,     0,     5,     0,
       6,     1,     4,    12,     0,     0,    10,     0,     0,     0,
      13,     0,    19,    15,     0,     0,     0,     0,    19,    21,
       0,    19,    14,    11,     0,    20,    57,    55,    56,     0,
       0,     0,    21,     0,     0,    21,    23,    24,    25,    26,
      27,     0,    36,    44,    48,    53,    54,    16,    21,     0,
       0,     0,     0,    34,     0,    53,     0,     0,    18,    22,
      39,    40,    41,    38,    42,    43,    30,     0,    46,    47,
       0,    50,    51,     0,     0,     0,     0,    59,    61,     0,
       0,     0,    35,    28,    52,    37,    45,    49,     0,    17,
      58,    60,     0,     0,     0,    29,    62,    31,    33,     0,
      32
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,    27,    28,     9,    19,    20,    10,
      29,    44,    45,    46,    47,    48,    49,    50,    51,    77,
      52,    80,    53,    83,    54,    65,    56,    89
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -46
static const yytype_int16 yypact[] =
{
      59,   -46,   -46,   -46,    38,    59,   -46,    39,   -46,    22,
     -46,   -46,   -46,   -15,    41,    50,   -46,    35,    75,    34,
      64,    71,    59,    90,    87,    59,    84,   115,    59,    36,
      92,    59,   -46,   -46,   -15,   -46,   -11,   -46,   -46,   104,
     105,     1,    36,    20,   107,    36,   -46,   -46,   -46,   -46,
     -46,    37,    32,    10,   -46,   112,   -46,   -46,    36,    20,
       5,    20,    20,   -46,    62,   -46,   109,    83,   -46,   -46,
     -46,   -46,   -46,   -46,   -46,   -46,   -46,    20,   -46,   -46,
      20,   -46,   -46,    20,    20,   110,    52,   -46,   108,    45,
      89,   102,   -46,   -46,   -46,    32,    10,   -46,    68,   -46,
     -46,   -46,    20,    36,    36,   -46,   108,   132,   -46,    36,
     -46
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -46,   -46,   -46,   136,    12,     2,   -46,   117,   -46,   -46,
      69,   -12,   -10,   -46,   -46,   -46,   -46,   -46,   -40,   -46,
     -45,   -46,    63,   -46,    61,   -29,   -46,   -46
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      55,    64,     8,    67,    36,    37,    38,     8,    36,    37,
      38,    15,     7,    55,    86,    59,    55,     7,    16,    60,
      88,    90,    91,    36,    37,    38,    18,    81,    82,    55,
      66,    43,    95,    69,    63,    43,    87,    18,    11,    36,
      37,    38,    13,    39,    98,    40,    85,    78,    79,    41,
      43,     1,    14,     2,    21,     3,    70,    71,    72,    73,
      74,    75,   106,    22,    42,    24,    43,    78,    79,     1,
      76,     2,    17,     3,    55,    55,   101,   102,    23,   100,
      55,    70,    71,    72,    73,    74,    75,    70,    71,    72,
      73,    74,    75,   107,   108,    92,    25,    35,    26,   110,
      58,   105,    70,    71,    72,    73,    74,    75,    70,    71,
      72,    73,    74,    75,    94,    31,    30,    33,    34,    57,
     103,    70,    71,    72,    73,    74,    75,    70,    71,    72,
      73,    74,    75,   104,    61,    62,    68,    84,    93,    99,
     109,    12,    32,    96,    97
};

static const yytype_uint8 yycheck[] =
{
      29,    41,     0,    43,     3,     4,     5,     5,     3,     4,
       5,    26,     0,    42,    59,    26,    45,     5,    33,    30,
      60,    61,    62,     3,     4,     5,    14,    17,    18,    58,
      42,    30,    77,    45,    33,    30,    31,    25,     0,     3,
       4,     5,     3,     7,    84,     9,    58,    15,    16,    13,
      30,    10,    30,    12,     4,    14,    19,    20,    21,    22,
      23,    24,   102,    28,    28,    31,    30,    15,    16,    10,
      33,    12,    31,    14,   103,   104,    31,    32,     3,    27,
     109,    19,    20,    21,    22,    23,    24,    19,    20,    21,
      22,    23,    24,   103,   104,    33,    32,    28,    27,   109,
      31,    33,    19,    20,    21,    22,    23,    24,    19,    20,
      21,    22,    23,    24,    31,    28,    26,    33,     3,    27,
      31,    19,    20,    21,    22,    23,    24,    19,    20,    21,
      22,    23,    24,    31,    30,    30,    29,    25,    29,    29,
       8,     5,    25,    80,    83
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    10,    12,    14,    50,    51,    52,    53,    54,    55,
      58,     0,    52,     3,    30,    26,    33,    31,    53,    56,
      57,     4,    28,     3,    31,    32,    27,    53,    54,    59,
      26,    28,    56,    33,     3,    59,     3,     4,     5,     7,
       9,    13,    28,    30,    60,    61,    62,    63,    64,    65,
      66,    67,    69,    71,    73,    74,    75,    27,    59,    26,
      30,    30,    30,    33,    67,    74,    60,    67,    29,    60,
      19,    20,    21,    22,    23,    24,    33,    68,    15,    16,
      70,    17,    18,    72,    25,    60,    69,    31,    67,    76,
      67,    67,    33,    29,    31,    69,    71,    73,    67,    29,
      27,    31,    32,    31,    31,    33,    67,    61,    61,     8,
      61
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 119 "src/parser.y"
    {
                    tree *progNode = maketree(PROGRAM);
                    addChild(progNode, (yyvsp[(1) - (1)].node));
                    ast = progNode;
                 }
    break;

  case 3:
#line 127 "src/parser.y"
    {
                    tree* declListNode = maketree(DECLLIST);
                    addChild(declListNode, (yyvsp[(1) - (1)].node));
                    (yyval.node) = declListNode;
                 }
    break;

  case 4:
#line 133 "src/parser.y"
    {
                    tree* declListNode = maketree(DECLLIST);
                    addChild(declListNode, (yyvsp[(1) - (2)].node));
                    addChild(declListNode, (yyvsp[(2) - (2)].node));
                    (yyval.node) = declListNode;
                 }
    break;

  case 5:
#line 142 "src/parser.y"
    {
                    tree *n = maketree(DECL);
                    addChild(n, (yyvsp[(1) - (1)].node));
                    (yyval.node) = n;
                 }
    break;

  case 6:
#line 148 "src/parser.y"
    {
                    tree *n = maketree(DECL);
                    addChild(n, (yyvsp[(1) - (1)].node));
                    (yyval.node) = n;
                 }
    break;

  case 7:
#line 156 "src/parser.y"
    { (yyval.node) = maketreeWithVal(TYPESPEC, INT_TYPE); }
    break;

  case 8:
#line 158 "src/parser.y"
    { (yyval.node) = maketreeWithVal(TYPESPEC, CHAR_TYPE); }
    break;

  case 9:
#line 160 "src/parser.y"
    { (yyval.node) = maketreeWithVal(TYPESPEC, VOID_TYPE); }
    break;

  case 10:
#line 164 "src/parser.y"
    {
                    int idx = ST_insert((yyvsp[(2) - (3)].strval), (yyvsp[(1) - (3)].node)->val, SCALAR, NULL);
                    tree *n = maketree(VARDECL);
                    addChild(n, (yyvsp[(1) - (3)].node));
                    addChild(n, maketreeWithVal(IDENTIFIER, idx));
                    (yyval.node) = n;
                 }
    break;

  case 11:
#line 172 "src/parser.y"
    {
                    int idx = ST_insert((yyvsp[(2) - (6)].strval), (yyvsp[(1) - (6)].node)->val, ARRAY, NULL);
                    tree *n = maketree(VARDECL);
                    addChild(n, (yyvsp[(1) - (6)].node));
                    addChild(n, maketreeWithVal(IDENTIFIER, idx));
                    addChild(n, maketreeWithVal(INTEGER, (yyvsp[(4) - (6)].value)));
                    (yyval.node) = n;
                 }
    break;

  case 12:
#line 183 "src/parser.y"
    {
                    int idx = ST_insert((yyvsp[(2) - (2)].strval), (yyvsp[(1) - (2)].node)->val, FUNCTION, NULL);
                    tree *n = maketree(FUNCTYPENAME);
                    addChild(n, (yyvsp[(1) - (2)].node));
                    addChild(n, maketreeWithVal(IDENTIFIER, idx));
                    scope = strTable[idx].id;
                    (yyval.node) = n;
                 }
    break;

  case 13:
#line 194 "src/parser.y"
    {
                    tree *n = maketree(FORMALDECLLIST);
                    addChild(n, (yyvsp[(1) - (1)].node));
                    (yyval.node) = n;
                 }
    break;

  case 14:
#line 200 "src/parser.y"
    {
                    tree *n = maketree(FORMALDECLLIST);
                    addChild(n, (yyvsp[(1) - (3)].node));
                    addChild(n, (yyvsp[(3) - (3)].node));
                    (yyval.node) = n;
                 }
    break;

  case 15:
#line 209 "src/parser.y"
    {
                    int idx = ST_insert((yyvsp[(2) - (2)].strval), (yyvsp[(1) - (2)].node)->val, SCALAR, NULL);
                    tree *n = maketree(FORMALDECL);
                    addChild(n, (yyvsp[(1) - (2)].node));
                    addChild(n, maketreeWithVal(IDENTIFIER, idx));
                    (yyval.node) = n;
                 }
    break;

  case 16:
#line 217 "src/parser.y"
    {
                    int idx = ST_insert((yyvsp[(2) - (4)].strval), (yyvsp[(1) - (4)].node)->val, ARRAY, NULL);
                    tree *n = maketree(FORMALDECL);
                    addChild(n, (yyvsp[(1) - (4)].node));
                    addChild(n, maketreeWithVal(IDENTIFIER, idx));
                    addChild(n, maketree(ARRAYDECL));
                    (yyval.node) = n;
                 }
    break;

  case 17:
#line 228 "src/parser.y"
    {
                    tree *n = maketree(FUNDECL);
                    addChild(n, (yyvsp[(1) - (8)].node));
                    addChild(n, (yyvsp[(3) - (8)].node));
                    tree *body = maketree(FUNBODY);
                    addChild(body, (yyvsp[(6) - (8)].node));
                    addChild(body, (yyvsp[(7) - (8)].node));
                    addChild(n, body);
                    scope = "";
                    (yyval.node) = n;
                 }
    break;

  case 18:
#line 240 "src/parser.y"
    {
                    tree *n = maketree(FUNDECL);
                    addChild(n, (yyvsp[(1) - (7)].node));
                    tree *body = maketree(FUNBODY);
                    addChild(body, (yyvsp[(5) - (7)].node));
                    addChild(body, (yyvsp[(6) - (7)].node));
                    addChild(n, body);
                    scope = "";
                    (yyval.node) = n;
                 }
    break;

  case 19:
#line 252 "src/parser.y"
    { (yyval.node) = NULL; }
    break;

  case 20:
#line 254 "src/parser.y"
    {
                    if ((yyvsp[(2) - (2)].node)) {
                      tree *n = maketree(LOCALDECLLIST);
                      addChild(n, (yyvsp[(1) - (2)].node));
                      addChild(n, (yyvsp[(2) - (2)].node));
                      (yyval.node) = n;
                    } else {
                      tree *n = maketree(LOCALDECLLIST);
                      addChild(n, (yyvsp[(1) - (2)].node));
                      (yyval.node) = n;
                    }
                 }
    break;

  case 21:
#line 268 "src/parser.y"
    { (yyval.node) = NULL; }
    break;

  case 22:
#line 270 "src/parser.y"
    {
                    if ((yyvsp[(2) - (2)].node)) {
                      tree *n = maketree(STATEMENTLIST);
                      addChild(n, (yyvsp[(1) - (2)].node));
                      addChild(n, (yyvsp[(2) - (2)].node));
                      (yyval.node) = n;
                    } else {
                      tree *n = maketree(STATEMENTLIST);
                      addChild(n, (yyvsp[(1) - (2)].node));
                      (yyval.node) = n;
                    }
                 }
    break;

  case 23:
#line 285 "src/parser.y"
    { tree *n = maketree(STATEMENT); addChild(n, (yyvsp[(1) - (1)].node)); (yyval.node) = n; }
    break;

  case 24:
#line 287 "src/parser.y"
    { tree *n = maketree(STATEMENT); addChild(n, (yyvsp[(1) - (1)].node)); (yyval.node) = n; }
    break;

  case 25:
#line 289 "src/parser.y"
    { tree *n = maketree(STATEMENT); addChild(n, (yyvsp[(1) - (1)].node)); (yyval.node) = n; }
    break;

  case 26:
#line 291 "src/parser.y"
    { tree *n = maketree(STATEMENT); addChild(n, (yyvsp[(1) - (1)].node)); (yyval.node) = n; }
    break;

  case 27:
#line 293 "src/parser.y"
    { tree *n = maketree(STATEMENT); addChild(n, (yyvsp[(1) - (1)].node)); (yyval.node) = n; }
    break;

  case 28:
#line 297 "src/parser.y"
    {
                    tree *n = maketree(COMPOUNDSTMT);
                    addChild(n, (yyvsp[(2) - (3)].node));
                    (yyval.node) = n;
                 }
    break;

  case 29:
#line 305 "src/parser.y"
    {
                    tree *n = maketree(ASSIGNSTMT);
                    addChild(n, (yyvsp[(1) - (4)].node));
                    addChild(n, (yyvsp[(3) - (4)].node));
                    (yyval.node) = n;
                 }
    break;

  case 30:
#line 312 "src/parser.y"
    {
                    tree *n = maketree(ASSIGNSTMT);
                    addChild(n, (yyvsp[(1) - (2)].node));
                    (yyval.node) = n;
                 }
    break;

  case 31:
#line 320 "src/parser.y"
    {
                    tree *n = maketree(CONDSTMT);
                    addChild(n, (yyvsp[(3) - (5)].node));
                    addChild(n, (yyvsp[(5) - (5)].node));
                    (yyval.node) = n;
                 }
    break;

  case 32:
#line 327 "src/parser.y"
    {
                    tree *n = maketree(CONDSTMT);
                    addChild(n, (yyvsp[(3) - (7)].node));
                    addChild(n, (yyvsp[(5) - (7)].node));
                    addChild(n, (yyvsp[(7) - (7)].node));
                    (yyval.node) = n;
                 }
    break;

  case 33:
#line 337 "src/parser.y"
    {
                    tree *n = maketree(LOOPSTMT);
                    addChild(n, (yyvsp[(3) - (5)].node));
                    addChild(n, (yyvsp[(5) - (5)].node));
                    (yyval.node) = n;
                 }
    break;

  case 34:
#line 346 "src/parser.y"
    { (yyval.node) = maketree(RETURNSTMT); }
    break;

  case 35:
#line 348 "src/parser.y"
    {
                    tree *n = maketree(RETURNSTMT);
                    addChild(n, (yyvsp[(2) - (3)].node));
                    (yyval.node) = n;
                 }
    break;

  case 36:
#line 356 "src/parser.y"
    {
                    tree *n = maketree(EXPRESSION);
                    addChild(n, (yyvsp[(1) - (1)].node));
                    (yyval.node) = n;
                 }
    break;

  case 37:
#line 362 "src/parser.y"
    {
                    tree *n = maketree(EXPRESSION);
                    addChild(n, (yyvsp[(1) - (3)].node));
                    addChild(n, (yyvsp[(2) - (3)].node));
                    addChild(n, (yyvsp[(3) - (3)].node));
                    (yyval.node) = n;
                 }
    break;

  case 38:
#line 371 "src/parser.y"
    { (yyval.node) = maketreeWithVal(RELOP, LTE); }
    break;

  case 39:
#line 372 "src/parser.y"
    { (yyval.node) = maketreeWithVal(RELOP, LT); }
    break;

  case 40:
#line 373 "src/parser.y"
    { (yyval.node) = maketreeWithVal(RELOP, GT); }
    break;

  case 41:
#line 374 "src/parser.y"
    { (yyval.node) = maketreeWithVal(RELOP, GTE); }
    break;

  case 42:
#line 375 "src/parser.y"
    { (yyval.node) = maketreeWithVal(RELOP, EQ); }
    break;

  case 43:
#line 376 "src/parser.y"
    { (yyval.node) = maketreeWithVal(RELOP, NEQ); }
    break;

  case 44:
#line 380 "src/parser.y"
    {
                    tree *n = maketree(ADDEXPR);
                    addChild(n, (yyvsp[(1) - (1)].node));
                    (yyval.node) = n;
                 }
    break;

  case 45:
#line 386 "src/parser.y"
    {
                    tree *n = maketree(ADDEXPR);
                    addChild(n, (yyvsp[(1) - (3)].node));
                    addChild(n, (yyvsp[(2) - (3)].node));
                    addChild(n, (yyvsp[(3) - (3)].node));
                    (yyval.node) = n;
                 }
    break;

  case 46:
#line 395 "src/parser.y"
    { (yyval.node) = maketreeWithVal(ADDOP, ADD); }
    break;

  case 47:
#line 396 "src/parser.y"
    { (yyval.node) = maketreeWithVal(ADDOP, SUB); }
    break;

  case 48:
#line 400 "src/parser.y"
    {
                    tree *n = maketree(TERM);
                    addChild(n, (yyvsp[(1) - (1)].node));
                    (yyval.node) = n;
                 }
    break;

  case 49:
#line 406 "src/parser.y"
    {
                    tree *n = maketree(TERM);
                    addChild(n, (yyvsp[(1) - (3)].node));
                    addChild(n, (yyvsp[(2) - (3)].node));
                    addChild(n, (yyvsp[(3) - (3)].node));
                    (yyval.node) = n;
                 }
    break;

  case 50:
#line 415 "src/parser.y"
    { (yyval.node) = maketreeWithVal(MULOP, MUL); }
    break;

  case 51:
#line 416 "src/parser.y"
    { (yyval.node) = maketreeWithVal(MULOP, DIV); }
    break;

  case 52:
#line 420 "src/parser.y"
    {
                    tree *n = maketree(FACTOR);
                    addChild(n, (yyvsp[(2) - (3)].node));
                    (yyval.node) = n;
                 }
    break;

  case 53:
#line 426 "src/parser.y"
    {
                    tree *n = maketree(FACTOR);
                    addChild(n, (yyvsp[(1) - (1)].node));
                    (yyval.node) = n;
                 }
    break;

  case 54:
#line 432 "src/parser.y"
    {
                    tree *n = maketree(FACTOR);
                    addChild(n, (yyvsp[(1) - (1)].node));
                    (yyval.node) = n;
                 }
    break;

  case 55:
#line 438 "src/parser.y"
    {
                    tree *n = maketree(FACTOR);
                    addChild(n, maketreeWithVal(INTEGER, (yyvsp[(1) - (1)].value)));
                    (yyval.node) = n;
                 }
    break;

  case 56:
#line 444 "src/parser.y"
    {
                    tree *n = maketree(FACTOR);
                    addChild(n, maketreeWithVal(CHAR, (yyvsp[(1) - (1)].value)));
                    (yyval.node) = n;
                 }
    break;

  case 57:
#line 452 "src/parser.y"
    {
                    int idx = lookup_var((yyvsp[(1) - (1)].strval));
                    tree *n = maketree(VAR);
                    addChild(n, maketreeWithVal(IDENTIFIER, idx));
                    (yyval.node) = n;
                 }
    break;

  case 58:
#line 459 "src/parser.y"
    {
                    int idx = lookup_var((yyvsp[(1) - (4)].strval));
                    tree *n = maketree(VAR);
                    addChild(n, maketreeWithVal(IDENTIFIER, idx));
                    addChild(n, (yyvsp[(3) - (4)].node));
                    (yyval.node) = n;
                 }
    break;

  case 59:
#line 469 "src/parser.y"
    {
                    int idx = lookup_fun((yyvsp[(1) - (3)].strval));
                    tree *n = maketree(FUNCCALLEXPR);
                    addChild(n, maketreeWithVal(IDENTIFIER, idx));
                    (yyval.node) = n;
                 }
    break;

  case 60:
#line 476 "src/parser.y"
    {
                    int idx = lookup_fun((yyvsp[(1) - (4)].strval));
                    tree *n = maketree(FUNCCALLEXPR);
                    addChild(n, maketreeWithVal(IDENTIFIER, idx));
                    addChild(n, (yyvsp[(3) - (4)].node));
                    (yyval.node) = n;
                 }
    break;

  case 61:
#line 486 "src/parser.y"
    {
                    tree *n = maketree(ARGLIST);
                    addChild(n, (yyvsp[(1) - (1)].node));
                    (yyval.node) = n;
                 }
    break;

  case 62:
#line 492 "src/parser.y"
    {
                    tree *n = maketree(ARGLIST);
                    addChild(n, (yyvsp[(1) - (3)].node));
                    addChild(n, (yyvsp[(3) - (3)].node));
                    (yyval.node) = n;
                 }
    break;


/* Line 1267 of yacc.c.  */
#line 2087 "obj/y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 500 "src/parser.y"


int yywarning(char *msg){
  printf("warning: line %d: %s\n", yylineno, msg);
  return 0;
}

int yyerror(char * msg){
  printf("error: line %d: %s\n", yylineno, msg);
  return 0;
}

