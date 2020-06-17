#ifndef LG_REPL_H
#define LG_REPL_H

#include <stdio.h>

struct lg_vm;

void lg_repl(struct lg_vm *vm, FILE *in, FILE *out);

#endif
