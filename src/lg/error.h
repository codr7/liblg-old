#ifndef LG_ERROR_H
#define LG_ERROR_H

#include <inttypes.h>
#include <stdbool.h>

#include "lg/str.h"

struct lg_pos;
struct lg_vm;

enum lg_error_type {LG_ESYNTAX};

struct lg_error {
  enum lg_error_type type;
  char *message;
  int16_t refs;
};

struct lg_error *lg_error_new(enum lg_error_type type, char *message);
void lg_error_deinit(struct lg_error *error);

struct lg_error *lg_error_ref(struct lg_error *error);
bool lg_error_deref(struct lg_error *error);

void lg_error(struct lg_vm *vm,
	      struct lg_pos,
	      enum lg_error_type type,
	      const char *spec, ...);

#endif
