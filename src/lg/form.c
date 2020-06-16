#include <stdlib.h>

#include "lg/block.h"
#include "lg/error.h"
#include "lg/form.h"
#include "lg/op.h"
#include "lg/vm.h"

struct lg_form *lg_form_new(enum lg_form_type type) {
  return lg_form_init(malloc(sizeof(struct lg_form)), type);
}

struct lg_form *lg_form_init(struct lg_form *form, enum lg_form_type type) {
  form->type = type;
  form->refs = 1;
  return form;
}

void lg_form_deinit(struct lg_form *form) {
  switch (form->type) {
  case LG_GROUP:
    lg_stack_deinit(&form->as_group);
    break;
  case LG_ID:
    lg_str_deinit(&form->as_id);
    break;
  default:
    break;
  }
}

bool lg_form_compile(struct lg_form *form,
		     struct lg_pos pos,
		     struct lg_stack *in,
		     struct lg_block *out,
		     struct lg_vm *vm) {
  switch (form->type) {
  case LG_GROUP: {
    lg_emit(out, pos, LG_POP_STACK);

    if (!lg_compile(&form->as_group, out, vm)) {
      return false;
    }
    
    lg_emit(out, pos, LG_PUSH_STACK);
    break;
  }
    
  case LG_ID: {
    struct lg_val *v = lg_get(vm->env, &form->as_id);

    if (!v) {
      lg_error(vm, pos, LG_ESYNTAX, "Unknown: %s", form->as_id.data);
      return false;

    }
    
    return lg_val_compile(v, in, out, vm);
  }
    
  default:
    break;
  }

  return true;
}


struct lg_form *lg_form_ref(struct lg_form *form) {
  form->refs++;
  return form;
}

bool lg_form_deref(struct lg_form *form) {
  if (!--form->refs) {
    lg_form_deinit(form);
    free(form);
    return true;
  }

  return false;
}
