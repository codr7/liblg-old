#ifndef LG_TYPE_H
#define LG_TYPE_H

#include <stdbool.h>

struct lg_val;

struct lg_type {
  char *id;
  int refs;
  
  void (*copy_val)(struct lg_val *src, struct lg_val *dst);
  void (*clone_val)(struct lg_val *src, struct lg_val *dst);

  void (*ref_val)(struct lg_val *);
  bool (*deref_val)(struct lg_val *);
};

struct lg_type *lg_type_init(struct lg_type *type, const char *id);
void lg_type_deinit(struct lg_type *type);

struct lg_type *lg_type_ref(struct lg_type *type);
bool lg_type_deref(struct lg_type *type);

#endif
