#ifndef LG_STACK_H
#define LG_STACK_H

#include "lg/slab.h"

struct lg_stack {
  int refs;
  struct lg_slab items;
};

struct lg_stack *lg_stack_init(struct lg_stack *stack);
void lg_stack_deinit(struct lg_stack *stack);
void lg_stack_grow(struct lg_stack *stack, size_t cap);
struct lg_val *lg_stack_push(struct lg_stack *stack);
struct lg_val *lg_stack_pop(struct lg_stack *stack);

#endif
