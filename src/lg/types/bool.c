#include "lg/type.h"
#include "lg/types/bool.h"
#include "lg/val.h"

struct lg_type lg_bool_type;

static bool is_val(struct lg_val *x, struct lg_val *y) {
  return x->as_bool == y->as_bool;
}

void lg_bool_type_init() {
    lg_type_init(&lg_bool_type, "Bool");
    lg_bool_type.refs = -1;
    lg_bool_type.is_val = is_val;
}
