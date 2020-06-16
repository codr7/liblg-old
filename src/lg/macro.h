#ifndef LG_MACRO_H
#define LG_MACRO_H

#include <stdbool.h>
#include <stdint.h>

struct lg_block;
struct lg_pos;
struct lg_stack;
struct lg_vm;

typedef bool (*lg_macro_imp)(struct lg_pos pos, struct lg_stack *args, struct lg_block *out, struct lg_vm *vm);

struct lg_macro {
  struct lg_str *id;
  uint8_t nargs;
  lg_macro_imp imp;
  int16_t refs;
};

struct lg_macro *lg_macro_new(struct lg_str *id,
			      uint8_t nargs,
			      lg_macro_imp imp);

struct lg_macro *lg_macro_init(struct lg_macro *macro,
			       struct lg_str *id,
			       uint8_t nargs,
			       lg_macro_imp imp);

void lg_macro_deinit(struct lg_macro *macro);

struct lg_macro *lg_macro_ref(struct lg_macro *macro);
bool lg_macro_deref(struct lg_macro *macro);

const char *lg_macro_parse(struct lg_macro *macro,
			   struct lg_pos *pos,
			   const char *in,
			   struct lg_stack *out,
			   struct lg_vm *vm);

bool lg_macro_call(struct lg_macro *macro,
		   struct lg_pos pos,
		   struct lg_stack *args,
		   struct lg_block *out,
		   struct lg_vm *vm);

#endif
