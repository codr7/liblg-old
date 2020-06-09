#ifndef LG_STACK_H
#define LG_STACK_H

#include <stdbool.h>

#include "lg/slab.h"

struct lg_stack {
  struct lg_slab items;
  int refs;
};

struct lg_stack *lg_stack_new();
struct lg_stack *lg_stack_init(struct lg_stack *stack);
void lg_stack_deinit(struct lg_stack *stack);

struct lg_stack *lg_stack_ref(struct lg_stack *stack);
bool lg_stack_deref(struct lg_stack *stack);

void lg_stack_grow(struct lg_stack *stack, size_t cap);
size_t lg_stack_len(struct lg_stack *stack);
struct lg_val *lg_stack_get(struct lg_stack *stack, size_t i);
struct lg_val *lg_stack_push(struct lg_stack *stack);
struct lg_val *lg_stack_pop(struct lg_stack *stack);

#endif
