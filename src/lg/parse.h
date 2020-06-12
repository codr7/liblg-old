#ifndef LG_PARSE_H
#define LG_PARSE_H

struct lg_pos;
struct lg_stack;
struct lg_vm;

const char *lg_parse(struct lg_vm *vm,
		     const char *in,
		     struct lg_pos *pos,
		     struct lg_stack *out);

const char *lg_parse_form(struct lg_vm *vm,
			  const char *in,
			  struct lg_pos *pos,
			  struct lg_stack *out);

const char *lg_parse_group(struct lg_vm *vm,
			   const char *in,
			   struct lg_pos *pos,
			   struct lg_stack *out);

const char *lg_parse_id(struct lg_vm *vm,
			const char *in,
			struct lg_pos *pos,
			struct lg_stack *out);

const char *lg_parse_int(struct lg_vm *vm,
			 const char *in,
			 struct lg_pos *pos,
			 struct lg_stack *out);

#endif
