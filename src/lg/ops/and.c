#include "lg/op.h"
#include "lg/ops/and.h"
#include "lg/vm.h"

struct lg_op *lg_and_eval(struct lg_op *op, struct lg_vm *vm) {
  struct lg_val *x = lg_peek(vm->stack);

  if (!lg_true(x)) {
    return op + op->as_and.nops + 1;
  }

  lg_pop(vm->stack);
  lg_deref(x);
  return op + 1;
}

