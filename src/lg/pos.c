#include "lg/pos.h"
#include "lg/str.h"

struct lg_pos LG_NIL_POS;

struct lg_pos *lg_pos_init(struct lg_pos *pos, const char *path, int16_t row, int16_t col) {
  pos->path = lg_str_new(path);
  pos->row = row;
  pos->col = col;
  return pos;
}

void lg_pos_deinit(struct lg_pos *pos) {
  lg_str_deref(pos->path);
}

void lg_pos_copy(struct lg_pos *src, struct lg_pos *dst) {
  dst->path = lg_str_ref(src->path);
  dst->row = src->row;
  dst->col = src->col;
}
