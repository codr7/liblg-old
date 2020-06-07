#include <stdlib.h>

#include "lg/type.h"
#include "lg/util.h"

struct lg_type *lg_type_init(struct lg_type *type, const char *id) {
  type->id = lg_strdup(id);
  type->refs = 1;

  type->ref_val = NULL;
  type->deref_val = NULL;

  return type;
}

void lg_type_deinit(struct lg_type *type) {
  free(type->id);
}
