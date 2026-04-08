#include "codegen.h"
#include "strtab.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern struct strEntry strTable[MAXIDS];

int codegen_enabled = 0;

enum {
  NK_PROGRAM = 0,
  NK_DECLLIST, NK_DECL, NK_VARDECL, NK_TYPESPEC, NK_FUNDECL,
  NK_FORMALDECLLIST, NK_FORMALDECL, NK_FUNBODY, NK_LOCALDECLLIST,
  NK_STATEMENTLIST, NK_STATEMENT, NK_COMPOUNDSTMT, NK_ASSIGNSTMT,
  NK_CONDSTMT, NK_LOOPSTMT, NK_RETURNSTMT, NK_EXPRESSION, NK_RELOP,
  NK_ADDEXPR, NK_ADDOP, NK_TERM, NK_MULOP, NK_FACTOR, NK_FUNCCALLEXPR,
  NK_ARGLIST, NK_INTEGER, NK_IDENTIFIER, NK_VAR, NK_ARRAYDECL, NK_CHAR,
  NK_FUNCTYPENAME
};

static int temp_id;
static int label_id;

static symEntry *sym_at(int idx) {
  if (idx < 0 || idx >= MAXIDS || strTable[idx].id == NULL)
    return NULL;
  return (symEntry *)&strTable[idx];
}

static void mangle(int idx, char *buf, size_t bufsz) {
  symEntry *e = sym_at(idx);
  if (!e) {
    snprintf(buf, bufsz, "_undef");
    return;
  }
  if (e->scope && e->scope[0])
    snprintf(buf, bufsz, "%s_%s", e->scope, e->id);
  else
    snprintf(buf, bufsz, "%s", e->id);
}

static void emit(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  vprintf(fmt, ap);
  va_end(ap);
  printf("\n");
}

static void new_temp(char *buf, size_t n) {
  snprintf(buf, n, "t%d", temp_id++);
}

static void new_label(char *buf, size_t n) {
  snprintf(buf, n, "L%d", label_id++);
}

static const char *relop_str(int v) {
  switch (v) {
  case 4: return "<";
  case 5: return "<=";
  case 6: return "==";
  case 7: return ">=";
  case 8: return ">";
  case 9: return "!=";
  default: return "?";
  }
}

static const char *addop_str(int v) { return v == 0 ? "+" : "-"; }
static const char *mulop_str(int v) { return v == 0 ? "*" : "/"; }

static void gather_args(tree *al, tree **out, int *cnt, int max);

static void gen_add_expr(tree *ae, char *out, size_t outsz);
static void gen_term(tree *tm, char *out, size_t outsz);
static void gen_factor(tree *fc, char *out, size_t outsz);
static void gen_expr(tree *ex, char *out, size_t outsz);
static void gen_stmt(tree *st);
static void gen_stmt_list(tree *sl);
static void gen_fun_body(tree *fb);

static void gather_args(tree *al, tree **out, int *cnt, int max) {
  if (!al || al->nodeKind != NK_ARGLIST || *cnt >= max) return;
  if (al->numChildren == 1) {
    out[(*cnt)++] = al->children[0];
    return;
  }
  gather_args(al->children[0], out, cnt, max);
  if (*cnt < max)
    out[(*cnt)++] = al->children[1];
}

static void gen_factor(tree *fc, char *out, size_t outsz) {
  if (!fc || fc->nodeKind != NK_FACTOR || fc->numChildren < 1) {
    snprintf(out, outsz, "t0");
    return;
  }
  tree *c = fc->children[0];
  if (c->nodeKind == NK_INTEGER) {
    new_temp(out, outsz);
    emit("  %s = %d", out, c->val);
    return;
  }
  if (c->nodeKind == NK_CHAR) {
    new_temp(out, outsz);
    emit("  %s = %d", out, c->val);
    return;
  }
  if (c->nodeKind == NK_VAR) {
    tree *idn = c->children[0];
    char name[256];
    mangle(idn->val, name, sizeof name);
    if (c->numChildren == 1) {
      symEntry *e = sym_at(idn->val);
      if (e && e->symbol_type == ARRAY) {
        new_temp(out, outsz);
        emit("  %s = &%s", out, name);
        return;
      }
      snprintf(out, outsz, "%s", name);
      return;
    }
    char ix[64];
    gen_add_expr(c->children[1], ix, sizeof ix);
    new_temp(out, outsz);
    emit("  %s = %s[%s]", out, name, ix);
    return;
  }
  if (c->nodeKind == NK_EXPRESSION) {
    gen_expr(c, out, outsz);
    return;
  }
  if (c->nodeKind == NK_FUNCCALLEXPR) {
    tree *id = c->children[0];
    char fname[256];
    mangle(id->val, fname, sizeof fname);
    tree *args[64];
    int n = 0;
    if (c->numChildren >= 2)
      gather_args(c->children[1], args, &n, 64);
    char parts[64][64];
    for (int i = 0; i < n; i++) {
      gen_expr(args[i], parts[i], sizeof parts[i]);
    }
    new_temp(out, outsz);
    printf("  %s = call %s", out, fname);
    for (int i = 0; i < n; i++)
      printf(" %s", parts[i]);
    printf("\n");
    return;
  }
  new_temp(out, outsz);
  emit("  %s = 0", out);
}

static void gen_term(tree *tm, char *out, size_t outsz) {
  if (!tm || tm->nodeKind != NK_TERM) {
    snprintf(out, outsz, "t0");
    return;
  }
  if (tm->numChildren == 1) {
    gen_factor(tm->children[0], out, outsz);
    return;
  }
  char a[64], b[64];
  gen_term(tm->children[0], a, sizeof a);
  gen_factor(tm->children[2], b, sizeof b);
  new_temp(out, outsz);
  emit("  %s = %s %s %s", out, a, mulop_str(tm->children[1]->val), b);
}

static void gen_add_expr(tree *ae, char *out, size_t outsz) {
  if (!ae || ae->nodeKind != NK_ADDEXPR) {
    snprintf(out, outsz, "t0");
    return;
  }
  if (ae->numChildren == 1) {
    gen_term(ae->children[0], out, outsz);
    return;
  }
  char a[64], b[64];
  gen_add_expr(ae->children[0], a, sizeof a);
  gen_term(ae->children[2], b, sizeof b);
  new_temp(out, outsz);
  emit("  %s = %s %s %s", out, a, addop_str(ae->children[1]->val), b);
}

static void gen_expr(tree *ex, char *out, size_t outsz) {
  if (!ex || ex->nodeKind != NK_EXPRESSION) {
    snprintf(out, outsz, "t0");
    return;
  }
  if (ex->numChildren == 1) {
    gen_add_expr(ex->children[0], out, outsz);
    return;
  }
  if (ex->numChildren == 3) {
    char a[64], b[64];
    gen_add_expr(ex->children[0], a, sizeof a);
    gen_add_expr(ex->children[2], b, sizeof b);
    new_temp(out, outsz);
    emit("  %s = (%s %s %s)", out, a, relop_str(ex->children[1]->val), b);
    return;
  }
  snprintf(out, outsz, "t0");
}

static void gen_assign(tree *st) {
  if (!st || st->nodeKind != NK_ASSIGNSTMT) return;
  if (st->numChildren == 1) {
    char t[64];
    gen_expr(st->children[0], t, sizeof t);
    emit("  // expr stmt (result in %s)", t);
    return;
  }
  tree *lhs = st->children[0];
  tree *rhs = st->children[1];
  char rv[64];
  gen_expr(rhs, rv, sizeof rv);
  if (lhs->nodeKind != NK_VAR) return;
  tree *lid = lhs->children[0];
  char name[256];
  mangle(lid->val, name, sizeof name);
  if (lhs->numChildren == 1) {
    symEntry *e = sym_at(lid->val);
    if (e && e->symbol_type == ARRAY) {
      emit("  // assign to array name %s (address)", name);
      return;
    }
    emit("  %s = %s", name, rv);
    return;
  }
  char ix[64];
  gen_add_expr(lhs->children[1], ix, sizeof ix);
  emit("  %s[%s] = %s", name, ix, rv);
}

static void gen_stmt(tree *st) {
  if (!st || st->nodeKind != NK_STATEMENT) return;
  tree *in = st->children[0];
  if (!in) return;
  switch (in->nodeKind) {
  case NK_ASSIGNSTMT:
    gen_assign(in);
    break;
  case NK_COMPOUNDSTMT:
    if (in->numChildren >= 1)
      gen_stmt_list(in->children[0]);
    break;
  case NK_CONDSTMT: {
    char tc[64];
    gen_expr(in->children[0], tc, sizeof tc);
    char Lelse[32], Lend[32];
    new_label(Lelse, sizeof Lelse);
    new_label(Lend, sizeof Lend);
    if (in->numChildren == 3) {
      emit("  if_false %s goto %s", tc, Lelse);
      gen_stmt(in->children[1]);
      emit("  goto %s", Lend);
      emit("%s:", Lelse);
      gen_stmt(in->children[2]);
      emit("%s:", Lend);
    } else {
      emit("  if_false %s goto %s", tc, Lend);
      gen_stmt(in->children[1]);
      emit("%s:", Lend);
    }
    break;
  }
  case NK_LOOPSTMT: {
    char Ltop[32], Lend[32];
    new_label(Ltop, sizeof Ltop);
    new_label(Lend, sizeof Lend);
    emit("%s:", Ltop);
    char tc[64];
    gen_expr(in->children[0], tc, sizeof tc);
    emit("  if_false %s goto %s", tc, Lend);
    gen_stmt(in->children[1]);
    emit("  goto %s", Ltop);
    emit("%s:", Lend);
    break;
  }
  case NK_RETURNSTMT:
    if (in->numChildren == 0)
      emit("  return");
    else {
      char t[64];
      gen_expr(in->children[0], t, sizeof t);
      emit("  return %s", t);
    }
    break;
  default:
    break;
  }
}

static void gen_stmt_list(tree *sl) {
  if (!sl || sl->nodeKind != NK_STATEMENTLIST) return;
  if (sl->numChildren == 1) {
    gen_stmt(sl->children[0]);
    return;
  }
  gen_stmt(sl->children[0]);
  gen_stmt_list(sl->children[1]);
}

static void emit_global_comment(tree *vd) {
  if (!vd || vd->nodeKind != NK_VARDECL) return;
  tree *idn = vd->children[1];
  char name[256];
  mangle(idn->val, name, sizeof name);
  symEntry *e = sym_at(idn->val);
  if (!e) return;
  static const char *dts[] = {"int", "char", "void"};
  if (e->symbol_type == ARRAY && vd->numChildren >= 3)
    emit("// global %s %s[%d]", dts[e->data_type], name, vd->children[2]->val);
  else if (e->symbol_type == ARRAY)
    emit("// global %s %s[]", dts[e->data_type], name);
  else
    emit("// global %s %s", dts[e->data_type], name);
}

static void walk_globals(tree *dl);

static void walk_globals(tree *dl) {
  if (!dl || dl->nodeKind != NK_DECLLIST) return;
  if (dl->numChildren == 1) {
    tree *d = dl->children[0];
    if (d && d->nodeKind == NK_DECL && d->numChildren >= 1) {
      tree *inner = d->children[0];
      if (inner->nodeKind == NK_VARDECL)
        emit_global_comment(inner);
    }
    return;
  }
  walk_globals(dl->children[0]);
  tree *d = dl->children[1];
  if (d && d->nodeKind == NK_DECL && d->numChildren >= 1) {
    tree *inner = d->children[0];
    if (inner->nodeKind == NK_VARDECL)
      emit_global_comment(inner);
  }
}

static void gen_fun(tree *fd) {
  if (!fd || fd->nodeKind != NK_FUNDECL) return;
  tree *ftn = fd->children[0];
  tree *idn = ftn->children[1];
  char fname[256];
  mangle(idn->val, fname, sizeof fname);
  emit("function %s:", fname);
  tree *fb = NULL;
  if (fd->numChildren == 3)
    fb = fd->children[2];
  else if (fd->numChildren == 2)
    fb = fd->children[1];
  if (fb)
    gen_fun_body(fb);
  emit("");
}

static void gen_fun_body(tree *fb) {
  if (!fb || fb->nodeKind != NK_FUNBODY) return;
  if (fb->numChildren >= 2)
    gen_stmt_list(fb->children[1]);
}

static void walk_functions(tree *dl);

static void walk_functions(tree *dl) {
  if (!dl || dl->nodeKind != NK_DECLLIST) return;
  if (dl->numChildren == 1) {
    tree *d = dl->children[0];
    if (d && d->nodeKind == NK_DECL && d->numChildren >= 1) {
      tree *inner = d->children[0];
      if (inner->nodeKind == NK_FUNDECL)
        gen_fun(inner);
    }
    return;
  }
  walk_functions(dl->children[0]);
  tree *d = dl->children[1];
  if (d && d->nodeKind == NK_DECL && d->numChildren >= 1) {
    tree *inner = d->children[0];
    if (inner->nodeKind == NK_FUNDECL)
      gen_fun(inner);
  }
}

void codegen_generate(tree *root) {
  if (!codegen_enabled || !root || root->nodeKind != NK_PROGRAM)
    return;
  temp_id = 0;
  label_id = 0;
  if (root->numChildren < 1) return;
  tree *dl = root->children[0];
  emit("# three-address code");
  walk_globals(dl);
  emit("");
  walk_functions(dl);
}
