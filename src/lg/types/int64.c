#include "lg/str.h"
#include "lg/type.h"
#include "lg/types/int64.h"
#include "lg/val.h"

struct lg_type lg_int64_type;

static void copy_val(struct lg_val *src, struct lg_val *dst) {
  dst->as_int64 = src->as_int64;
}

static bool is_val(struct lg_val *x, struct lg_val *y) {
  return x->as_int64 == y->as_int64;
}

void lg_int64_type_init() {
  lg_type_init(&lg_int64_type, lg_str("Int64"));
  lg_int64_type.copy_val = copy_val;
  lg_int64_type.is_val = is_val;
}
