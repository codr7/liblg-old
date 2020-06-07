#include <stdlib.h>
#include <string.h>

#include "lg/util.h"

char *lg_strdup(const char *in) {
  const size_t len = strlen(in) + 1;
  char *out = malloc(len);
  strcpy(out, in);
  return out;
}
