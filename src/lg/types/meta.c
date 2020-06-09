#include <stdlib.h>

#include "lg/type.h"
#include "lg/types/meta.h"
#include "lg/val.h"

struct lg_type lg_meta_type;

static void copy_val(struct lg_val *src, struct lg_val *dst) {
  dst->as_meta = lg_type_ref(src->as_meta);
}

static bool is_val(struct lg_val *x, struct lg_val *y) {
  return x->as_meta == y->as_meta;
}

static void ref_val(struct lg_val *val) {
  lg_type_ref(val->as_meta);
}

static bool deref_val(struct lg_val *val) {
  return lg_type_deref(val->as_meta);
}

void lg_meta_type_init() {
    lg_type_init(&lg_meta_type, "Meta");
    lg_meta_type.refs = -1;
    lg_meta_type.copy_val = copy_val;
    lg_meta_type.is_val = is_val;
    lg_meta_type.ref_val = ref_val;
    lg_meta_type.deref_val = deref_val;
}
