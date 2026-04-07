%{
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

%}

%union
{
    int value;
    struct treenode *node;
    char *strval;
}

/* Token codes must match src/tokendef.h and scanner.l returns. */
%token <strval> ID 251
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
                    addChild(progNode, $1);
                    ast = progNode;
                 }
                ;

declList        : decl
                 {
                    tree* declListNode = maketree(DECLLIST);
                    addChild(declListNode, $1);
                    $$ = declListNode;
                 }
                | declList decl
                 {
                    tree* declListNode = maketree(DECLLIST);
                    addChild(declListNode, $1);
                    addChild(declListNode, $2);
                    $$ = declListNode;
                 }
                ;

decl            : varDecl
                 {
                    tree *n = maketree(DECL);
                    addChild(n, $1);
                    $$ = n;
                 }
                | funDecl
                 {
                    tree *n = maketree(DECL);
                    addChild(n, $1);
                    $$ = n;
                 }
                ;

typeSpecifier   : KWD_INT
                 { $$ = maketreeWithVal(TYPESPEC, INT_TYPE); }
                | KWD_CHAR
                 { $$ = maketreeWithVal(TYPESPEC, CHAR_TYPE); }
                | KWD_VOID
                 { $$ = maketreeWithVal(TYPESPEC, VOID_TYPE); }
                ;

varDecl         : typeSpecifier ID SEMICLN
                 {
                    int idx = ST_insert($2, $1->val, SCALAR, NULL);
                    tree *n = maketree(VARDECL);
                    addChild(n, $1);
                    addChild(n, maketreeWithVal(IDENTIFIER, idx));
                    $$ = n;
                 }
                | typeSpecifier ID LSQ_BRKT INTCONST RSQ_BRKT SEMICLN
                 {
                    int idx = ST_insert($2, $1->val, ARRAY, NULL);
                    tree *n = maketree(VARDECL);
                    addChild(n, $1);
                    addChild(n, maketreeWithVal(IDENTIFIER, idx));
                    addChild(n, maketreeWithVal(INTEGER, $4));
                    $$ = n;
                 }
                ;

funcTypeName    : typeSpecifier ID
                 {
                    int idx = ST_insert($2, $1->val, FUNCTION, NULL);
                    tree *n = maketree(FUNCTYPENAME);
                    addChild(n, $1);
                    addChild(n, maketreeWithVal(IDENTIFIER, idx));
                    scope = strTable[idx].id;
                    $$ = n;
                 }
                ;

formalDeclList  : formalDecl
                 {
                    tree *n = maketree(FORMALDECLLIST);
                    addChild(n, $1);
                    $$ = n;
                 }
                | formalDecl COMMA formalDeclList
                 {
                    tree *n = maketree(FORMALDECLLIST);
                    addChild(n, $1);
                    addChild(n, $3);
                    $$ = n;
                 }
                ;

formalDecl      : typeSpecifier ID
                 {
                    int idx = ST_insert($2, $1->val, SCALAR, NULL);
                    tree *n = maketree(FORMALDECL);
                    addChild(n, $1);
                    addChild(n, maketreeWithVal(IDENTIFIER, idx));
                    $$ = n;
                 }
                | typeSpecifier ID LSQ_BRKT RSQ_BRKT
                 {
                    int idx = ST_insert($2, $1->val, ARRAY, NULL);
                    tree *n = maketree(FORMALDECL);
                    addChild(n, $1);
                    addChild(n, maketreeWithVal(IDENTIFIER, idx));
                    addChild(n, maketree(ARRAYDECL));
                    $$ = n;
                 }
                ;

funDecl         : funcTypeName LPAREN formalDeclList RPAREN LCRLY_BRKT localDeclList statementList RCRLY_BRKT
                 {
                    tree *n = maketree(FUNDECL);
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
                    tree *n = maketree(FUNDECL);
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
                      addChild(n, $1);
                      addChild(n, $2);
                      $$ = n;
                    } else {
                      tree *n = maketree(LOCALDECLLIST);
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
                      addChild(n, $1);
                      addChild(n, $2);
                      $$ = n;
                    } else {
                      tree *n = maketree(STATEMENTLIST);
                      addChild(n, $1);
                      $$ = n;
                    }
                 }
                ;

statement       : compoundStmt
                 { tree *n = maketree(STATEMENT); addChild(n, $1); $$ = n; }
                | assignStmt
                 { tree *n = maketree(STATEMENT); addChild(n, $1); $$ = n; }
                | condStmt
                 { tree *n = maketree(STATEMENT); addChild(n, $1); $$ = n; }
                | loopStmt
                 { tree *n = maketree(STATEMENT); addChild(n, $1); $$ = n; }
                | returnStmt
                 { tree *n = maketree(STATEMENT); addChild(n, $1); $$ = n; }
                ;

compoundStmt    : LCRLY_BRKT statementList RCRLY_BRKT
                 {
                    tree *n = maketree(COMPOUNDSTMT);
                    addChild(n, $2);
                    $$ = n;
                 }
                ;

assignStmt      : var OPER_ASGN expression SEMICLN
                 {
                    tree *n = maketree(ASSIGNSTMT);
                    addChild(n, $1);
                    addChild(n, $3);
                    $$ = n;
                 }
                | expression SEMICLN
                 {
                    tree *n = maketree(ASSIGNSTMT);
                    addChild(n, $1);
                    $$ = n;
                 }
                ;

condStmt        : KWD_IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE
                 {
                    tree *n = maketree(CONDSTMT);
                    addChild(n, $3);
                    addChild(n, $5);
                    $$ = n;
                 }
                | KWD_IF LPAREN expression RPAREN statement KWD_ELSE statement
                 {
                    tree *n = maketree(CONDSTMT);
                    addChild(n, $3);
                    addChild(n, $5);
                    addChild(n, $7);
                    $$ = n;
                 }
                ;

loopStmt        : KWD_WHILE LPAREN expression RPAREN statement
                 {
                    tree *n = maketree(LOOPSTMT);
                    addChild(n, $3);
                    addChild(n, $5);
                    $$ = n;
                 }
                ;

returnStmt      : KWD_RETURN SEMICLN
                 { $$ = maketree(RETURNSTMT); }
                | KWD_RETURN expression SEMICLN
                 {
                    tree *n = maketree(RETURNSTMT);
                    addChild(n, $2);
                    $$ = n;
                 }
                ;

expression      : addExpr
                 {
                    tree *n = maketree(EXPRESSION);
                    addChild(n, $1);
                    $$ = n;
                 }
                | expression relop addExpr
                 {
                    tree *n = maketree(EXPRESSION);
                    addChild(n, $1);
                    addChild(n, $2);
                    addChild(n, $3);
                    $$ = n;
                 }
                ;

relop           : OPER_LTE { $$ = maketreeWithVal(RELOP, LTE); }
                | OPER_LT  { $$ = maketreeWithVal(RELOP, LT); }
                | OPER_GT  { $$ = maketreeWithVal(RELOP, GT); }
                | OPER_GTE { $$ = maketreeWithVal(RELOP, GTE); }
                | OPER_EQ  { $$ = maketreeWithVal(RELOP, EQ); }
                | OPER_NEQ { $$ = maketreeWithVal(RELOP, NEQ); }
                ;

addExpr         : term
                 {
                    tree *n = maketree(ADDEXPR);
                    addChild(n, $1);
                    $$ = n;
                 }
                | addExpr addop term
                 {
                    tree *n = maketree(ADDEXPR);
                    addChild(n, $1);
                    addChild(n, $2);
                    addChild(n, $3);
                    $$ = n;
                 }
                ;

addop           : OPER_ADD { $$ = maketreeWithVal(ADDOP, ADD); }
                | OPER_SUB { $$ = maketreeWithVal(ADDOP, SUB); }
                ;

term            : factor
                 {
                    tree *n = maketree(TERM);
                    addChild(n, $1);
                    $$ = n;
                 }
                | term mulop factor
                 {
                    tree *n = maketree(TERM);
                    addChild(n, $1);
                    addChild(n, $2);
                    addChild(n, $3);
                    $$ = n;
                 }
                ;

mulop           : OPER_MUL { $$ = maketreeWithVal(MULOP, MUL); }
                | OPER_DIV { $$ = maketreeWithVal(MULOP, DIV); }
                ;

factor          : LPAREN expression RPAREN
                 {
                    tree *n = maketree(FACTOR);
                    addChild(n, $2);
                    $$ = n;
                 }
                | var
                 {
                    tree *n = maketree(FACTOR);
                    addChild(n, $1);
                    $$ = n;
                 }
                | funCallExpr
                 {
                    tree *n = maketree(FACTOR);
                    addChild(n, $1);
                    $$ = n;
                 }
                | INTCONST
                 {
                    tree *n = maketree(FACTOR);
                    addChild(n, maketreeWithVal(INTEGER, $1));
                    $$ = n;
                 }
                | CHARCONST
                 {
                    tree *n = maketree(FACTOR);
                    addChild(n, maketreeWithVal(CHAR, $1));
                    $$ = n;
                 }
                ;

var             : ID
                 {
                    int idx = lookup_var($1);
                    tree *n = maketree(VAR);
                    addChild(n, maketreeWithVal(IDENTIFIER, idx));
                    $$ = n;
                 }
                | ID LSQ_BRKT addExpr RSQ_BRKT
                 {
                    int idx = lookup_var($1);
                    tree *n = maketree(VAR);
                    addChild(n, maketreeWithVal(IDENTIFIER, idx));
                    addChild(n, $3);
                    $$ = n;
                 }
                ;

funCallExpr     : ID LPAREN RPAREN
                 {
                    int idx = lookup_fun($1);
                    tree *n = maketree(FUNCCALLEXPR);
                    addChild(n, maketreeWithVal(IDENTIFIER, idx));
                    $$ = n;
                 }
                | ID LPAREN argList RPAREN
                 {
                    int idx = lookup_fun($1);
                    tree *n = maketree(FUNCCALLEXPR);
                    addChild(n, maketreeWithVal(IDENTIFIER, idx));
                    addChild(n, $3);
                    $$ = n;
                 }
                ;

argList         : expression
                 {
                    tree *n = maketree(ARGLIST);
                    addChild(n, $1);
                    $$ = n;
                 }
                | argList COMMA expression
                 {
                    tree *n = maketree(ARGLIST);
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
