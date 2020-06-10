#include <stdio.h>
#include <stdlib.h>

#include "lg/op.h"

struct lg_op *lg_op_init(struct lg_op *op, enum lg_op_type type, struct lg_pos pos) {
  op->type = type;
  lg_pos_copy(&pos, &op->pos);
  return op;
}

void lg_op_deinit(struct lg_op *op) {
  lg_pos_deinit(&op->pos);
}

bool lg_op_eval(struct lg_op *op, struct lg_stack *stack) {
  switch (op->type) {
  case LG_PUSH:
    return lg_push_eval(op, stack);
  case LG_STOP:
    return false;
  default:
    fprintf(stderr, "Eval not implemented for op type: %d", op->type);
    abort();
  }
}

