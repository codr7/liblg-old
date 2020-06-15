#include <stdlib.h>

#include "lg/block.h"
#include "lg/form.h"
#include "lg/op.h"
#include "lg/vm.h"

struct lg_form *lg_form_new(struct lg_pos pos, enum lg_form_type type) {
  return lg_form_init(malloc(sizeof(struct lg_form)), pos, type);
}

struct lg_form *lg_form_init(struct lg_form *form, struct lg_pos pos, enum lg_form_type type) {
  lg_pos_copy(&pos, &form->pos);
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

  lg_pos_deinit(&form->pos);
}

bool lg_form_compile(struct lg_form *form, struct lg_block *out, struct lg_vm *vm) {
  switch (form->type) {
  case LG_GROUP: {
    lg_emit(out, LG_PUSH_STACK, form->pos);

    lg_stack_do(&form->as_group, v) {
      if (!lg_val_compile(v, out, vm)) {
	return false;
      }
    }

    lg_emit(out, LG_POP_STACK, form->pos);
    break;
  }
    
  case LG_ID: {
    struct lg_val *v = lg_env_get(vm->env, &form->as_id);

    if (v != NULL) {
      return lg_val_compile(v, out, vm);
    }
    
    break;
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
