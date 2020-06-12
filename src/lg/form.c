#include <stdlib.h>

#include "lg/form.h"

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
    free(form->as_id);
    break;
  default:
    break;
  }

  lg_pos_deinit(&form->pos);
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
