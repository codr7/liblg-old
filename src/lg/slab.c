#include <stdlib.h>

#include "lg/slab.h"
#include "lg/util.h"

struct lg_slab *lg_slab_init(struct lg_slab *slab) {
  slab->cap = slab->len = 0;
  slab->slots = NULL;
  return slab;
}

void lg_slab_deinit(struct lg_slab *slab) {
  if (slab->slots) {
    free(slab->slots);
  }
}

void lg_slab_grow(struct lg_slab *slab, size_t size, size_t cap) {
  slab->slots = realloc(slab->slots, lg_align(0, size)*cap);
  slab->cap = cap;
}

void *lg_slab_push(struct lg_slab *slab, size_t size) {
  if (slab->len == slab->cap) {
    lg_slab_grow(slab, size, slab->cap ? slab->cap*LG_SLAB_N : LG_SLAB_N);
  }

  return slab->slots + lg_align(0, size)*slab->len++;
}

void *lg_slab_pop(struct lg_slab *slab, size_t size) {
  if (!slab->len) {
    return NULL;
  }

  return slab->slots + lg_align(0, size)*--slab->len;
}
