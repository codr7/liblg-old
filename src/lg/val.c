#include "lg/type.h"
#include "lg/val.h"

struct lg_val *lg_val_init(struct lg_val *val, struct lg_type *type) {
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
  if (val->type->deref_val) {
    return val->type->deref_val(val);
  }

  return true;
}

void lg_copy(struct lg_val *src, struct lg_val *dst) {
  struct lg_type *t = src->type;
  dst->type = t;
  t->copy_val(src, dst);
}

void lg_clone(struct lg_val *src, struct lg_val *dst) {
  struct lg_type *t = src->type;
  dst->type = t;
  t->clone_val(src, dst);
}
