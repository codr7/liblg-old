#include "lg/vm.h"

struct lg_vm *lg_vm_init(struct lg_vm *vm) {
  vm->debug = false;
  lg_stack_init(&vm->errors);
  return vm;
}

void lg_vm_deinit(struct lg_vm *vm) {
  lg_stack_deinit(&vm->errors);
}
