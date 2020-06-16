#include <stdio.h>
#include <stdlib.h>

#include "lg/op.h"
#include "lg/stack.h"
#include "lg/vm.h"

struct lg_op *lg_op_init(struct lg_op *op, struct lg_pos pos, enum lg_op_type type) {
  lg_pos_copy(&pos, &op->pos);
  op->type = type;
  return op;
}

void lg_op_deinit(struct lg_op *op) {
  switch (op->type) {
  case LG_PUSH:
    lg_push_deinit(op);
    break;
  default:
    break;
  }

  lg_pos_deinit(&op->pos);
}

struct lg_op *lg_op_eval(struct lg_op *op, struct lg_vm *vm) {
  switch (op->type) {
  case LG_OR:
    return lg_or_eval(op, vm);
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
    return NULL;
  default:
    fprintf(stderr, "Eval not implemented for op type: %d", op->type);
    abort();
  }

  return op + 1;
}

