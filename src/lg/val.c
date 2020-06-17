#include <assert.h>

#include "lg/type.h"
#include "lg/val.h"

struct lg_val *lg_val_init(struct lg_val *val, struct lg_pos pos, struct lg_type *type) {
  lg_pos_copy(&pos, &val->pos);
  val->type = type;
  return val;
} 

struct lg_val *lg_ref(struct lg_val *val) {
  if (val->type->ref_val) {
    val->type->ref_val(val);
  }

  return val;
}

bool lg_deref(struct lg_val *val) {
  lg_pos_deinit(&val->pos);
  return val->type->deref_val ? val->type->deref_val(val) : true;
}

void lg_copy(struct lg_val *src, struct lg_val *dst) {
  lg_pos_copy(&src->pos, &dst->pos);
  struct lg_type *t = src->type;
  assert(t->copy_val);
  dst->type = lg_type_ref(t);
  t->copy_val(src, dst);
}

void lg_clone(struct lg_val *src, struct lg_val *dst) {
  lg_pos_copy(&src->pos, &dst->pos);
  struct lg_type *t = src->type;
  assert(t->clone_val);
  dst->type = lg_type_ref(t);
  t->clone_val(src, dst);
}

bool lg_is(struct lg_val *x, struct lg_val *y) {
  struct lg_type *t = x->type;
  assert(t->is_val);
  return t == y->type && t->is_val(x, y);
}

bool lg_eq(struct lg_val *x, struct lg_val *y) {
  struct lg_type *t = x->type;
  assert(t->eq_val);
  return t == y->type && t->eq_val(x, y);
}

bool lg_val_compile(struct lg_val *val, struct lg_stack *in, struct lg_block *out, struct lg_vm *vm) {
  struct lg_type *t = val->type;
  assert(t->compile_val);
  return t->compile_val(val, in, out, vm);
}

void lg_dump(struct lg_val *val, struct lg_stream *out) {
  struct lg_type *t = val->type;
  assert(t->dump_val);
  t->dump_val(val, out);
}
