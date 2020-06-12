#ifndef LG_ERROR_H
#define LG_ERROR_H

#include <inttypes.h>
#include <stdbool.h>

#include "lg/str.h"

#define lg_error(vm, pos, type, spec, ...) ({				\
      _lg_error(vm,							\
		__FILE__, __LINE__,					\
		type,							\
		"Error in %s, line %" PRId16 ", column %" PRId16 "\n"	\
		spec,							\
		pos->path->data,					\
		pos->row,						\
		pos->col,						\
		## __VA_ARGS__, NULL);					\
    })

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

void _lg_error(struct lg_vm *vm,
	       const char *file, int line,
	       enum lg_error_type type,
	       const char *spec, ...);

#endif
