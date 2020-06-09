#include "lg/type.h"
#include "lg/types/int64.h"
#include "lg/val.h"

struct lg_type lg_int64_type;

static bool is_val(struct lg_val *x, struct lg_val *y) {
  return x->as_int64 == y->as_int64;
}

void lg_int64_type_init() {
    lg_type_init(&lg_int64_type, "Int64");
    lg_int64_type.refs = -1;
    lg_int64_type.is_val = is_val;
}
