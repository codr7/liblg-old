#include <stdlib.h>

#include "lg/str.h"
#include "lg/util.h"

struct lg_str *lg_str(const char *data) {
  return lg_str_init(malloc(sizeof(struct lg_str)), data);
}

struct lg_str *lg_str_init(struct lg_str *str, const char *data) {
  str->data = lg_strdup(data, &str->len);
  str->refs = 1;
  return str;
}

void lg_str_deinit(struct lg_str *str) {
  free(str->data);
}

struct lg_str *lg_str_ref(struct lg_str *str) {
  str->refs++;
  return str;
}

bool lg_str_deref(struct lg_str *str) {
  if (!--str->refs) {
    lg_str_deinit(str);
    free(str);
    return true;
  }

  return false;
}
