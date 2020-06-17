#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "lg/stream.h"

struct lg_stream *lg_stream_init(struct lg_stream *stream) {
  stream->data = NULL;
  stream->len = stream->cap = 0;
  return stream;
}

void lg_stream_deinit(struct lg_stream *stream) {
  if (stream->data) { free(stream->data); }
}

void lg_stream_reset(struct lg_stream *stream) {
  if (stream->data) {
    stream->len = 0;
    stream->data[0] = 0;
  }
}

void lg_stream_grow(struct lg_stream *stream, uint64_t len) {
  if (stream->cap) {
    while (stream->cap < len + 1) {
      stream->cap *= 2;
    }
  } else {
    stream->cap = len + 1;
  }

  stream->data = realloc(stream->data, stream->cap);
}

void lg_printf(struct lg_stream *stream, const char *spec, ...) {
  va_list args;
  va_start(args, spec);

  va_list len_args;
  va_copy(len_args, args);
  int len = vsnprintf(NULL, 0, spec, len_args);
  va_end(len_args);

  lg_stream_grow(stream, stream->len + len);
  vsnprintf(stream->data + stream->len, len + 1, spec, args);
  va_end(args);
  stream->len += len;
}

void lg_putc(struct lg_stream *stream, char value) {
  lg_stream_grow(stream, stream->len + 1);
  stream->data[stream->len++] = value;
  stream->data[stream->len] = 0;
}

void lg_puts(struct lg_stream *stream, const char *value) {
  size_t len = strlen(value);
  lg_stream_grow(stream, stream->len + len);
  strncpy(stream->data + stream->len, value, len+1);
  stream->len += len;
}

char *lg_getline(struct lg_stream *stream, FILE *in) {
  uint64_t start = stream->len;

  for (;;) {
    char c = fgetc(in);

    if (c == EOF) {
      break;
    }

    lg_putc(stream, c);

    if (c == '\n') {
      break;
    }
  }

  return stream->data + start;
}
