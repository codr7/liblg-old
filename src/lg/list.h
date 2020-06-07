#ifndef LG_LIST_H
#define LG_LIST_H

#include "lg/util.h"

#define _lg_list_do(list, i, _next)				\
  for (struct lg_list *i = (list)->next, *_next = i->next;	\
       i != (list);						\
       i = _next, _next = i->next)

#define lg_list_do(list, i)			\
  _lg_list_do(list, i, lg_unique(next))

struct lg_list {
  struct lg_list *prev, *next;
};

void lg_list_init(struct lg_list *list);
void lg_list_fix(struct lg_list *list);

void lg_list_insert(struct lg_list *list, struct lg_list *item);
struct lg_list *lg_list_remove(struct lg_list *list);

void lg_list_push_front(struct lg_list *list, struct lg_list *item);
struct lg_list *lg_list_pop_front(struct lg_list *list);

void lg_list_push_back(struct lg_list *list, struct lg_list *item);
struct lg_list *lg_list_pop_back(struct lg_list *list);

#endif
