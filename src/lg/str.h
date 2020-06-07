#ifndef LG_STR_H
#define LG_STR_H

#include <stdbool.h>
#include <stddef.h>

struct lg_str {
  char *data;
  size_t len;
  int refs;
};

struct lg_str *lg_str_new(const char *data);
struct lg_str *lg_str_init(struct lg_str *str, const char *data);
void lg_str_deinit(struct lg_str *str);
bool lg_str_deref(struct lg_str *str);

#endif
