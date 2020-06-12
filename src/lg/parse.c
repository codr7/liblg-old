#include <ctype.h>
#include <string.h>

#include "lg/error.h"
#include "lg/form.h"
#include "lg/parse.h"
#include "lg/pos.h"
#include "lg/stack.h"
#include "lg/types/form.h"
#include "lg/types/int64.h"
#include "lg/val.h"
#include "lg/util.h"

static struct lg_form *push_form(struct lg_stack *out, struct lg_pos pos, enum lg_form_type type) {
  struct lg_val *v = lg_val_init(lg_push(out), &lg_form_type);
  struct lg_form *f = lg_form_new(pos, type);
  v->as_form = f;
  return f;
}

static const char *skip(const char *in, struct lg_pos *pos) {
  for (;;) {
    switch (*in) {
    case ' ':
      in++;
      pos->col++;
      break;
    case '\n':
      in++;
      pos->row++;
      pos->col = LG_MIN_COL;
      break;
    default:
      return in;
    }
  }
}

const char *lg_parse(struct lg_vm *vm,
		     const char *in,
		     struct lg_pos *pos,
		     struct lg_stack *out) {
  do {
    in = lg_parse_form(vm, skip(in, pos), pos, out);
  } while (in && *in);

  return in;
}

const char *lg_parse_form(struct lg_vm *vm,
			  const char *in,
			  struct lg_pos *pos,
			  struct lg_stack *out) {
  char c = *in;

  switch (c) {
  case 0:
    return in;
  case '(':
    return lg_parse_group(vm, in, pos, out);
  }

  if (isdigit(c)) {
    return lg_parse_int(vm, in, pos, out);
  }

  return lg_parse_id(vm, in, pos, out);
}

const char *lg_parse_group(struct lg_vm *vm,
			   const char *in,
			   struct lg_pos *pos,
			   struct lg_stack *out) {
  char c = *in;

  if (c != '(') {
    lg_error(vm, pos, LG_ESYNTAX, "Invalid group: %c (%d)", c, (int)c);
    return NULL;
  }

  struct lg_stack *g = &push_form(out, *pos, LG_GROUP)->as_group;
  lg_stack_init(g);
  
  in++;
  pos->col++;

  do {
    in = skip(in, pos);
    
    if (*in == ')') {
      pos->col++;
      return ++in;
    }

    in = lg_parse_form(vm, in, pos, g);
  } while (*in);

  lg_error(vm, pos, LG_ESYNTAX, "Open group");
  return NULL;
}

const char *lg_parse_id(struct lg_vm *vm,
			const char *in,
			struct lg_pos *pos,
			struct lg_stack *out) {
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
  push_form(out, start_pos, LG_ID)->as_id = lg_strdup(name, NULL);
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

const char *lg_parse_int(struct lg_vm *vm,
			 const char *in,
			 struct lg_pos *pos,
			 struct lg_stack *out) {
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
    if (!isdigit(c)) {
      break;
    }

    const int cv = char_int(c, base);
    v = v * base + cv;
    in++;
    pos->col++;
  }

  lg_val_init(lg_push(out), &lg_int64_type)->as_int64 = v;
  return in;
}
