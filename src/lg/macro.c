#include "lg/macro.h"
#include "lg/stack.h"
#include "lg/util.h"

#include <stdlib.h>

struct lg_macro *lg_macro_init(struct lg_macro *macro, 
			       const char *id,
			       uint8_t nargs,
			       const char *args[],
			       lg_macro_imp imp) {
  macro->id = lg_strdup(id, NULL);
  macro->nargs = nargs;
  macro->args = malloc(nargs*sizeof(char *));
  
  for (uint8_t i = 0; i < nargs; i++) {
    macro->args[i] = lg_strdup(args[i], NULL);
  }
  
  macro->imp = imp;
  macro->refs = 1;
  return macro;
}

void lg_macro_deinit(struct lg_macro *macro) {
  for (uint8_t i = 0; i < macro->nargs; i++) {
    free(macro->args[i]);
  }

  free(macro->id);
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

const char *lg_macro_compile(struct lg_macro *macro, struct lg_stack *args, const char *in, struct lg_block *out) {
  for (uint8_t i = 0; i < macro->nargs - lg_stack_len(args); i++) {
  }
  
  return macro->imp(args, out);
}
