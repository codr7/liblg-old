#include "lg/bset.h"
#include "lg/init.h"
#include "lg/stack.h"
#include "lg/str.h"
#include "lg/type.h"
#include "lg/types/bool.h"
#include "lg/types/int64.h"
#include "lg/types/meta.h"
#include "lg/types/stack.h"
#include "lg/types/str.h"
#include "lg/val.h"

#include <assert.h>

static enum lg_cmp cmp_int(const void *x, const void *y) {
  int xv = *(const int *)x, yv = *(const int *)y;

  if (xv < yv) {
    return LG_LT;
  }

  return (xv > yv) ? LG_GT : LG_EQ;
}

static void bset_tests() {
  const int MAX = 10000;
  
  struct lg_bset s;
  lg_bset_init(&s, sizeof(int), cmp_int);
  
  for (int i = MAX-1; i >= 0; i--) {
    *(int *)lg_bset_add(&s, &i) = i;
  }

  assert(lg_bset_len(&s) == MAX);
  
  for (int i = 0; i < MAX; i++) {
    assert(*(int *)lg_bset_get(&s, &i) == i);
  }

  lg_bset_deinit(&s);
}

static void stack_tests() {
  const int64_t MAX = 10000;
  
  struct lg_stack s;
  lg_stack_init(&s);
  
  for (int64_t i = 0; i < MAX; i++) {
    lg_stack_push(&s)->as_int64 = i;
  }

  assert(lg_stack_len(&s) == MAX);

  for (int64_t i = 0; i < MAX; i++) {
    assert(lg_stack_pop(&s)->as_int64 == MAX-i-1);
  }

  lg_stack_deinit(&s);
}

static void test_val(struct lg_val *v) {
  assert(lg_is(v, v));
  assert(lg_eq(v, v));
  
  struct lg_val cv;
  lg_copy(v, &cv);
  assert(lg_is(v, &cv));
  lg_deref(&cv);
}

static void val_tests() {
  struct lg_val v;
  lg_val_init(&v, &lg_bool_type)->as_bool = true;
  test_val(&v);
  lg_deref(&v);

  lg_val_init(&v, &lg_int64_type)->as_int64 = 42;
  test_val(&v);
  lg_deref(&v);
  
  lg_val_init(&v, &lg_meta_type)->as_meta = &lg_int64_type;
  test_val(&v);
  lg_deref(&v);

  struct lg_stack *stack = lg_stack_new();
  lg_val_init(&v, &lg_stack_type)->as_stack = stack;
  lg_val_init(lg_stack_push(stack), &lg_str_type)->as_str = lg_str_new("foo"); 
  test_val(&v);
  lg_deref(&v);

  lg_val_init(&v, &lg_str_type)->as_str = lg_str_new("foo");
  test_val(&v);
  assert(v.as_str->len == 3);
  lg_deref(&v);  
}

int main() {
  lg_init();

  bset_tests();
  stack_tests();
  val_tests();

  lg_deinit();
  return 0;
}
