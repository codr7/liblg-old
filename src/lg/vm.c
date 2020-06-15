#include "lg/vm.h"

struct lg_vm *lg_vm_init(struct lg_vm *vm) {
  vm->debug = false;
  vm->env = lg_env_new(NULL);
  vm->stack = lg_stack_new(NULL);
  lg_stack_init(&vm->errors, NULL);
  return vm;
}

void lg_vm_deinit(struct lg_vm *vm) {
  lg_env_deref(vm->env);
  lg_stack_deref(vm->stack);
  lg_stack_deinit(&vm->errors);
}
