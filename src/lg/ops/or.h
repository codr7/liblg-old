#ifndef LG_OPS_OR_H
#define LG_OPS_OR_H

#include <stddef.h>

struct lg_op;
struct lg_vm;

struct lg_or {
  size_t nops;
};

struct lg_op *lg_or_eval(struct lg_op *op, struct lg_vm *vm);

#endif
