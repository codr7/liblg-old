#ifndef LG_UTILS_H
#define LG_UTILS_H

#include <stddef.h>

#define lg_align(base, size) ({						\
      __auto_type _base = base;						\
      __auto_type _size = lg_min((size), _Alignof(max_align_t));	\
      (_base) + _size - ((ptrdiff_t)(_base)) % _size;			\
    })									\

#define lg_baseof(p, t, m) ({			\
      uint8_t *_p = (uint8_t *)p;		\
      _p ? ((t *)(_p - offsetof(t, m))) : NULL;	\
    })

#define _lg_id(x, y)				\
  x##y

#define lg_id(x, y)				\
  _lg_id(x, y)

#define lg_max(x, y) ({				\
      __auto_type _x = x;			\
      __auto_type _y = y;			\
      _x > _y ? _x : _y;			\
    })						\

#define lg_min(x, y) ({				\
      __auto_type _x = x;			\
      __auto_type _y = y;			\
      _x < _y ? _x : _y;			\
    })						\

#define lg_unique(x)				\
  lg_id(x, __COUNTER__)

char *lg_strdup(const char *in);

#endif
