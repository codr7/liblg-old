#include <stdlib.h>
#include <string.h>

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
  slab->cap = cap ? cap : LG_SLAB_N;
  slab->slots = realloc(slab->slots, lg_align(0, size)*slab->cap);
}

void *lg_slab_get(struct lg_slab *slab, size_t size, size_t i) {
  return slab->slots + lg_align(0, size)*i;
}

void *lg_slab_push(struct lg_slab *slab, size_t size) {
  if (slab->len == slab->cap) {
    lg_slab_grow(slab, size, slab->cap*LG_SLAB_N);
  }

  return lg_slab_get(slab, size, slab->len++);
}

void *lg_slab_pop(struct lg_slab *slab, size_t size) {
  if (!slab->len) {
    return NULL;
  }

  return lg_slab_get(slab, size, --slab->len);
}

void *lg_slab_insert(struct lg_slab *slab, size_t size, size_t i) {
  if (i == slab->len) {
    return lg_slab_push(slab, size);
  }

  if (slab->len == slab->cap) {
    lg_slab_grow(slab, size, slab->cap*LG_SLAB_N);
  }

  const size_t s = lg_align(0, size);
  uint8_t *const p = slab->slots + s*i;
  memmove(p+s, p, (slab->len-i)*s);
  slab->len++;
  return p;
}

