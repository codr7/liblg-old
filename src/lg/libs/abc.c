#include "lg/env.h"
#include "lg/libs/abc.h"
#include "lg/types/bool.h"
#include "lg/types/error.h"
#include "lg/types/form.h"
#include "lg/types/int64.h"
#include "lg/types/meta.h"
#include "lg/types/stack.h"
#include "lg/types/str.h"

void lg_add_abc_lib(struct lg_env *env) {
  lg_add_type(env, &lg_bool_type);
  lg_add_type(env, &lg_error_type);
  lg_add_type(env, &lg_form_type);
  lg_add_type(env, &lg_int64_type);
  lg_add_type(env, &lg_meta_type);
  lg_add_type(env, &lg_stack_type);
  lg_add_type(env, &lg_str_type);
}
