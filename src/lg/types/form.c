#include "lg/form.h"
#include "lg/str.h"
#include "lg/type.h"
#include "lg/val.h"

struct lg_type lg_form_type;

static void copy_val(struct lg_val *src, struct lg_val *dst) {
  dst->as_form = lg_form_ref(src->as_form);
}

static bool is_val(struct lg_val *x, struct lg_val *y) {
  return x->as_form == y->as_form;
}

static bool compile_val(struct lg_val *val, struct lg_block *out, struct lg_vm *vm) {
  return lg_form_compile(val->as_form, out, vm);
}

static void ref_val(struct lg_val *val) {
  lg_form_ref(val->as_form);
}

static bool deref_val(struct lg_val *val) {
  return lg_form_deref(val->as_form);
}

void lg_form_type_init() {
    lg_type_init(&lg_form_type, lg_str_new("Form"));
    lg_form_type.copy_val = copy_val;
    lg_form_type.is_val = is_val;
    lg_form_type.compile_val = compile_val;
    lg_form_type.ref_val = ref_val;
    lg_form_type.deref_val = deref_val;
}
