#include "lg/init.h"
#include "lg/stack.h"
#include "lg/type.h"
#include "lg/types/int64.h"
#include "lg/types/meta.h"
#include "lg/val.h"

#include <assert.h>

void val_tests() {
  struct lg_val v1;
  lg_val_init(&v1, &lg_int64_type)->as_int64 = 42;
  lg_deref(&v1);
  
  struct lg_val v2;
  lg_val_init(&v2, &lg_meta_type)->as_meta = &lg_int64_type;
  lg_deref(&v2);
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
