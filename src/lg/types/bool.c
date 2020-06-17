#include "lg/str.h"
#include "lg/stream.h"
#include "lg/type.h"
#include "lg/types/bool.h"
#include "lg/val.h"

struct lg_type lg_bool_type;

static void copy_val(struct lg_val *src, struct lg_val *dst) {
  dst->as_bool = src->as_bool;
}

static bool is_val(struct lg_val *x, struct lg_val *y) {
  return x->as_bool == y->as_bool;
}

static void dump_val(struct lg_val *val, struct lg_stream *out) {
  lg_putc(out, val->as_bool ? 'T' : 'F');
}

void lg_bool_type_init() {
  lg_type_init(&lg_bool_type, lg_str("Bool"));
  lg_bool_type.copy_val = copy_val;
  lg_bool_type.is_val = is_val;
  lg_bool_type.dump_val = dump_val;
}
