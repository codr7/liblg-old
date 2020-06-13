#include <stdlib.h>
#include <string.h>

#include "lg/env.h"
#include "lg/str.h"
#include "lg/type.h"
#include "lg/types/meta.h"

struct lg_env *lg_env_new(struct lg_env *parent) {
  return lg_env_init(malloc(sizeof(struct lg_env)), parent);
}

static enum lg_cmp cmp(const void *x, const void *y) {
  const struct lg_str *xs = x, *ys = y;
  return strcmp(xs->data, ys->data);
}

static const void *key(const void *val) {
  const struct lg_binding *b = val;
  return b->key;
}

struct lg_env *lg_env_init(struct lg_env *env, struct lg_env *parent) {
  env->parent = parent ? lg_env_ref(parent) : NULL;
  lg_bset_init(&env->bindings, sizeof(struct lg_binding), cmp);
  env->bindings.key = key;
  env->refs = 1;
  return env;
}

void lg_env_deinit(struct lg_env *env) {
  if (env->parent) {
    lg_env_deref(env->parent);
  }
  
  lg_env_do(env, b) {
    lg_str_deref(b->key);
    lg_deref(&b->val);
  }
  
  lg_bset_deinit(&env->bindings);
}

struct lg_env *lg_env_ref(struct lg_env *env) {
  env->refs++;
  return env;
}

bool lg_env_deref(struct lg_env *env) {
  if (!--env->refs) {
    lg_env_deinit(env);
    free(env);
    return true;
  }

  return false;
}

struct lg_val *lg_env_add(struct lg_env *env, struct lg_str *key, struct lg_type *type) {
  struct lg_binding *b = lg_bset_add(&env->bindings, key);

  if (b == NULL) {
    return false;
  }

  b->key = key;
  return lg_val_init(&b->val, type);
}

void lg_add_type(struct lg_env *env, struct lg_type *type) {
  lg_env_add(env, lg_str_ref(type->id), &lg_meta_type)->as_meta = lg_type_ref(type);
}
