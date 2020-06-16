#include "lg/error.h"
#include "lg/macro.h"
#include "lg/parse.h"
#include "lg/pos.h"
#include "lg/stack.h"
#include "lg/util.h"

#include <stdlib.h>

struct lg_macro *lg_macro_new(struct lg_str *id,
			      uint8_t nargs,
			      lg_macro_imp imp) {
  return lg_macro_init(malloc(sizeof(struct lg_macro)), id, nargs, imp);
}

struct lg_macro *lg_macro_init(struct lg_macro *macro, 
			       struct lg_str *id,
			       uint8_t nargs,
			       lg_macro_imp imp) {
  macro->id = lg_str_ref(id);
  macro->nargs = nargs;
  macro->imp = imp;
  macro->refs = 1;
  return macro;
}

void lg_macro_deinit(struct lg_macro *macro) {
  lg_str_deref(macro->id);
}

struct lg_macro *lg_macro_ref(struct lg_macro *macro) {
  macro->refs++;
  return macro;
}

bool lg_macro_deref(struct lg_macro *macro) {
  if (!--macro->refs) {
    lg_macro_deinit(macro);
    free(macro);
    return true;
  }

  return false;
}

const char *lg_macro_parse(struct lg_macro *macro,
			   struct lg_pos *pos,
			   const char *in,
			   struct lg_stack *out,
			   struct lg_vm *vm) {
  for (uint8_t i = 0; i < macro->nargs - lg_stack_len(out); i++) {
    in = lg_skip(pos, in);

    if (!(in = lg_parse_form(pos, in, out, vm))) {
      lg_error(vm, *pos, LG_ESYNTAX,
	       "%s takes %d arguments, %d given", macro->id->data, macro->nargs, lg_stack_len(out));
      
      return NULL;
    }
  }

  return in;
}

bool lg_macro_call(struct lg_macro *macro,
		   struct lg_pos pos,
		   struct lg_stack *args,
		   struct lg_block *out,
		   struct lg_vm *vm) {  
  return macro->imp(pos, args, out, vm);
}
