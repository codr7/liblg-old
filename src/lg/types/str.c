#include <stdlib.h>
#include <string.h>

#include "lg/str.h"
#include "lg/stream.h"
#include "lg/type.h"
#include "lg/types/str.h"
#include "lg/val.h"

#include <stdio.h>

struct lg_type lg_str_type;

static void copy_val(struct lg_val *src, struct lg_val *dst) {
  dst->as_str = lg_str_ref(src->as_str);
}

static void clone_val(struct lg_val *src, struct lg_val *dst) {
  struct lg_str *ss = src->as_str, *ds = malloc(sizeof(struct lg_str));
  dst->as_str = ds;
  ds->len = ss->len;
  ds->data = malloc(ds->len+1);
  strcpy(ds->data, ss->data);
}

static bool is_val(struct lg_val *x, struct lg_val *y) {
  return x->as_str == y->as_str;
}

static bool eq_val(struct lg_val *x, struct lg_val *y) {
  return strcmp(x->as_str->data, y->as_str->data) == 0;
}

static void ref_val(struct lg_val *val) {
  lg_str_ref(val->as_str);
}

static bool deref_val(struct lg_val *val) {
  return lg_str_deref(val->as_str);
}

static void dump_val(struct lg_val *val, struct lg_stream *out) {
  lg_printf(out, "\"%s\"", val->as_str->data);
}

void lg_str_type_init() {
  lg_type_init(&lg_str_type, lg_str("Str"));
  lg_str_type.copy_val = copy_val;
  lg_str_type.clone_val = clone_val;
  lg_str_type.is_val = is_val;
  lg_str_type.eq_val = eq_val;
  lg_str_type.ref_val = ref_val;
  lg_str_type.deref_val = deref_val;
  lg_str_type.dump_val = dump_val;
}
