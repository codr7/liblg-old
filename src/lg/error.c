#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "lg/error.h"
#include "lg/types/error.h"
#include "lg/val.h"
#include "lg/vm.h"

struct lg_error *lg_error_new(enum lg_error_type type, char *message) {
  struct lg_error *e = malloc(sizeof(struct lg_error));
  e->type = type;
  e->message = message;
  e->refs = 1;
  return e;
}

void lg_error_deinit(struct lg_error *error) {
  free(error->message);
}

struct lg_error *lg_error_ref(struct lg_error *error) {
  error->refs++;
  return error;
}

bool lg_error_deref(struct lg_error *error) {
  if (!--error->refs) {
    lg_error_deinit(error);
    free(error);
    return true;
  }

  return false;
}

void _lg_error(struct lg_vm *vm,
	       const char *file, int line,
	       enum lg_error_type type,
	       const char *spec, ...) {
  va_list args;
  va_start(args, spec);

  if (vm->debug) {
    fprintf(stderr, "Error in %s, line %d\n", file, line);
    vfprintf(stderr, spec, args);
    abort();
  }

  va_list len_args;
  va_copy(len_args, args);
  int len = vsnprintf(NULL, 0, spec, len_args);
  va_end(len_args);

  if (len < 0) {
    fprintf(stderr, "Error in %s, line %d\n", file, line);
    fputs(spec, stderr);
    fputc('\n', stderr);
    abort();
  }

  len++;
  char *message = malloc(len);
  vsnprintf(message, len, spec, args);
  va_end(args);
  lg_val_init(lg_push(&vm->errors), &lg_error_type)->as_error = lg_error_new(type, message);
}
