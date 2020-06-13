#ifndef LG_ENV_H
#define LG_ENV_H

#include "lg/bset.h"
#include "lg/val.h"
#include "lg/util.h"

#define _lg_env_do(env, binding, _i)					\
  size_t _i = 0;							\
  for (struct lg_binding *binding =					\
		(struct lg_binding *)(env)->bindings.items.slots;	\
  _i < (env)->bindings.items.len;					\
  _i++, binding++)

#define lg_env_do(env, binding)			\
  _lg_env_do(env, binding, lg_unique(i))

struct lg_binding {
  struct lg_str *key;
  struct lg_val val;
};

struct lg_env {
  struct lg_env *parent;
  struct lg_bset bindings;
  int16_t refs;
};

struct lg_env *lg_env_new(struct lg_env *parent);

struct lg_env *lg_env_init(struct lg_env *env, struct lg_env *parent);
void lg_env_deinit(struct lg_env *env);

struct lg_env *lg_env_ref(struct lg_env *env);
bool lg_env_deref(struct lg_env *env);

struct lg_val *lg_env_add(struct lg_env *env, struct lg_str *key, struct lg_type *type);
void lg_add_type(struct lg_env *env, struct lg_type *type);

#endif
