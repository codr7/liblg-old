#ifndef LG_VM_H
#define LG_VM_H

#include <stdbool.h>

#include "lg/env.h"
#include "lg/stack.h"

struct lg_vm {
  bool debug;
  struct lg_env root_env;
  struct lg_env *env;
  struct lg_stack stack;
  struct lg_stack errors;
};

struct lg_vm *lg_vm_init(struct lg_vm *vm);
void lg_vm_deinit(struct lg_vm *vm);

#endif
