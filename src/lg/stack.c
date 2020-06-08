#include <stdlib.h>

#include "lg/stack.h"
#include "lg/val.h"

struct lg_stack *lg_stack_new() {
  return lg_stack_init(malloc(sizeof(struct lg_stack)));
}

struct lg_stack *lg_stack_init(struct lg_stack *stack) {
  lg_slab_init(&stack->items);
  stack->refs = 1;
  return stack;
}

void lg_stack_deinit(struct lg_stack *stack) {
  lg_slab_deinit(&stack->items);
}

void lg_stack_grow(struct lg_stack *stack, size_t cap) {
  lg_slab_grow(&stack->items, sizeof(struct lg_val), cap);
}

size_t lg_stack_len(struct lg_stack *stack) {
  return stack->items.len;
}

struct lg_val *lg_stack_push(struct lg_stack *stack) {
  return (struct lg_val *)lg_slab_push(&stack->items, sizeof(struct lg_val));
}

struct lg_val *lg_stack_pop(struct lg_stack *stack) {
  return (struct lg_val *)lg_slab_pop(&stack->items, sizeof(struct lg_val));
}
