#include "lg/block.h"
#include "lg/op.h"
#include "lg/stack.h"
#include "lg/vm.h"

static void deinit_ops(struct lg_block *block) {
  lg_block_do(block, op) {
    lg_op_deinit(op);
  }
}

struct lg_block *lg_block_init(struct lg_block *block) {
  lg_slab_init(&block->ops);
  return block;
}

void lg_block_deinit(struct lg_block *block) {
  deinit_ops(block);
  lg_slab_deinit(&block->ops);
}

struct lg_op *lg_block_start(struct lg_block *block) {
  return (struct lg_op *)block->ops.slots;
}

size_t lg_block_len(struct lg_block *block) {
  return block->ops.len;
}

void lg_block_clear(struct lg_block *block) {
  deinit_ops(block);
  lg_slab_clear(&block->ops);
}

void lg_block_reverse(struct lg_block *block, size_t offs) {
  for (struct lg_op
	 *i = (struct lg_op *)block->ops.slots + offs,
	 *j = (struct lg_op *)block->ops.slots + lg_block_len(block) - 1;
       i < j;
       i++, j--) {
    struct lg_op tmp = *i;
    *i = *j;
    *j = tmp;
  }
}

struct lg_op *lg_emit(struct lg_block *block, struct lg_pos pos, enum lg_op_type type) {
  return lg_op_init(lg_slab_push(&block->ops, sizeof(struct lg_op)), pos, type);
}

bool lg_eval(struct lg_op *start, struct lg_vm *vm) {
  for (struct lg_op *op = start; op; op = lg_op_eval(op, vm));
  return !lg_stack_len(&vm->errors);
}
