#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "strtab.h"

param *working_list_head = NULL;
param *working_list_end = NULL;
table_node *current_scope = NULL;

struct strEntry strTable[MAXIDS];
extern char *scope;

void reset_formal_params(void) {
  param *p = working_list_head;
  while (p) {
    param *n = p->next;
    free(p);
    p = n;
  }
  working_list_head = working_list_end = NULL;
}

int hash(unsigned char *str) {
  unsigned long h = 5381;
  int c;
  while ((c = *str++))
    h += (h << 5) + c;
  return h % MAXIDS;
}

static int probe_find(char *id, const char *scopestr) {
  char keyBuf[512];
  const char *s = scopestr ? scopestr : "";
  snprintf(keyBuf, sizeof(keyBuf), "%s%s", s, id ? id : "");
  int idx = hash((unsigned char *)keyBuf);
  int start = idx;
  for (int i = 0; i < MAXIDS; i++) {
    if (strTable[idx].id == NULL)
      return -1;
    if (strcmp(strTable[idx].id, id ? id : "") == 0 &&
        strcmp(strTable[idx].scope, s) == 0)
      return idx;
    idx = (idx + 1) % MAXIDS;
  }
  return -1;
}

int ST_insert(char *id, int data_type, int symbol_type, int size, int *idx_out) {
  const char *s = scope ? scope : "";
  if (probe_find(id, s) >= 0)
    return -1;
  char keyBuf[512];
  snprintf(keyBuf, sizeof(keyBuf), "%s%s", s, id ? id : "");
  int idx = hash((unsigned char *)keyBuf);
  for (int i = 0; i < MAXIDS; i++) {
    if (strTable[idx].id == NULL) {
      strTable[idx].id = strdup(id ? id : "");
      strTable[idx].scope = strdup(s);
      strTable[idx].data_type = data_type;
      strTable[idx].symbol_type = symbol_type;
      strTable[idx].size = size;
      strTable[idx].params = NULL;
      if (idx_out) *idx_out = idx;
      return idx;
    }
    idx = (idx + 1) % MAXIDS;
  }
  return -1;
}

symEntry *ST_lookup(char *id) {
  int idx = probe_find(id, scope ? scope : "");
  if (idx < 0) idx = probe_find(id, "");
  if (idx < 0) return NULL;
  return (symEntry *)&strTable[idx];
}

symEntry *ST_lookup_global(char *id) {
  int idx = probe_find(id, "");
  if (idx < 0) return NULL;
  return (symEntry *)&strTable[idx];
}

void add_param(int data_type, int symbol_type) {
  param *p = (param *)malloc(sizeof(param));
  if (!p) return;
  p->data_type = data_type;
  p->symbol_type = symbol_type;
  p->next = NULL;
  if (!working_list_end)
    working_list_head = working_list_end = p;
  else {
    working_list_end->next = p;
    working_list_end = p;
  }
}

void connect_params(int i, int num_params) {
  (void)num_params;
  if (i < 0 || i >= MAXIDS) return;
  int n = 0;
  for (param *p = working_list_head; p; p = p->next) n++;
  strTable[i].params = working_list_head;
  strTable[i].size = n;
  working_list_head = working_list_end = NULL;
}

void new_scope(void) { }
void up_scope(void) { }

static const char *dataTypeStr[3] = {"int", "char", "void"};
static const char *symbolTypeStr[3] = {"", "[]", "()"};

char *get_symbol_id(int idx) {
  if (idx < 0 || idx >= MAXIDS || strTable[idx].id == NULL)
    return "";
  return strTable[idx].id;
}

static void output_entry(int i) {
  printf("%d: %s ", i, dataTypeStr[strTable[i].data_type]);
  printf("%s:%s%s\n",
    strTable[i].scope, strTable[i].id, symbolTypeStr[strTable[i].symbol_type]);
}

void print_sym_tab(void) {
  for (int i = 0; i < MAXIDS; i++)
    if (strTable[i].id != NULL)
      output_entry(i);
}
