#include "lg/block.h"
#include "lg/op.h"

struct lg_block *lg_block_init(struct lg_block *block) {
  lg_slab_init(&block->ops);
  return block;
}

void lg_block_deinit(struct lg_block *block) {
  lg_block_do(block, op) {
    lg_op_deinit(op);
  }
  
  lg_slab_deinit(&block->ops);
}

struct lg_op *lg_block_start(struct lg_block *block) {
  return (struct lg_op *)block->ops.slots;
}

struct lg_op *lg_emit(struct lg_block *block, enum lg_op_type type, struct lg_pos pos) {
  return lg_op_init(lg_slab_push(&block->ops, sizeof(struct lg_op)), type, pos);
}

void lg_eval(struct lg_op *start, struct lg_vm *vm) {
  for (struct lg_op *op = start; true; op++) {
    if (!lg_op_eval(op, vm)) {
      break;
    }
  }
}
