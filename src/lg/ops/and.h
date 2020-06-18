#ifndef LG_OPS_AND_H
#define LG_OPS_AND_H

#include <stddef.h>

struct lg_op;
struct lg_vm;

struct lg_and {
  size_t nops;
};

struct lg_op *lg_and_eval(struct lg_op *op, struct lg_vm *vm);

#endif
