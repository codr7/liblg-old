#include "lg/init.h"
#include "lg/type.h"
#include "lg/types/int64.h"
#include "lg/types/meta.h"
#include "lg/val.h"

int main() {
  lg_init();
  
  struct lg_val v1;
  lg_val_init(&v1, &lg_int64_type)->as_int64 = 42;
  lg_deref(&v1);
  
  struct lg_val v2;
  lg_val_init(&v2, &lg_meta_type)->as_meta = &lg_int64_type;
  lg_deref(&v2);

  lg_deinit();
  return 0;
}
