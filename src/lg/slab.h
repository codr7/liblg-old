#ifndef LG_SLAB_H
#define LG_SLAB_H

#include <stddef.h>
#include <stdint.h>

#define LG_SLAB_N 3

struct lg_slab {
  size_t cap, len;
  uint8_t *slots;
};

struct lg_slab *lg_slab_init(struct lg_slab *slab);
void lg_slab_deinit(struct lg_slab *slab);
void lg_slab_grow(struct lg_slab *slab, size_t size, size_t cap);
void lg_slab_clear(struct lg_slab *slab);
void *lg_slab_get(struct lg_slab *slab, size_t size, size_t i);
void *lg_slab_push(struct lg_slab *slab, size_t size);
void *lg_slab_pop(struct lg_slab *slab, size_t size);
void *lg_slab_insert(struct lg_slab *slab, size_t size, size_t i);

#endif
