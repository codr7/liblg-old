#include "lg/error.h"
#include "lg/str.h"
#include "lg/type.h"
#include "lg/val.h"

struct lg_type lg_error_type;

static void copy_val(struct lg_val *src, struct lg_val *dst) {
  dst->as_error = lg_error_ref(src->as_error);
}

static bool is_val(struct lg_val *x, struct lg_val *y) {
  return x->as_error == y->as_error;
}

static void ref_val(struct lg_val *val) {
  lg_error_ref(val->as_error);
}

static bool deref_val(struct lg_val *val) {
  return lg_error_deref(val->as_error);
}

void lg_error_type_init() {
  lg_type_init(&lg_error_type, lg_str("Error"));
  lg_error_type.copy_val = copy_val;
  lg_error_type.is_val = is_val;
  lg_error_type.ref_val = ref_val;
  lg_error_type.deref_val = deref_val;
}
