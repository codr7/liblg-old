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

struct lg_pos *lg_pos_init(struct lg_pos *pos, const char *path, int16_t row, int16_t col);
void lg_pos_deinit(struct lg_pos *pos);

#endif