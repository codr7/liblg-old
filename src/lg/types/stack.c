#include <stdlib.h>

#include "lg/stack.h"
#include "lg/type.h"
#include "lg/types/stack.h"
#include "lg/val.h"

#include <stdio.h>

struct lg_type lg_stack_type;

static void ref_val(struct lg_val *val) {
  struct lg_stack *v = val->as_stack;

  if (v->refs != -1) {
    v->refs++;
  }
}

static bool deref_val(struct lg_val *val) {
  struct lg_stack *v = val->as_stack;
  
  if (v->refs == -1) {
    return false;
  }

  if (!--v->refs) {
    lg_stack_deinit(v);
    free(v);
    return true;
  }

  return false;
}

void lg_stack_type_init() {
    lg_type_init(&lg_stack_type, "Stack");
    lg_stack_type.refs = -1;
    lg_stack_type.ref_val = ref_val;
    lg_stack_type.deref_val = deref_val;
}
