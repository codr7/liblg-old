#ifndef LG_VAL_H
#define LG_VAL_H

#include <stdbool.h>
#include <stdint.h>

struct lg_error;
struct lg_stack;
struct lg_str;
struct lg_type;

struct lg_val {
  struct lg_type *type;
  
  union {
    bool as_bool;
    struct lg_error *as_error;
    struct lg_form *as_form;
    int64_t as_int64;
    struct lg_type *as_meta;
    struct lg_stack *as_stack;
    struct lg_str *as_str;
  };
};

struct lg_val *lg_val_init(struct lg_val *val, struct lg_type *type);

void lg_copy(struct lg_val *src, struct lg_val *dst);
void lg_clone(struct lg_val *src, struct lg_val *dst);

bool lg_is(struct lg_val *x, struct lg_val *y);
bool lg_eq(struct lg_val *x, struct lg_val *y);

struct lg_val *lg_ref(struct lg_val *val);
bool lg_deref(struct lg_val *val);

#endif
