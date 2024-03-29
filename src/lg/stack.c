#include <stdlib.h>

#include "lg/block.h"
#include "lg/stack.h"
#include "lg/stream.h"

static void deref_items(struct lg_stack *stack) {
  lg_stack_do(stack, v) {
    lg_deref(v);
  }
}

struct lg_stack *lg_stack_new(struct lg_stack *parent) {
  return lg_stack_init(malloc(sizeof(struct lg_stack)), parent);
}

struct lg_stack *lg_stack_init(struct lg_stack *stack, struct lg_stack *parent) {
  stack->parent = parent ? lg_stack_ref(parent) : NULL;
  lg_slab_init(&stack->items, sizeof(struct lg_val));
  stack->refs = 1;
  return stack;
}

void lg_stack_deinit(struct lg_stack *stack) {
  if (stack->parent) {
    lg_stack_deref(stack->parent);
  }

  deref_items(stack);
  lg_slab_deinit(&stack->items);
}

void lg_stack_grow(struct lg_stack *stack, size_t cap) {
  lg_slab_grow(&stack->items, cap);
}

size_t lg_stack_len(struct lg_stack *stack) {
  return stack->items.len;
}

void lg_stack_clear(struct lg_stack *stack) {
  deref_items(stack);
  lg_slab_clear(&stack->items);
}

void lg_stack_dump(struct lg_stack *stack, struct lg_stream *out) {
  lg_putc(out, '[');
  bool first = true;
  
  lg_stack_do(stack, v) {
    if (!first) {
      lg_putc(out, ' ');
    }

    lg_dump(v, out);
    first = false;
  }
  
  lg_putc(out, ']');
}

struct lg_val *lg_push(struct lg_stack *stack) {
  return (struct lg_val *)lg_slab_push(&stack->items);
}

struct lg_val *lg_pop(struct lg_stack *stack) {
  return (struct lg_val *)lg_slab_pop(&stack->items);
}

struct lg_val *lg_peek(struct lg_stack *stack) {
  struct lg_slab *is = &stack->items;
  return lg_slab_get(is, is->len-1);
}

bool lg_compile(struct lg_stack *in, struct lg_block *out, struct lg_vm *vm) {
  size_t nops = lg_block_len(out);
  
  while (lg_stack_len(in)) {
    struct lg_val *v = lg_pop(in);

    if (!lg_val_compile(v, in, out, vm)) {
      return false;
    }

    lg_deref(v);
  }

  lg_block_reverse(out, nops);
  return true;
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
