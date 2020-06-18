#ifndef LG_STACK_H
#define LG_STACK_H

#include <stdbool.h>

#include "lg/slab.h"
#include "lg/util.h"
#include "lg/val.h"

#define _lg_stack_do(stack, item, _i)				\
  size_t _i = 0;						\
  for (struct lg_val *item =					\
	 (struct lg_val *)lg_slab_get(&(stack)->items, 0);	\
       _i < (stack)->items.len;					\
       _i++, item++)

#define lg_stack_do(stack, item)		\
  _lg_stack_do(stack, item, lg_unique(i))

struct lg_stream;

struct lg_stack {
  struct lg_stack *parent;
  struct lg_slab items;
  int refs;
};

struct lg_stack *lg_stack_new(struct lg_stack *parent);
struct lg_stack *lg_stack_init(struct lg_stack *stack, struct lg_stack *parent);
void lg_stack_deinit(struct lg_stack *stack);

void lg_stack_grow(struct lg_stack *stack, size_t cap);
size_t lg_stack_len(struct lg_stack *stack);
void lg_stack_clear(struct lg_stack *stack);
struct lg_val *lg_stack_get(struct lg_stack *stack, size_t i);
void lg_stack_dump(struct lg_stack *stack, struct lg_stream *out);

struct lg_val *lg_push(struct lg_stack *stack);
struct lg_val *lg_pop(struct lg_stack *stack);
struct lg_val *lg_peek(struct lg_stack *stack);

bool lg_compile(struct lg_stack *in, struct lg_block *out, struct lg_vm *vm);

struct lg_stack *lg_stack_ref(struct lg_stack *stack);
bool lg_stack_deref(struct lg_stack *stack);

#endif
