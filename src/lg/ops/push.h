#ifndef LG_OPS_PUSH_H
#define LG_OPS_PUSH_H

#include "lg/val.h"

struct lg_op;

struct lg_push {
  struct lg_val val;
};

struct lg_op *lg_push_eval(struct lg_op *op, struct lg_vm *vm);
void lg_push_deinit(struct lg_op *op);

#endif
