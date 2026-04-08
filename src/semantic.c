#include "semantic.h"
#include "tree.h"
#include "strtab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern struct strEntry strTable[MAXIDS];

static int expr_type_expr(tree *ex);
static void check_var_for_errors(tree *v);
static void check_fun_call(tree *call);

enum {
  NK_PROGRAM, NK_DECLLIST, NK_DECL, NK_VARDECL, NK_TYPESPEC, NK_FUNDECL,
  NK_FORMALDECLLIST, NK_FORMALDECL, NK_FUNBODY, NK_LOCALDECLLIST,
  NK_STATEMENTLIST, NK_STATEMENT, NK_COMPOUNDSTMT, NK_ASSIGNSTMT,
  NK_CONDSTMT, NK_LOOPSTMT, NK_RETURNSTMT, NK_EXPRESSION, NK_RELOP,
  NK_ADDEXPR, NK_ADDOP, NK_TERM, NK_MULOP, NK_FACTOR, NK_FUNCCALLEXPR,
  NK_ARGLIST, NK_INTEGER, NK_IDENTIFIER, NK_VAR, NK_ARRAYDECL, NK_CHAR,
  NK_FUNCTYPENAME
};

#define TY_ERR (-1)

static void sem_err(int line, const char *msg) {
  if (line <= 0) line = 1;
  printf("error: line %d: %s\n", line, msg);
}

static int line_of(tree *n) {
  if (!n) return 1;
  return n->lineno > 0 ? n->lineno : 1;
}

static symEntry *sym_at(int idx) {
  if (idx < 0 || idx >= MAXIDS || strTable[idx].id == NULL)
    return NULL;
  return (symEntry *)&strTable[idx];
}

static int fold_addexpr(tree *ae, int *ok);
static int fold_term(tree *tm, int *ok);
static int fold_factor(tree *fc, int *ok);

static int fold_factor(tree *fc, int *ok) {
  *ok = 0;
  if (!fc || fc->nodeKind != NK_FACTOR || fc->numChildren != 1) return 0;
  tree *c = getChild(fc, 0);
  if (c->nodeKind == NK_INTEGER) {
    *ok = 1;
    return c->val;
  }
  if (c->nodeKind == NK_EXPRESSION)
    return fold_addexpr(getChild(c, 0), ok);
  return 0;
}

static int fold_term(tree *tm, int *ok) {
  *ok = 0;
  if (!tm || tm->nodeKind != NK_TERM) return 0;
  if (tm->numChildren == 1)
    return fold_factor(getChild(tm, 0), ok);
  if (tm->numChildren == 3) {
    int ok1 = 0, ok2 = 0;
    int a = fold_term(getChild(tm, 0), &ok1);
    int b = fold_factor(getChild(tm, 2), &ok2);
    if (!ok1 || !ok2) return 0;
    int opv = getChild(tm, 1)->val;
    *ok = 1;
    if (opv == 0) return a * b;
    if (b == 0) { *ok = 0; return 0; }
    return a / b;
  }
  return 0;
}

static int fold_addexpr(tree *ae, int *ok) {
  *ok = 0;
  if (!ae || ae->nodeKind != NK_ADDEXPR) return 0;
  if (ae->numChildren == 1)
    return fold_term(getChild(ae, 0), ok);
  if (ae->numChildren == 3) {
    int ok1 = 0, ok2 = 0;
    int a = fold_addexpr(getChild(ae, 0), &ok1);
    int b = fold_term(getChild(ae, 2), &ok2);
    if (!ok1 || !ok2) return 0;
    int opv = getChild(ae, 1)->val;
    *ok = 1;
    if (opv == 0) return a + b;
    return a - b;
  }
  return 0;
}

static void gather_args(tree *al, tree **out, int *cnt, int max) {
  if (!al || al->nodeKind != NK_ARGLIST || *cnt >= max) return;
  if (al->numChildren == 1) {
    out[(*cnt)++] = getChild(al, 0);
    return;
  }
  gather_args(getChild(al, 0), out, cnt, max);
  if (*cnt < max)
    out[(*cnt)++] = getChild(al, 1);
}

static tree *extract_simple_var(tree *argEx) {
  if (!argEx || argEx->nodeKind != NK_EXPRESSION || argEx->numChildren != 1)
    return NULL;
  tree *ae = getChild(argEx, 0);
  if (!ae || ae->nodeKind != NK_ADDEXPR || ae->numChildren != 1)
    return NULL;
  tree *tm = getChild(ae, 0);
  if (!tm || tm->nodeKind != NK_TERM || tm->numChildren != 1)
    return NULL;
  tree *fc = getChild(tm, 0);
  if (!fc || fc->nodeKind != NK_FACTOR || fc->numChildren != 1)
    return NULL;
  tree *v = getChild(fc, 0);
  if (v && v->nodeKind == NK_VAR) return v;
  return NULL;
}

static int expr_type_factor(tree *fc) {
  if (!fc || fc->nodeKind != NK_FACTOR || fc->numChildren < 1) return TY_ERR;
  tree *c = getChild(fc, 0);
  if (c->nodeKind == NK_INTEGER) return INT_TYPE;
  if (c->nodeKind == NK_CHAR) return CHAR_TYPE;
  if (c->nodeKind == NK_VAR) {
    check_var_for_errors(c);
    tree *idn = getChild(c, 0);
    symEntry *e = sym_at(idn->val);
    if (!e) return TY_ERR;
    if (c->numChildren == 1)
      return e->data_type;
    return e->data_type;
  }
  if (c->nodeKind == NK_EXPRESSION)
    return expr_type_expr(c);
  if (c->nodeKind == NK_FUNCCALLEXPR) {
    check_fun_call(c);
    tree *id = getChild(c, 0);
    symEntry *fn = sym_at(id->val);
    if (!fn || fn->symbol_type != FUNCTION) return TY_ERR;
    return fn->data_type;
  }
  return TY_ERR;
}

static int expr_type_term(tree *tm) {
  if (!tm || tm->nodeKind != NK_TERM) return TY_ERR;
  if (tm->numChildren == 1)
    return expr_type_factor(getChild(tm, 0));
  if (tm->numChildren == 3) {
    int a = expr_type_term(getChild(tm, 0));
    int b = expr_type_factor(getChild(tm, 2));
    if (a == TY_ERR || b == TY_ERR) return TY_ERR;
    if (a != b) return TY_ERR;
    return a;
  }
  return TY_ERR;
}

static int expr_type_addexpr(tree *ae) {
  if (!ae || ae->nodeKind != NK_ADDEXPR) return TY_ERR;
  if (ae->numChildren == 1)
    return expr_type_term(getChild(ae, 0));
  if (ae->numChildren == 3) {
    int a = expr_type_addexpr(getChild(ae, 0));
    int b = expr_type_term(getChild(ae, 2));
    if (a == TY_ERR || b == TY_ERR) return TY_ERR;
    if (a != b) return TY_ERR;
    return a;
  }
  return TY_ERR;
}

static int expr_type_expr(tree *ex) {
  if (!ex || ex->nodeKind != NK_EXPRESSION) return TY_ERR;
  if (ex->numChildren == 1)
    return expr_type_addexpr(getChild(ex, 0));
  if (ex->numChildren == 3) {
    expr_type_addexpr(getChild(ex, 0));
    expr_type_addexpr(getChild(ex, 2));
    return INT_TYPE;
  }
  return TY_ERR;
}

static int index_expr_type(tree *ix) {
  if (!ix) return TY_ERR;
  if (ix->nodeKind == NK_EXPRESSION)
    return expr_type_expr(ix);
  if (ix->nodeKind == NK_ADDEXPR)
    return expr_type_addexpr(ix);
  return TY_ERR;
}

static void check_index(tree *idxExpr, int line) {
  int t = index_expr_type(idxExpr);
  if (t != INT_TYPE)
    sem_err(line, "Array indexed using non-integer expression.");
}

static void check_var_for_errors(tree *v) {
  tree *idn = getChild(v, 0);
  int line = line_of(v);
  if (idn->val < 0) {
    sem_err(line_of(idn), "Undeclared variable");
    return;
  }
  symEntry *e = sym_at(idn->val);
  if (!e) return;
  if (v->numChildren == 2) {
    tree *ix = getChild(v, 1);
    if (e->symbol_type != ARRAY)
      sem_err(line, "Non-array identifier used as an array.");
    else {
      check_index(ix, line);
      int ok = 0;
      int folded = 0;
      if (ix->nodeKind == NK_ADDEXPR)
        folded = fold_addexpr(ix, &ok);
      else if (ix->nodeKind == NK_EXPRESSION && ix->numChildren >= 1)
        folded = fold_addexpr(getChild(ix, 0), &ok);
      if (ok && e->size > 0) {
        if (folded < 0 || folded >= e->size)
          sem_err(line,
            "Statically sized array indexed with constant, out-of-bounds expression.");
      }
    }
  }
}

static void check_fun_call(tree *call) {
  tree *idn = getChild(call, 0);
  int line = line_of(call);
  if (idn->val < 0) {
    sem_err(line_of(idn), "Undefined function");
    return;
  }
  symEntry *fn = sym_at(idn->val);
  if (!fn || fn->symbol_type != FUNCTION) return;

  tree *args[64];
  int n = 0;
  if (call->numChildren == 2)
    gather_args(getChild(call, 1), args, &n, 64);

  int need = fn->size;
  if (n < need) {
    sem_err(line, "Too few arguments provided in function call.");
    return;
  }
  if (n > need) {
    sem_err(line, "Too many arguments provided in function call.");
    return;
  }

  param *p = fn->params;
  for (int i = 0; i < n && p; i++) {
    tree *argEx = args[i];
    tree *vv = extract_simple_var(argEx);
    if (vv) {
      tree *vid = getChild(vv, 0);
      symEntry *asym = sym_at(vid->val);
      if (asym) {
        if (p->symbol_type == ARRAY) {
          if (asym->symbol_type == ARRAY && asym->data_type == p->data_type) {
            p = p->next;
            continue;
          }
          if (asym->symbol_type == SCALAR && asym->data_type == p->data_type) {
            p = p->next;
            continue;
          }
          sem_err(line, "Argument type mismatch in function call.");
          return;
        } else {
          if (asym->symbol_type == ARRAY || asym->data_type != p->data_type) {
            sem_err(line, "Argument type mismatch in function call.");
            return;
          }
        }
        p = p->next;
        continue;
      }
    }

    int at = expr_type_expr(argEx);
    if (p->symbol_type == SCALAR) {
      if (at != p->data_type || at == TY_ERR) {
        sem_err(line, "Argument type mismatch in function call.");
        return;
      }
    } else {
      sem_err(line, "Argument type mismatch in function call.");
      return;
    }
    p = p->next;
  }
}

static void check_assign(tree *st) {
  if (!st || st->nodeKind != NK_ASSIGNSTMT) return;
  int ln = line_of(st);
  if (st->numChildren == 1) {
    expr_type_expr(getChild(st, 0));
    return;
  }
  tree *lhs = getChild(st, 0);
  tree *rhs = getChild(st, 1);
  if (lhs->nodeKind != NK_VAR) return;
  check_var_for_errors(lhs);
  tree *lid = getChild(lhs, 0);
  symEntry *le = sym_at(lid->val);
  if (!le) return;
  if (le->symbol_type == ARRAY && lhs->numChildren == 1) {
    sem_err(ln, "Type mismatch in assignment.");
    return;
  }
  if (le->data_type == VOID_TYPE) {
    int rt0 = expr_type_expr(rhs);
    if (rt0 == VOID_TYPE)
      return;
    sem_err(ln, "Type mismatch in assignment.");
    return;
  }
  int rt = expr_type_expr(rhs);
  if (rt == TY_ERR || le->data_type != rt)
    sem_err(ln, "Type mismatch in assignment.");
}

static void walk_stmt(tree *st);

static void walk_stmt_list(tree *sl) {
  if (!sl || sl->nodeKind != NK_STATEMENTLIST) return;
  if (sl->numChildren == 1) {
    walk_stmt(getChild(sl, 0));
    return;
  }
  walk_stmt(getChild(sl, 0));
  walk_stmt_list(getChild(sl, 1));
}

static void walk_stmt(tree *st) {
  if (!st || st->nodeKind != NK_STATEMENT) return;
  tree *in = getChild(st, 0);
  if (!in) return;
  switch (in->nodeKind) {
  case NK_ASSIGNSTMT:
    check_assign(in);
    break;
  case NK_COMPOUNDSTMT:
    if (in->numChildren >= 1)
      walk_stmt_list(getChild(in, 0));
    break;
  case NK_CONDSTMT:
    if (in->numChildren >= 1)
      expr_type_expr(getChild(in, 0));
    if (in->numChildren >= 2)
      walk_stmt(getChild(in, 1));
    if (in->numChildren >= 3)
      walk_stmt(getChild(in, 2));
    break;
  case NK_LOOPSTMT:
    if (in->numChildren >= 1)
      expr_type_expr(getChild(in, 0));
    if (in->numChildren >= 2)
      walk_stmt(getChild(in, 1));
    break;
  case NK_RETURNSTMT:
    if (in->numChildren >= 1)
      expr_type_expr(getChild(in, 0));
    break;
  default:
    break;
  }
}

static void walk_fun_body(tree *fb) {
  if (!fb || fb->nodeKind != NK_FUNBODY) return;
  if (fb->numChildren >= 2)
    walk_stmt_list(getChild(fb, 1));
}

static void walk_decl(tree *d) {
  if (!d || d->nodeKind != NK_DECL) return;
  tree *ch = getChild(d, 0);
  if (!ch || ch->nodeKind != NK_FUNDECL) return;
  tree *fb = NULL;
  if (ch->numChildren == 3)
    fb = getChild(ch, 2);
  else if (ch->numChildren == 2)
    fb = getChild(ch, 1);
  if (fb)
    walk_fun_body(fb);
}

static void walk_decl_list(tree *dl) {
  if (!dl || dl->nodeKind != NK_DECLLIST) return;
  if (dl->numChildren == 1) {
    walk_decl(getChild(dl, 0));
    return;
  }
  walk_decl_list(getChild(dl, 0));
  walk_decl(getChild(dl, 1));
}

void semantic_analyze(tree *root) {
  if (!root || root->nodeKind != NK_PROGRAM) return;
  if (root->numChildren < 1) return;
  walk_decl_list(getChild(root, 0));
}
