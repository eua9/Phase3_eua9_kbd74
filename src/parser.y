%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<../src/tree.h>
#include<../src/strtab.h>
#include<../src/semantic.h>
#include<../src/codegen.h>

extern int yylineno;
extern int yylex(void);

int yywarning(char *msg);
int yyerror(char *msg);

extern tree *ast;
extern struct strEntry strTable[MAXIDS];
extern symEntry *ST_lookup_global(char *id);
extern void reset_formal_params(void);
extern void add_param(int data_type, int symbol_type);
extern void connect_params(int i, int num_params);

#define SET_LINE(NODE, LIN) do { if ((NODE) && (LIN) > 0) (NODE)->lineno = (LIN); } while (0)

enum nodeTypes {PROGRAM, DECLLIST, DECL, VARDECL, TYPESPEC, FUNDECL,
                FORMALDECLLIST, FORMALDECL, FUNBODY, LOCALDECLLIST,
                STATEMENTLIST, STATEMENT, COMPOUNDSTMT, ASSIGNSTMT,
                CONDSTMT, LOOPSTMT, RETURNSTMT, EXPRESSION, RELOP,
                ADDEXPR, ADDOP, TERM, MULOP, FACTOR, FUNCCALLEXPR,
                ARGLIST, INTEGER, IDENTIFIER, VAR, ARRAYDECL, CHAR,
                FUNCTYPENAME};

enum opType {ADD, SUB, MUL, DIV, LT, LTE, EQ, GTE, GT, NEQ};

#define SET_LINE(NODE, LIN) do { if ((NODE) && (LIN) > 0) (NODE)->lineno = (LIN); } while (0)

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

%}

%union
{
    int value;
    struct treenode *node;
    char *strval;
    struct {
      char *text;
      int line;
    } id;
}

/* Token codes must match src/tokendef.h and scanner.l returns. */
%token <id> ID 251
%token <value> INTCONST 252
%token <value> CHARCONST 253
%token <strval> STRCONST 254

%token <strval> KWD_IF 255
%token <strval> KWD_ELSE 256
%token <strval> KWD_WHILE 257
%token <strval> KWD_INT 258
%token <strval> KWD_STRING 259
%token <strval> KWD_CHAR 260
%token <strval> KWD_RETURN 261
%token <strval> KWD_VOID 262

%token <strval> OPER_ADD 263
%token <strval> OPER_SUB 264
%token <strval> OPER_MUL 265
%token <strval> OPER_DIV 266
%token <strval> OPER_LT 267
%token <strval> OPER_GT 268
%token <strval> OPER_GTE 269
%token <strval> OPER_LTE 270
%token <strval> OPER_EQ 271
%token <strval> OPER_NEQ 272
%token <strval> OPER_ASGN 273

%token <strval> LSQ_BRKT 274
%token <strval> RSQ_BRKT 275
%token <strval> LCRLY_BRKT 276
%token <strval> RCRLY_BRKT 277
%token <strval> LPAREN 278
%token <strval> RPAREN 279

%token <strval> COMMA 280
%token <strval> SEMICLN 281

%token <strval> OPER_NEG 282
%token <strval> OPER_MOD 283
%token <strval> OPER_AT 284
%token <strval> OPER_INC 285
%token <strval> OPER_DEC 286
%token <strval> OPER_AND 287
%token <strval> OPER_OR 288
%token <strval> OPER_NOT 289
%token <strval> ERROR 290
%token <strval> ILLEGAL_TOK 291
%token <strval> COMMENT 292
%token <strval> NEWLINE 293
%token <strval> WHITESPACE 294
%token <strval> MULTLNCOMMENT 295

%nonassoc LOWER_THAN_ELSE
%nonassoc KWD_ELSE

%type <node> program declList decl varDecl typeSpecifier funDecl funcTypeName
%type <node> formalDeclList formalDecl localDeclList statementList statement
%type <node> compoundStmt assignStmt condStmt loopStmt returnStmt
%type <node> expression relop addExpr addop term mulop factor funCallExpr argList var

%start program

%%

program         : declList
                 {
                    tree *progNode = maketree(PROGRAM);
                    SET_LINE(progNode, $1->lineno > 0 ? $1->lineno : 1);
                    addChild(progNode, $1);
                    ast = progNode;
                    semantic_analyze(ast);
                    if (codegen_enabled)
                      codegen_generate(ast);
                 }
                ;

declList        : decl
                 {
                    tree* declListNode = maketree(DECLLIST);
                    SET_LINE(declListNode, $1->lineno);
                    addChild(declListNode, $1);
                    $$ = declListNode;
                 }
                | declList decl
                 {
                    tree* declListNode = maketree(DECLLIST);
                    SET_LINE(declListNode, $1->lineno);
                    addChild(declListNode, $1);
                    addChild(declListNode, $2);
                    $$ = declListNode;
                 }
                ;

decl            : varDecl
                 {
                    tree *n = maketree(DECL);
                    SET_LINE(n, $1->lineno);
                    addChild(n, $1);
                    $$ = n;
                 }
                | funDecl
                 {
                    tree *n = maketree(DECL);
                    SET_LINE(n, $1->lineno);
                    addChild(n, $1);
                    $$ = n;
                 }
                ;

typeSpecifier   : KWD_INT
                 { tree *t = maketreeWithVal(TYPESPEC, INT_TYPE); SET_LINE(t, yylineno); $$ = t; }
                | KWD_CHAR
                 { tree *t = maketreeWithVal(TYPESPEC, CHAR_TYPE); SET_LINE(t, yylineno); $$ = t; }
                | KWD_VOID
                 { tree *t = maketreeWithVal(TYPESPEC, VOID_TYPE); SET_LINE(t, yylineno); $$ = t; }
                ;

varDecl         : typeSpecifier ID SEMICLN
                 {
                    int idx = ST_insert($2.text, $1->val, SCALAR, 0, NULL);
                    if (idx < 0)
                      printf("error: line %d: Symbol declared multiple times.\n", $2.line);
                    tree *n = maketree(VARDECL);
                    SET_LINE(n, $2.line);
                    addChild(n, $1);
                    tree *idn = maketreeWithVal(IDENTIFIER, idx);
                    SET_LINE(idn, $2.line);
                    addChild(n, idn);
                    $$ = n;
                 }
                | typeSpecifier ID LSQ_BRKT INTCONST RSQ_BRKT SEMICLN
                 {
                    if ($4 == 0)
                      printf("error: line %d: Array variable declared with size of zero.\n", $2.line);
                    int idx = ST_insert($2.text, $1->val, ARRAY, $4, NULL);
                    if (idx < 0)
                      printf("error: line %d: Symbol declared multiple times.\n", $2.line);
                    tree *n = maketree(VARDECL);
                    SET_LINE(n, $2.line);
                    addChild(n, $1);
                    tree *idn = maketreeWithVal(IDENTIFIER, idx);
                    SET_LINE(idn, $2.line);
                    addChild(n, idn);
                    tree *isz = maketreeWithVal(INTEGER, $4);
                    SET_LINE(isz, yylineno);
                    addChild(n, isz);
                    $$ = n;
                 }
                ;

funcTypeName    : typeSpecifier ID
                 {
                    reset_formal_params();
                    int idx = ST_insert($2.text, $1->val, FUNCTION, 0, NULL);
                    if (idx < 0)
                      printf("error: line %d: Symbol declared multiple times.\n", $2.line);
                    else
                      scope = strTable[idx].id;
                    tree *n = maketree(FUNCTYPENAME);
                    SET_LINE(n, $2.line);
                    addChild(n, $1);
                    tree *idn = maketreeWithVal(IDENTIFIER, idx);
                    SET_LINE(idn, $2.line);
                    addChild(n, idn);
                    $$ = n;
                 }
                ;

formalDeclList  : formalDecl
                 {
                    tree *n = maketree(FORMALDECLLIST);
                    SET_LINE(n, $1->lineno);
                    addChild(n, $1);
                    $$ = n;
                 }
                | formalDecl COMMA formalDeclList
                 {
                    tree *n = maketree(FORMALDECLLIST);
                    SET_LINE(n, $1->lineno);
                    addChild(n, $1);
                    addChild(n, $3);
                    $$ = n;
                 }
                ;

formalDecl      : typeSpecifier ID
                 {
                    int idx = ST_insert($2.text, $1->val, SCALAR, 0, NULL);
                    if (idx < 0)
                      printf("error: line %d: Symbol declared multiple times.\n", $2.line);
                    else
                      add_param($1->val, SCALAR);
                    tree *n = maketree(FORMALDECL);
                    SET_LINE(n, $2.line);
                    addChild(n, $1);
                    tree *idn = maketreeWithVal(IDENTIFIER, idx);
                    SET_LINE(idn, $2.line);
                    addChild(n, idn);
                    $$ = n;
                 }
                | typeSpecifier ID LSQ_BRKT RSQ_BRKT
                 {
                    int idx = ST_insert($2.text, $1->val, ARRAY, 0, NULL);
                    if (idx < 0)
                      printf("error: line %d: Symbol declared multiple times.\n", $2.line);
                    else
                      add_param($1->val, ARRAY);
                    tree *n = maketree(FORMALDECL);
                    SET_LINE(n, $2.line);
                    addChild(n, $1);
                    tree *idn = maketreeWithVal(IDENTIFIER, idx);
                    SET_LINE(idn, $2.line);
                    addChild(n, idn);
                    addChild(n, maketree(ARRAYDECL));
                    $$ = n;
                 }
                ;

funDecl         : funcTypeName LPAREN formalDeclList RPAREN LCRLY_BRKT localDeclList statementList RCRLY_BRKT
                 {
                    int func_idx = getChild($1, 1)->val;
                    if (func_idx >= 0)
                      connect_params(func_idx, 0);
                    tree *n = maketree(FUNDECL);
                    SET_LINE(n, $1->lineno);
                    addChild(n, $1);
                    addChild(n, $3);
                    tree *body = maketree(FUNBODY);
                    addChild(body, $6);
                    addChild(body, $7);
                    addChild(n, body);
                    scope = "";
                    $$ = n;
                 }
                | funcTypeName LPAREN RPAREN LCRLY_BRKT localDeclList statementList RCRLY_BRKT
                 {
                    int func_idx = getChild($1, 1)->val;
                    if (func_idx >= 0)
                      connect_params(func_idx, 0);
                    tree *n = maketree(FUNDECL);
                    SET_LINE(n, $1->lineno);
                    addChild(n, $1);
                    tree *body = maketree(FUNBODY);
                    addChild(body, $5);
                    addChild(body, $6);
                    addChild(n, body);
                    scope = "";
                    $$ = n;
                 }
                ;

localDeclList   : /* empty */ { $$ = NULL; }
                | varDecl localDeclList
                 {
                    if ($2) {
                      tree *n = maketree(LOCALDECLLIST);
                      SET_LINE(n, $1->lineno);
                      addChild(n, $1);
                      addChild(n, $2);
                      $$ = n;
                    } else {
                      tree *n = maketree(LOCALDECLLIST);
                      SET_LINE(n, $1->lineno);
                      addChild(n, $1);
                      $$ = n;
                    }
                 }
                ;

statementList   : /* empty */ { $$ = NULL; }
                | statement statementList
                 {
                    if ($2) {
                      tree *n = maketree(STATEMENTLIST);
                      SET_LINE(n, $1->lineno);
                      addChild(n, $1);
                      addChild(n, $2);
                      $$ = n;
                    } else {
                      tree *n = maketree(STATEMENTLIST);
                      SET_LINE(n, $1->lineno);
                      addChild(n, $1);
                      $$ = n;
                    }
                 }
                ;

statement       : compoundStmt
                 { tree *n = maketree(STATEMENT); SET_LINE(n, $1->lineno); addChild(n, $1); $$ = n; }
                | assignStmt
                 { tree *n = maketree(STATEMENT); SET_LINE(n, $1->lineno); addChild(n, $1); $$ = n; }
                | condStmt
                 { tree *n = maketree(STATEMENT); SET_LINE(n, $1->lineno); addChild(n, $1); $$ = n; }
                | loopStmt
                 { tree *n = maketree(STATEMENT); SET_LINE(n, $1->lineno); addChild(n, $1); $$ = n; }
                | returnStmt
                 { tree *n = maketree(STATEMENT); SET_LINE(n, $1->lineno); addChild(n, $1); $$ = n; }
                ;

compoundStmt    : LCRLY_BRKT statementList RCRLY_BRKT
                 {
                    tree *n = maketree(COMPOUNDSTMT);
                    SET_LINE(n, yylineno);
                    addChild(n, $2);
                    $$ = n;
                 }
                ;

assignStmt      : var OPER_ASGN expression SEMICLN
                 {
                    tree *n = maketree(ASSIGNSTMT);
                    SET_LINE(n, $1->lineno);
                    addChild(n, $1);
                    addChild(n, $3);
                    $$ = n;
                 }
                | expression SEMICLN
                 {
                    tree *n = maketree(ASSIGNSTMT);
                    SET_LINE(n, yylineno);
                    addChild(n, $1);
                    $$ = n;
                 }
                ;

condStmt        : KWD_IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE
                 {
                    tree *n = maketree(CONDSTMT);
                    SET_LINE(n, yylineno);
                    addChild(n, $3);
                    addChild(n, $5);
                    $$ = n;
                 }
                | KWD_IF LPAREN expression RPAREN statement KWD_ELSE statement
                 {
                    tree *n = maketree(CONDSTMT);
                    SET_LINE(n, yylineno);
                    addChild(n, $3);
                    addChild(n, $5);
                    addChild(n, $7);
                    $$ = n;
                 }
                ;

loopStmt        : KWD_WHILE LPAREN expression RPAREN statement
                 {
                    tree *n = maketree(LOOPSTMT);
                    SET_LINE(n, yylineno);
                    addChild(n, $3);
                    addChild(n, $5);
                    $$ = n;
                 }
                ;

returnStmt      : KWD_RETURN SEMICLN
                 { tree *n = maketree(RETURNSTMT); SET_LINE(n, yylineno); $$ = n; }
                | KWD_RETURN expression SEMICLN
                 {
                    tree *n = maketree(RETURNSTMT);
                    SET_LINE(n, yylineno);
                    addChild(n, $2);
                    $$ = n;
                 }
                ;

expression      : addExpr
                 {
                    tree *n = maketree(EXPRESSION);
                    SET_LINE(n, $1->lineno);
                    addChild(n, $1);
                    $$ = n;
                 }
                | expression relop addExpr
                 {
                    tree *n = maketree(EXPRESSION);
                    SET_LINE(n, $1->lineno);
                    addChild(n, $1);
                    addChild(n, $2);
                    addChild(n, $3);
                    $$ = n;
                 }
                ;

relop           : OPER_LTE { tree *t = maketreeWithVal(RELOP, LTE); SET_LINE(t, yylineno); $$ = t; }
                | OPER_LT  { tree *t = maketreeWithVal(RELOP, LT); SET_LINE(t, yylineno); $$ = t; }
                | OPER_GT  { tree *t = maketreeWithVal(RELOP, GT); SET_LINE(t, yylineno); $$ = t; }
                | OPER_GTE { tree *t = maketreeWithVal(RELOP, GTE); SET_LINE(t, yylineno); $$ = t; }
                | OPER_EQ  { tree *t = maketreeWithVal(RELOP, EQ); SET_LINE(t, yylineno); $$ = t; }
                | OPER_NEQ { tree *t = maketreeWithVal(RELOP, NEQ); SET_LINE(t, yylineno); $$ = t; }
                ;

addExpr         : term
                 {
                    tree *n = maketree(ADDEXPR);
                    SET_LINE(n, $1->lineno);
                    addChild(n, $1);
                    $$ = n;
                 }
                | addExpr addop term
                 {
                    tree *n = maketree(ADDEXPR);
                    SET_LINE(n, $1->lineno);
                    addChild(n, $1);
                    addChild(n, $2);
                    addChild(n, $3);
                    $$ = n;
                 }
                ;

addop           : OPER_ADD { tree *t = maketreeWithVal(ADDOP, ADD); SET_LINE(t, yylineno); $$ = t; }
                | OPER_SUB { tree *t = maketreeWithVal(ADDOP, SUB); SET_LINE(t, yylineno); $$ = t; }
                ;

term            : factor
                 {
                    tree *n = maketree(TERM);
                    SET_LINE(n, $1->lineno);
                    addChild(n, $1);
                    $$ = n;
                 }
                | term mulop factor
                 {
                    tree *n = maketree(TERM);
                    SET_LINE(n, $1->lineno);
                    addChild(n, $1);
                    addChild(n, $2);
                    addChild(n, $3);
                    $$ = n;
                 }
                ;

mulop           : OPER_MUL { tree *t = maketreeWithVal(MULOP, MUL); SET_LINE(t, yylineno); $$ = t; }
                | OPER_DIV { tree *t = maketreeWithVal(MULOP, DIV); SET_LINE(t, yylineno); $$ = t; }
                ;

factor          : LPAREN expression RPAREN
                 {
                    tree *n = maketree(FACTOR);
                    SET_LINE(n, yylineno);
                    addChild(n, $2);
                    $$ = n;
                 }
                | var
                 {
                    tree *n = maketree(FACTOR);
                    SET_LINE(n, $1->lineno);
                    addChild(n, $1);
                    $$ = n;
                 }
                | funCallExpr
                 {
                    tree *n = maketree(FACTOR);
                    SET_LINE(n, $1->lineno);
                    addChild(n, $1);
                    $$ = n;
                 }
                | INTCONST
                 {
                    tree *n = maketree(FACTOR);
                    SET_LINE(n, yylineno);
                    tree *ic = maketreeWithVal(INTEGER, $1);
                    SET_LINE(ic, yylineno);
                    addChild(n, ic);
                    $$ = n;
                 }
                | CHARCONST
                 {
                    tree *n = maketree(FACTOR);
                    SET_LINE(n, yylineno);
                    tree *cc = maketreeWithVal(CHAR, $1);
                    SET_LINE(cc, yylineno);
                    addChild(n, cc);
                    $$ = n;
                 }
                ;

var             : ID
                 {
                    int idx = lookup_var($1.text);
                    tree *n = maketree(VAR);
                    SET_LINE(n, $1.line);
                    tree *idn = maketreeWithVal(IDENTIFIER, idx);
                    SET_LINE(idn, $1.line);
                    addChild(n, idn);
                    $$ = n;
                 }
                | ID LSQ_BRKT addExpr RSQ_BRKT
                 {
                    int idx = lookup_var($1.text);
                    tree *n = maketree(VAR);
                    SET_LINE(n, $1.line);
                    tree *idn = maketreeWithVal(IDENTIFIER, idx);
                    SET_LINE(idn, $1.line);
                    addChild(n, idn);
                    addChild(n, $3);
                    $$ = n;
                 }
                ;

funCallExpr     : ID LPAREN RPAREN
                 {
                    int idx = lookup_fun($1.text);
                    tree *n = maketree(FUNCCALLEXPR);
                    SET_LINE(n, $1.line);
                    tree *idn = maketreeWithVal(IDENTIFIER, idx);
                    SET_LINE(idn, $1.line);
                    addChild(n, idn);
                    $$ = n;
                 }
                | ID LPAREN argList RPAREN
                 {
                    int idx = lookup_fun($1.text);
                    tree *n = maketree(FUNCCALLEXPR);
                    SET_LINE(n, $1.line);
                    tree *idn = maketreeWithVal(IDENTIFIER, idx);
                    SET_LINE(idn, $1.line);
                    addChild(n, idn);
                    addChild(n, $3);
                    $$ = n;
                 }
                ;

argList         : expression
                 {
                    tree *n = maketree(ARGLIST);
                    SET_LINE(n, $1->lineno);
                    addChild(n, $1);
                    $$ = n;
                 }
                | argList COMMA expression
                 {
                    tree *n = maketree(ARGLIST);
                    SET_LINE(n, $1->lineno);
                    addChild(n, $1);
                    addChild(n, $3);
                    $$ = n;
                 }
                ;

%%

int yywarning(char *msg){
  printf("warning: line %d: %s\n", yylineno, msg);
  return 0;
}

int yyerror(char * msg){
  printf("error: line %d: %s\n", yylineno, msg);
  return 0;
}
