#include "lg/init.h"
#include "lg/stack.h"
#include "lg/type.h"
#include "lg/types/int64.h"
#include "lg/types/meta.h"
#include "lg/types/stack.h"
#include "lg/val.h"

#include <assert.h>

void val_tests() {
  struct lg_val int64;
  lg_val_init(&int64, &lg_int64_type)->as_int64 = 42;
  lg_deref(&int64);
  
  struct lg_val meta;
  lg_val_init(&meta, &lg_meta_type)->as_meta = &lg_int64_type;
  lg_deref(&meta);

  struct lg_val stack;
  lg_val_init(&stack, &lg_stack_type)->as_stack = lg_stack_new();
  lg_deref(&stack);  
}

void stack_tests() {
  const int64_t MAX = 10000;
  
  struct lg_stack s;
  lg_stack_init(&s);
  
  for (int64_t i = 0; i < MAX; i++) {
    lg_stack_push(&s)->as_int64 = i;
  }

  for (int64_t i = 0; i < MAX; i++) {
    assert(lg_stack_pop(&s)->as_int64 == MAX-i-1);
  }

  lg_stack_deinit(&s);
}

int main() {
  lg_init();
  val_tests();
  stack_tests();
  lg_deinit();
  return 0;
}
