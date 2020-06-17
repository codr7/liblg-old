#include "lg/init.h"
#include "lg/libs/abc.h"
#include "lg/repl.h"
#include "lg/vm.h"

int main() {
  lg_init();
  struct lg_vm vm;
  lg_vm_init(&vm);
  vm.debug = true;
  lg_add_abc_lib(vm.env);
  lg_repl(&vm, stdin, stdout);
  lg_vm_deinit(&vm);
  lg_deinit();
  return 0;
}
