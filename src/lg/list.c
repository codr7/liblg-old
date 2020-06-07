#include "lg/list.h"

void lg_list_init(struct lg_list *list) {
  list->prev = list->next = list;
}

void lg_list_fix(struct lg_list *list) {
  list->prev->next = list->next->prev = list;
}

void lg_list_insert(struct lg_list *list, struct lg_list *item) {
  item->prev = list->prev;
  list->prev->next = item;
  item->next = list;
  list->prev = item;
}

struct lg_list *lg_list_remove(struct lg_list *list) {
  list->prev->next = list->next;
  list->next->prev = list->prev;
  return list;
}

void lg_list_push_front(struct lg_list *list, struct lg_list *item) {
  lg_list_insert(list->next, item);
}

struct lg_list *lg_list_pop_front(struct lg_list *list) {
  struct lg_list *i = list->next;
  return (i == list) ? NULL : lg_list_remove(i);
}

void lg_list_push_back(struct lg_list *list, struct lg_list *item) {
  lg_list_insert(list, item);
}

struct lg_list *lg_list_pop_back(struct lg_list *list) {
  struct lg_list *i = list->prev;
  return (i == list) ? NULL : lg_list_remove(i);
}
