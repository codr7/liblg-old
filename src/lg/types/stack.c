#include <string.h>

#include "lg/stack.h"
#include "lg/str.h"
#include "lg/stream.h"
#include "lg/type.h"
#include "lg/types/stack.h"
#include "lg/util.h"
#include "lg/val.h"

struct lg_type lg_stack_type;

static void copy_val(struct lg_val *src, struct lg_val *dst) {
  dst->as_stack = lg_stack_ref(src->as_stack);
}

static void clone_val(struct lg_val *src, struct lg_val *dst) {
  struct lg_stack *ss = src->as_stack, *ds = lg_stack_new(NULL);
  dst->as_stack = ds;
  const size_t len = lg_stack_len(ss);
  lg_stack_grow(ds, len);
  memcpy(ds->items.slots, ss->items.slots, lg_align(0, sizeof(struct lg_val))*len);
}

static bool is_val(struct lg_val *x, struct lg_val *y) {
  return x->as_stack == y->as_stack;
}

static bool eq_val(struct lg_val *x, struct lg_val *y) {
  struct lg_stack *xs = x->as_stack, *ys = y->as_stack;
  size_t xl = lg_stack_len(xs), yl = lg_stack_len(ys);

  if (xl != yl) {
    return false;
  }
  
  struct lg_val *xv = (struct lg_val *)xs->items.slots, *yv = (struct lg_val *)ys->items.slots;
  
  for (size_t i = 0; i < xl; i++, xv++, yv++) {
    if (!lg_eq(xv, yv)) {
      return false;
    }
  }			   

  return true;
}

static void ref_val(struct lg_val *val) {
  lg_stack_ref(val->as_stack);
}

static bool deref_val(struct lg_val *val) {
  return lg_stack_deref(val->as_stack);
}

static void dump_val(struct lg_val *val, struct lg_stream *out) {
  lg_stack_dump(val->as_stack, out);
}

void lg_stack_type_init() {
  lg_type_init(&lg_stack_type, lg_str("Stack"));
  lg_stack_type.copy_val = copy_val;
  lg_stack_type.clone_val = clone_val;
  lg_stack_type.is_val = is_val;
  lg_stack_type.eq_val = eq_val;
  lg_stack_type.ref_val = ref_val;
  lg_stack_type.deref_val = deref_val;
  lg_stack_type.dump_val = dump_val;
}
