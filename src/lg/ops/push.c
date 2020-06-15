#include "lg/op.h"
#include "lg/ops/push.h"
#include "lg/vm.h"

bool lg_push_eval(struct lg_op *op, struct lg_vm *vm) {
  lg_clone(&op->as_push.val, lg_push(vm->stack));
  return true;
}

void lg_push_deinit(struct lg_op *op) {
  lg_deref(&op->as_push.val);
}

