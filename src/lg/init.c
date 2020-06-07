#include "lg/init.h"
#include "lg/type.h"
#include "lg/types/int64.h"
#include "lg/types/meta.h"
#include "lg/types/stack.h"

void lg_init() {
  lg_int64_type_init();
  lg_meta_type_init();
  lg_stack_type_init();
}

void lg_deinit() {
  lg_type_deinit(&lg_int64_type);
  lg_type_deinit(&lg_meta_type);
  lg_type_deinit(&lg_stack_type);
}
