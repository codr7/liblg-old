#include "lg/type.h"
#include "lg/val.h"

struct lg_val *lg_val_init(struct lg_val *val, struct lg_type *type) {
  val->type = type;
  return val;
} 

struct lg_val *lg_ref(struct lg_val *val) {
  if (val->type->ref_val) {
    val->type->ref_val(val);
  }

  return val;
}

bool lg_deref(struct lg_val *val) {
  if (val->type->deref_val) {
    return val->type->deref_val(val);
  }

  return true;
}
