#include <stdlib.h>

#include "lg/bset.h"
#include "lg/val.h"

struct lg_bset *lg_bset_new(size_t size, lg_cmp_t cmp) {
  return lg_bset_init(malloc(sizeof(struct lg_bset)), size, cmp);
}

struct lg_bset *lg_bset_init(struct lg_bset *bset, size_t size, lg_cmp_t cmp) {
  lg_slab_init(&bset->items, size);
  bset->cmp = cmp;
  bset->key = NULL;
  bset->refs = 1;
  return bset;
}

void lg_bset_deinit(struct lg_bset *bset) {
  lg_slab_deinit(&bset->items);
}

size_t lg_bset_find(struct lg_bset *bset, void *key, bool *ok) {
  size_t min = 0, max = bset->items.len;

  while (min < max) {
    const size_t i = (min+max)/2;
    const void *v = lg_slab_get(&bset->items, i);
    const void *k = bset->key ? bset->key(v) : v;

    switch (bset->cmp(key, k)) {
    case LG_LT:
      max = i;
      break;
    case LG_GT:
      min = i+1;
      break;
    default:
      if (ok) {
	*ok = true;
      }
      
      return i;
    }
  }

  return min;
}

size_t lg_bset_len(struct lg_bset *bset) {
  return bset->items.len;
}

void *lg_bset_get(struct lg_bset *bset, void *key) {
  bool ok = false;
  const size_t i = lg_bset_find(bset, key, &ok);
  return ok ? lg_slab_get(&bset->items, i) : NULL;
}

void *lg_bset_add(struct lg_bset *bset, void *key) {
  bool ok = false;
  const size_t i = lg_bset_find(bset, key, &ok);

  if (ok) {
    return NULL;
  }
  
  return lg_slab_insert(&bset->items, i);
}
