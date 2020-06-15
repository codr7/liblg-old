#include <stdlib.h>

#include "lg/stack.h"

struct lg_stack *lg_stack_new(struct lg_stack *parent) {
  return lg_stack_init(malloc(sizeof(struct lg_stack)), parent);
}

struct lg_stack *lg_stack_init(struct lg_stack *stack, struct lg_stack *parent) {
  stack->parent = parent ? lg_stack_ref(parent) : NULL;

  lg_slab_init(&stack->items);
  stack->refs = 1;
  return stack;
}

void lg_stack_deinit(struct lg_stack *stack) {
  if (stack->parent) {
    lg_stack_deref(stack->parent);
  }

  for (size_t i = 0; i < stack->items.len; i++) {
    lg_deref(lg_slab_get(&stack->items, sizeof(struct lg_val), i));
  }
  
  lg_slab_deinit(&stack->items);
}

struct lg_stack *lg_stack_ref(struct lg_stack *stack) {
  if (stack->refs != -1) {
    stack->refs++;
  }

  return stack;
}

bool lg_stack_deref(struct lg_stack *stack) {
  if (stack->refs == -1) {
    return false;
  }

  if (!--stack->refs) {
    lg_stack_deinit(stack);
    free(stack);
    return true;
  }

  return false;
}

void lg_stack_grow(struct lg_stack *stack, size_t cap) {
  lg_slab_grow(&stack->items, sizeof(struct lg_val), cap);
}

size_t lg_stack_len(struct lg_stack *stack) {
  return stack->items.len;
}

struct lg_val *lg_push(struct lg_stack *stack) {
  return (struct lg_val *)lg_slab_push(&stack->items, sizeof(struct lg_val));
}

struct lg_val *lg_pop(struct lg_stack *stack) {
  return (struct lg_val *)lg_slab_pop(&stack->items, sizeof(struct lg_val));
}

struct lg_val *lg_peek(struct lg_stack *stack) {
  struct lg_slab *is = &stack->items;
  return lg_slab_get(is, sizeof(struct lg_val), is->len-1);
}

bool lg_compile(struct lg_stack *in, struct lg_block *out, struct lg_vm *vm) {
  lg_stack_do(in, v) {
    if (!lg_val_compile(v, out, vm)) {
      return false;
    }
  }

  return true;
}
