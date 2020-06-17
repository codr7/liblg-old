#ifndef LG_STREAM_H
#define LG_STREAM_H

#include <stdint.h>
#include <stdio.h>

struct lg_stream {
  uint64_t cap, len;
  char *data;
};

struct lg_stream *lg_stream_init(struct lg_stream *stream);
void lg_stream_deinit(struct lg_stream *stream);

void lg_stream_reset(struct lg_stream *stream);
void lg_stream_grow(struct lg_stream *stream, uint64_t length);
void lg_printf(struct lg_stream *stream, const char *spec, ...);
void lg_putc(struct lg_stream *stream, char value);
void lg_puts(struct lg_stream *stream, const char *value);
char *lg_getline(struct lg_stream *stream, FILE *in);

#endif
