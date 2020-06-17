#include "lg/str.h"
#include "lg/stream.h"
#include "lg/macro.h"
#include "lg/type.h"
#include "lg/types/macro.h"
#include "lg/val.h"

struct lg_type lg_macro_type;

static void copy_val(struct lg_val *src, struct lg_val *dst) {
  dst->as_macro = lg_macro_ref(src->as_macro);
}

static bool is_val(struct lg_val *x, struct lg_val *y) {
  return x->as_macro == y->as_macro;
}

static void ref_val(struct lg_val *val) {
  lg_macro_ref(val->as_macro);
}

static bool deref_val(struct lg_val *val) {
  return lg_macro_deref(val->as_macro);
}

static bool compile_val(struct lg_val *val, struct lg_stack *in, struct lg_block *out, struct lg_vm *vm) {
  return lg_macro_call(val->as_macro, val->pos, in, out, vm);
}

static void dump_val(struct lg_val *val, struct lg_stream *out) {
  lg_printf(out, "Macro(%s)", val->as_macro->id->data);
}

void lg_macro_type_init() {
    lg_type_init(&lg_macro_type, lg_str("Macro"));
    lg_macro_type.copy_val = copy_val;

    lg_macro_type.is_val = is_val;

    lg_macro_type.ref_val = ref_val;
    lg_macro_type.deref_val = deref_val;

    lg_macro_type.compile_val = compile_val;
    lg_macro_type.dump_val = dump_val;
}
