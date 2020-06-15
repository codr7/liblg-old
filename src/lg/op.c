#include <stdio.h>
#include <stdlib.h>

#include "lg/op.h"
#include "lg/stack.h"
#include "lg/vm.h"

struct lg_op *lg_op_init(struct lg_op *op, enum lg_op_type type, struct lg_pos pos) {
  op->type = type;
  lg_pos_copy(&pos, &op->pos);
  return op;
}

void lg_op_deinit(struct lg_op *op) {
  lg_pos_deinit(&op->pos);
}

bool lg_op_eval(struct lg_op *op, struct lg_vm *vm) {
  switch (op->type) {
  case LG_POP_STACK:
    lg_stack_deref(vm->stack);
    vm->stack = vm->stack->parent;
    break;
  case LG_PUSH:
    return lg_push_eval(op, vm);
  case LG_PUSH_STACK:
    vm->stack = lg_stack_new(vm->stack);
    break;
  case LG_STOP:
    return false;
  default:
    fprintf(stderr, "Eval not implemented for op type: %d", op->type);
    abort();
  }

  return true;
}

