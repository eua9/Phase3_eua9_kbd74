#ifndef CODEGEN_H
#define CODEGEN_H

#include "tree.h"

/* Set by driver when --code is passed; otherwise codegen_generate is a no-op. */
extern int codegen_enabled;

void codegen_generate(tree *root);

#endif
