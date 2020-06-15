#ifndef LG_FORM_H
#define LG_FORM_H

#include <stdbool.h>
#include <stdint.h>

#include "lg/pos.h"
#include "lg/stack.h"
#include "lg/str.h"
#include "lg/val.h"

enum lg_form_type {LG_GROUP, LG_ID};

struct lg_form {
  struct lg_pos pos;
  enum lg_form_type type;
  int16_t refs;
  
  union {
    struct lg_stack as_group;
    struct lg_str as_id;
  };
};

struct lg_form *lg_form_new(struct lg_pos pos, enum lg_form_type type);
struct lg_form *lg_form_init(struct lg_form *form, struct lg_pos, enum lg_form_type type);
void lg_form_deinit(struct lg_form *form);

bool lg_form_compile(struct lg_form *form, struct lg_block *out, struct lg_vm *vm);

struct lg_form *lg_form_ref(struct lg_form *form);
bool lg_form_deref(struct lg_form *form);

#endif
