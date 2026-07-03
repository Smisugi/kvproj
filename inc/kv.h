#ifndef KV_H
#define KV_H

#include <stddef.h>

typedef struct {
  //def key as int and val as char
  char * key;
  char * val;
} kv_pair_t;

typedef struct {
  kv_pair_t *entries; //dynamic array, grows if needed
  size_t  count; //no. of entries currently stored
  size_t  capacity; //no. of allocated slots (can be > count)
} kv_t;


kv_t  *kv_init(size_t capacity);
int   kv_put(kv_t *db, const char *key, const char *value);
char *kv_get(kv_t *db, const char *key);
int   kv_delete(kv_t *db, const char *key);
void  kv_free(kv_t *db);

#endif
