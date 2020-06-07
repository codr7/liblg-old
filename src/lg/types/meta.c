#include <stdlib.h>

#include "lg/type.h"
#include "lg/types/meta.h"
#include "lg/val.h"

struct lg_type lg_meta_type;

static void ref_val(struct lg_val *val) {
  struct lg_type *v = val->as_meta;

  if (v->refs != -1) {
    v->refs++;
  }
}

static bool deref_val(struct lg_val *val) {
  struct lg_type *v = val->as_meta;
  
  if (v->refs == -1) {
    return false;
  }
  
  if (!--v->refs) {
    lg_type_deinit(v);
    free(v);
    return true;
  }

  return false;
}

void lg_meta_type_init() {
    lg_type_init(&lg_meta_type, "Meta");
    lg_meta_type.refs = -1;
    lg_meta_type.ref_val = ref_val;
    lg_meta_type.deref_val = deref_val;
}
