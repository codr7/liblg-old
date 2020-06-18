#ifndef LG_BLOCK_H
#define LG_BLOCK_H

#include "lg/pos.h"
#include "lg/slab.h"
#include "lg/util.h"

#include <stdbool.h>

#define _lg_block_do(block, op, _i)					\
  size_t _i = 0;							\
  for (struct lg_op *op = lg_slab_get(&block->ops, 0);			\
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
size_t lg_block_len(struct lg_block *block);
void lg_block_clear(struct lg_block *block);
void lg_block_reverse(struct lg_block *block, size_t offs);

struct lg_op *lg_emit(struct lg_block *block, struct lg_pos pos, enum lg_op_type type);
bool lg_eval(struct lg_op *start, struct lg_vm *vm);

#endif
