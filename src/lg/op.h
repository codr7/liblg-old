#ifndef LG_OP_H
#define LG_OP_H

#include "lg/ops/push.h"
#include "lg/pos.h"

enum lg_op_type {LG_PUSH, LG_STOP};

struct lg_op {
  enum lg_op_type type;
  struct lg_pos pos;
  
  union {
    struct lg_push as_push;
  };
};

struct lg_op *lg_op_init(struct lg_op *op, enum lg_op_type type, struct lg_pos pos);
void lg_op_deinit(struct lg_op *op);

bool lg_op_eval(struct lg_op *op, struct lg_stack *stack);

#endif
