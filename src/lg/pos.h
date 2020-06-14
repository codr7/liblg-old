#ifndef LG_POS_H
#define LG_POS_H

#include <inttypes.h>

#define LG_MIN_ROW 1
#define LG_MIN_COL 0

struct lg_str;

struct lg_pos {
  struct lg_str *path;
  int16_t row, col;
};

extern struct lg_pos LG_NIL_POS;

struct lg_pos *lg_pos_init(struct lg_pos *pos, const char *path, int16_t row, int16_t col);
void lg_pos_deinit(struct lg_pos *pos);
void lg_pos_copy(struct lg_pos *src, struct lg_pos *dst);

#endif
