#include <ctype.h>
#include <string.h>

#include "lg/error.h"
#include "lg/env.h"
#include "lg/form.h"
#include "lg/parse.h"
#include "lg/pos.h"
#include "lg/stack.h"
#include "lg/types/form.h"
#include "lg/types/int64.h"
#include "lg/types/macro.h"
#include "lg/val.h"
#include "lg/vm.h"
#include "lg/util.h"

static struct lg_form *push_form(struct lg_pos pos, enum lg_form_type type, struct lg_stack *out) {
  struct lg_val *v = lg_val_init(lg_push(out), pos, &lg_form_type);
  struct lg_form *f = lg_form_new(type);
  v->as_form = f;
  return f;
}

const char *lg_parse(struct lg_pos *pos,
		     const char *in,
		     struct lg_stack *out,
		     struct lg_vm *vm) {
  do {
    in = lg_parse_form(pos, lg_skip(pos, in), out, vm);
  } while (in && *in);

  return in;
}

const char *lg_parse_form(struct lg_pos *pos,
			  const char *in,
			  struct lg_stack *out,
			  struct lg_vm *vm) {
  char c = *in;

  switch (c) {
  case 0:
    return in;
  case '(':
    return lg_parse_group(pos, in, out, vm);
  }

  if (isdigit(c)) {
    return lg_parse_int(pos, in, out, vm);
  }

  return lg_parse_id(pos, in, out, vm);
}

const char *lg_parse_group(struct lg_pos *pos,
			   const char *in,
			   struct lg_stack *out,
			   struct lg_vm *vm) {
  char c = *in;

  if (c != '(') {
    lg_error(vm, *pos, LG_ESYNTAX, "Invalid group: %c (%d)", c, (int)c);
    return NULL;
  }

  struct lg_stack *g = &push_form(*pos, LG_GROUP, out)->as_group;
  lg_stack_init(g, NULL);
  
  in++;
  pos->col++;

  do {
    in = lg_skip(pos, in);
    
    if (*in == ')') {
      pos->col++;
      return ++in;
    }

    in = lg_parse_form(pos, in, g, vm);
  } while (*in);

  lg_error(vm, *pos, LG_ESYNTAX, "Open group");
  return NULL;
}

const char *lg_parse_id(struct lg_pos *pos,
			const char *in,
			struct lg_stack *out,
			struct lg_vm *vm) {
  const char *start = in;
  struct lg_pos start_pos;
  lg_pos_copy(pos, &start_pos);

  while (*in && !isspace(*in)) {
    in++;
    pos->col++;
  }

  size_t l = in - start;
  char name[l + 1];
  name[l] = 0;
  strncpy(name, start, l);
  struct lg_str s;
  lg_str_init(&s, name);
  struct lg_val *v = lg_get(vm->env, &s);

  if (v && v->type == &lg_macro_type && !(in = lg_macro_parse(v->as_macro, pos, in, out, vm))) {
    return NULL;
  }
	
  push_form(start_pos, LG_ID, out)->as_id = s;
  lg_pos_deinit(&start_pos);
  return in;
}

static int char_int(char c, int base) {
  if (isdigit(c)) {
    return c - '0';
  }

  if (base == 16 && c >= 'a' && c <= 'f') {
    return 10 + c - 'a';
  }

  return -1;
}

const char *lg_parse_int(struct lg_pos *pos,
			 const char *in,
			 struct lg_stack *out,
			 struct lg_vm *vm) {
  int64_t v = 0;
  int base = 10;

  if (*in == '0') {
    in++;
    pos->col++;

    switch (*in) {
    case 'b':
      base = 2;
      in++;
      pos->col++;
      break;
    case 'x':
      base = 16;
      in++;
      pos->col++;
      break;
    }
  }

  char c = 0;

  while ((c = *in)) {
    const int cv = char_int(c, base);

    if (cv == -1) {
      break;
    }
    
    v = v * base + cv;
    in++;
    pos->col++;
  }

  lg_val_init(lg_push(out), *pos, &lg_int64_type)->as_int64 = v;
  return in;
}

const char *lg_skip(struct lg_pos *pos, const char *in) {
  for (;;) {
    switch (*in) {
    case ' ':
      in++;
      pos->col++;
      break;
    case '\n':
      in++;
      pos->row++;
      pos->col = 0;
      break;
    default:
      return in;
    }
  }
}
