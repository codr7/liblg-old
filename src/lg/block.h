#ifndef LG_BLOCK_H
#define LG_BLOCK_H

#include "lg/pos.h"
#include "lg/slab.h"
#include "lg/util.h"

#include <stdbool.h>

#define _lg_block_do(block, op, _i)					\
  size_t _i = 0;							\
  for (struct lg_op *op = (struct lg_op *)block->ops.slots;		\
       _i < block->ops.len;						\
       _i++, op++)

#define lg_block_do(block, op)			\
  _lg_block_do(block, op, lg_unique(i))

enum lg_op_type;
struct lg_vm;

struct lg_block {
  struct lg_slab ops;
};

struct lg_block *lg_block_init(struct lg_block *block);
void lg_block_deinit(struct lg_block *block);
struct lg_op *lg_block_start(struct lg_block *block);

struct lg_op *lg_emit(struct lg_block *block, enum lg_op_type type, struct lg_pos pos);
void lg_eval(struct lg_op *start, struct lg_vm *vm);

#endif
