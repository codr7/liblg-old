#include <stdlib.h>

#include "lg/str.h"
#include "lg/type.h"
#include "lg/val.h"

static void clone_val(struct lg_val *src, struct lg_val *dst) {
  src->type->copy_val(src, dst);
}

static bool eq_val(struct lg_val *x, struct lg_val *y) {
  return x->type->is_val(x, y);
}

struct lg_type *lg_type_init(struct lg_type *type, struct lg_str *id) {
  type->id = id;
  type->refs = 1;
  
  type->copy_val = NULL;
  type->clone_val = clone_val;

  type->is_val = NULL;
  type->eq_val = eq_val;
  
  type->ref_val = NULL;
  type->deref_val = NULL;

  return type;
}

void lg_type_deinit(struct lg_type *type) {
  lg_str_deref(type->id);
}

struct lg_type *lg_type_ref(struct lg_type *type) {
  type->refs++;
  return type;
}

bool lg_type_deref(struct lg_type *type) {
  if (!--type->refs) {
    lg_type_deinit(type);
    free(type);
    return true;
  }

  return false;
}
