#ifndef LG_PARSE_H
#define LG_PARSE_H

struct lg_pos;
struct lg_stack;
struct lg_vm;

const char *lg_parse(const char *in,
		     struct lg_pos *pos,
		     struct lg_stack *out,
		     struct lg_vm *vm);

const char *lg_parse_form(const char *in,
			  struct lg_pos *pos,
			  struct lg_stack *out,
			  struct lg_vm *vm);

const char *lg_parse_group(const char *in,
			   struct lg_pos *pos,
			   struct lg_stack *out,
			   struct lg_vm *vm);

const char *lg_parse_id(const char *in,
			struct lg_pos *pos,
			struct lg_stack *out,
			struct lg_vm *vm);

const char *lg_parse_int(const char *in,
			 struct lg_pos *pos,
			 struct lg_stack *out,
			 struct lg_vm *vm);

#endif
