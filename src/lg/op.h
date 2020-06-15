#ifndef LG_OP_H
#define LG_OP_H

#include "lg/ops/push.h"
#include "lg/pos.h"

enum lg_op_type {LG_POP_STACK, LG_PUSH, LG_PUSH_STACK, LG_STOP};

struct lg_op {
  struct lg_pos pos;
  enum lg_op_type type;
  
  union {
    struct lg_push as_push;
  };
};

struct lg_op *lg_op_init(struct lg_op *op, struct lg_pos pos, enum lg_op_type type);
void lg_op_deinit(struct lg_op *op);

bool lg_op_eval(struct lg_op *op, struct lg_vm *vm);

#endif
