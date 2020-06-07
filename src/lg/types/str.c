#include <stdlib.h>

#include "lg/str.h"
#include "lg/type.h"
#include "lg/types/str.h"
#include "lg/val.h"

#include <stdio.h>

struct lg_type lg_str_type;

static void ref_val(struct lg_val *val) {
  struct lg_str *v = val->as_str;

  if (v->refs != -1) {
    v->refs++;
  }
}

static bool deref_val(struct lg_val *val) {
  return lg_str_deref(val->as_str);
}

void lg_str_type_init() {
    lg_type_init(&lg_str_type, "Str");
    lg_str_type.refs = -1;
    lg_str_type.ref_val = ref_val;
    lg_str_type.deref_val = deref_val;
}
