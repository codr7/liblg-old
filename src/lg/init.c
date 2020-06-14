#include "lg/init.h"
#include "lg/pos.h"
#include "lg/type.h"
#include "lg/types/bool.h"
#include "lg/types/error.h"
#include "lg/types/form.h"
#include "lg/types/int64.h"
#include "lg/types/meta.h"
#include "lg/types/stack.h"
#include "lg/types/str.h"

void lg_init() {
  lg_pos_init(&LG_NIL_POS, "n/a", -1, -1);

  lg_bool_type_init();
  lg_error_type_init();
  lg_form_type_init();
  lg_int64_type_init();
  lg_meta_type_init();
  lg_stack_type_init();
  lg_str_type_init();
}

void lg_deinit() {
  lg_pos_deinit(&LG_NIL_POS);
  
  lg_type_deinit(&lg_bool_type);
  lg_type_deinit(&lg_error_type);
  lg_type_deinit(&lg_form_type);
  lg_type_deinit(&lg_int64_type);
  lg_type_deinit(&lg_meta_type);
  lg_type_deinit(&lg_stack_type);
  lg_type_deinit(&lg_str_type);
}
