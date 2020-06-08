#ifndef LG_BSET_H
#define LG_BSET_H

#include <stdbool.h>

#include "lg/cmp.h"
#include "lg/slab.h"

typedef void *(*lg_bset_key_t)(const void *); 

struct lg_bset {
  size_t size;
  struct lg_slab items;
  lg_cmp_t cmp;
  lg_bset_key_t key;
  int refs;
};

struct lg_bset *lg_bset_new(size_t size, lg_cmp_t cmp);
struct lg_bset *lg_bset_init(struct lg_bset *bset, size_t size, lg_cmp_t cmp);
void lg_bset_deinit(struct lg_bset *bset);
size_t lg_bset_find(struct lg_bset *bset, void *key, bool *ok);
size_t lg_bset_len(struct lg_bset *bset);
void *lg_bset_get(struct lg_bset *bset, void *key);
void *lg_bset_add(struct lg_bset *bset, void *key);

#endif
