#include "lg/op.h"
#include "lg/ops/push.h"
#include "lg/stack.h"

bool lg_push_eval(struct lg_op *op, struct lg_stack *stack) {
  lg_clone(&op->as_push.val, lg_push(stack));
  return true;
}
