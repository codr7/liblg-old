#include "lg/env.h"
#include "lg/libs/abc.h"
#include "lg/str.h"
#include "lg/types/bool.h"
#include "lg/types/error.h"
#include "lg/types/form.h"
#include "lg/types/int64.h"
#include "lg/types/meta.h"
#include "lg/types/stack.h"
#include "lg/types/str.h"

void lg_add_abc_lib(struct lg_env *env) {
  struct lg_pos p = LG_NIL_POS;
  lg_add_type(env, p, &lg_bool_type);
  lg_add_type(env, p, &lg_error_type);
  lg_add_type(env, p, &lg_form_type);
  lg_add_type(env, p, &lg_int64_type);
  lg_add_type(env, p, &lg_meta_type);
  lg_add_type(env, p, &lg_stack_type);
  lg_add_type(env, p, &lg_str_type);

  lg_add(env, p, lg_str("T"), &lg_bool_type)->as_bool = true;
  lg_add(env, p, lg_str("F"), &lg_bool_type)->as_bool = false;
}
