#include <stdlib.h>
#include <string.h>

#include "lg/slab.h"
#include "lg/util.h"

struct lg_slab *lg_slab_init(struct lg_slab *slab, size_t size) {
  slab->size = size;
  slab->cap = slab->len = 0;
  slab->slots = NULL;
  return slab;
}

void lg_slab_deinit(struct lg_slab *slab) {
  if (slab->slots) {
    free(slab->slots);
  }
}

void lg_slab_grow(struct lg_slab *slab, size_t cap) {
  slab->cap = cap ? cap : LG_SLAB_N;
  slab->slots = realloc(slab->slots, slab->size*(slab->cap+1));
}

void lg_slab_clear(struct lg_slab *slab) {
  slab->len = 0;
}

void *lg_slab_get(struct lg_slab *slab, size_t i) {
  return slab->slots ? lg_align(slab->slots, slab->size) + slab->size*i : NULL;
}

void *lg_slab_push(struct lg_slab *slab) {
  if (slab->len == slab->cap) {
    lg_slab_grow(slab, slab->cap*LG_SLAB_N);
  }

  return lg_slab_get(slab, slab->len++);
}

void *lg_slab_pop(struct lg_slab *slab) {
  if (!slab->len) {
    return NULL;
  }

  return lg_slab_get(slab, --slab->len);
}

void *lg_slab_insert(struct lg_slab *slab, size_t i) {
  if (i == slab->len) {
    return lg_slab_push(slab);
  }

  if (slab->len == slab->cap) {
    lg_slab_grow(slab, slab->cap*LG_SLAB_N);
  }

  uint8_t *const p = lg_slab_get(slab, i);
  memmove(p+slab->size, p, (slab->len-i)*slab->size);
  slab->len++;
  return p;
}

