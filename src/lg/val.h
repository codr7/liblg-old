#ifndef LG_VAL_H
#define LG_VAL_H

#include <stdbool.h>
#include <stdint.h>

struct lg_stack;
struct lg_str;
struct lg_type;

struct lg_val {
  struct lg_type *type;
  
  union {
    int64_t as_int64;
    struct lg_type *as_meta;
    struct lg_stack *as_stack;
    struct lg_str *as_str;
  };
};

struct lg_val *lg_val_init(struct lg_val *val, struct lg_type *type);

struct lg_val *lg_ref(struct lg_val *val);
bool lg_deref(struct lg_val *val);

#endif
