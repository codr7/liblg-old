#include "lg/block.h"
#include "lg/bset.h"
#include "lg/form.h"
#include "lg/init.h"
#include "lg/libs/abc.h"
#include "lg/op.h"
#include "lg/parse.h"
#include "lg/stack.h"
#include "lg/str.h"
#include "lg/type.h"
#include "lg/types/bool.h"
#include "lg/types/form.h"
#include "lg/types/int64.h"
#include "lg/types/meta.h"
#include "lg/types/stack.h"
#include "lg/types/str.h"
#include "lg/val.h"
#include "lg/vm.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

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

static void compile_tests() {
  struct lg_vm vm;
  lg_vm_init(&vm);  

  struct lg_stack in;
  lg_stack_init(&in, NULL);
  lg_val_init(lg_push(&in), LG_NIL_POS, &lg_int64_type)->as_int64 = 42;

  struct lg_block out;
  lg_block_init(&out);
  assert(lg_compile(&in, &out, &vm));
  lg_emit(&out, LG_NIL_POS, LG_STOP);
  lg_eval(lg_block_start(&out), &vm);

  assert(lg_stack_len(vm.stack) == 1);
  assert(lg_peek(vm.stack)->as_int64 == 42);
  
  lg_block_deinit(&out);
  lg_stack_deinit(&in);
  lg_vm_deinit(&vm);
}

static void env_tests() {
  struct lg_vm vm;
  lg_vm_init(&vm);  
  lg_add_abc_lib(vm.env);
  lg_vm_deinit(&vm);
}

static void eval_tests()  {
  struct lg_block block;
  lg_block_init(&block);

  struct lg_val *v = lg_val_init(&lg_emit(&block, LG_NIL_POS, LG_PUSH)->as_push.val, LG_NIL_POS, &lg_int64_type);
  v->as_int64 = 42;

  lg_emit(&block, LG_NIL_POS, LG_STOP);

  struct lg_vm vm;
  lg_vm_init(&vm);  

  lg_eval(lg_block_start(&block), &vm);
  assert(lg_stack_len(vm.stack) == 1);
  assert(lg_peek(vm.stack)->as_int64 == 42);
  
  lg_vm_deinit(&vm);
  lg_block_deinit(&block);
}

static void macro_tests()  {
  struct lg_vm vm;
  lg_vm_init(&vm);  
  lg_add_abc_lib(vm.env);

  struct lg_stack in;
  lg_stack_init(&in, NULL);

  struct lg_pos pos;
  lg_pos_init(&pos, "macro_tests", 0, 0);

  lg_parse(&pos, "F or T", &in, &vm);

  struct lg_block out;
  lg_block_init(&out);

  lg_compile(&in, &out, &vm);
  lg_emit(&out, pos, LG_STOP);
  lg_eval(lg_block_start(&out), &vm);
  
  assert(lg_stack_len(vm.stack) == 1);
  struct lg_val *v = lg_peek(vm.stack);
  assert(v->type == &lg_bool_type);
  assert(v->as_bool);

  lg_pos_deinit(&pos);
  lg_stack_deinit(&in);
  lg_block_deinit(&out);
  lg_vm_deinit(&vm);
}

static void parse_tests() {
  struct lg_vm vm;
  lg_vm_init(&vm);  
  
  struct lg_stack forms;
  lg_stack_init(&forms, NULL);

  struct lg_pos pos;
  lg_pos_init(&pos, "parse_tests", 0, 0);

  assert(!*lg_parse(&pos, "(foo\n42)", &forms, &vm));
  assert(pos.row == 1);
  assert(pos.col == 3);

  assert(lg_stack_len(&forms) == 1);
  struct lg_stack *group = &lg_peek(&forms)->as_form->as_group;
  assert(lg_stack_len(group) == 2);

  struct lg_val *f2 = lg_pop(group);
  assert(f2->type == &lg_int64_type);
  assert(f2->as_int64 == 42);
  lg_deref(f2);
  
  struct lg_val *f1 = lg_pop(group);
  assert(f1->type == &lg_form_type);
  assert(strcmp(f1->as_form->as_id.data, "foo") == 0);
  lg_deref(f1);

  lg_pos_deinit(&pos);
  lg_stack_deinit(&forms);
  lg_vm_deinit(&vm);
}

static void stack_tests() {
  const int64_t MAX = 10000;
  
  struct lg_stack s;
  lg_stack_init(&s, NULL);
  
  for (int64_t i = 0; i < MAX; i++) {
    lg_val_init(lg_push(&s), LG_NIL_POS, &lg_int64_type)->as_int64 = i;
  }

  assert(lg_stack_len(&s) == MAX);

  for (int64_t i = 0; i < MAX; i++) {
    struct lg_val *v = lg_pop(&s);
    assert(v->type == &lg_int64_type);
    assert(v->as_int64 == MAX-i-1);
    lg_deref(v);
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
  lg_val_init(&v, LG_NIL_POS, &lg_bool_type)->as_bool = true;
  test_val(&v);
  lg_deref(&v);

  lg_val_init(&v, LG_NIL_POS, &lg_int64_type)->as_int64 = 42;
  test_val(&v);
  lg_deref(&v);
  
  lg_val_init(&v, LG_NIL_POS, &lg_meta_type)->as_meta = &lg_int64_type;
  test_val(&v);
  lg_deref(&v);

  struct lg_stack *stack = lg_stack_new(NULL);
  lg_val_init(&v, LG_NIL_POS, &lg_stack_type)->as_stack = stack;
  lg_val_init(lg_push(stack), LG_NIL_POS, &lg_str_type)->as_str = lg_str("foo"); 
  test_val(&v);
  lg_deref(&v);

  lg_val_init(&v, LG_NIL_POS, &lg_str_type)->as_str = lg_str("foo");
  test_val(&v);
  assert(v.as_str->len == 3);
  lg_deref(&v);  
}

int main() {
  lg_init();

  bset_tests();
  compile_tests();
  env_tests();
  eval_tests();
  macro_tests();
  parse_tests();
  stack_tests();
  val_tests();

  lg_deinit();
  return 0;
}
