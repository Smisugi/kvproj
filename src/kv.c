#include <stdlib.h>
#include <string.h>
#include "kv.h"

kv_t *kv_init(size_t capacity){
  //probably wrong but oh well
  size_t count = 0;
  size_t capacity = capacity;
  //malloc for kv_t
  char *kv_t = malloc(capacity * sizeof(*kv_t));
  if(kv_t == NULL){ //avoid deref NULL ptr
    printf("Error: Malloc failed for kv_t.");
    return -1;
  }

  //malloc for kv_pair_t
  char *kv_pair_t = malloc(capacity * sizeof(*kv_pair_t));
  if(kv_pair_t == NULL){
    printf("Error. Malloc failed for kv_pair_t.");
    return -1;
  }
  return NULL;
}

int kv_put(kv_t *db, const char *key, const char *value) {
    // Think through the cases:
    // - key already exists -> update its value (free old value, strdup new one)
    // - key doesn't exist, room available -> append new pair
    // - key doesn't exist, no room -> grow the array first (realloc), then append
    //
    // IMPORTANT: don't just store the `key`/`value` pointers you were given.
    // The caller might free or reuse that memory after this function returns.
    // You need your own copies -> strdup().
    return -1;
}

char *kv_get(kv_t *db, const char *key) {
    // linear scan for now (an array-backed store can't do better than O(n)
    // without adding a hash index - that's a good v2 upgrade later)
    return NULL;
}

int kv_delete(kv_t *db, const char *key) {
    // find the entry, free its key and value strings,
    // then shift everything after it left by one slot (or swap-with-last
    // if you don't care about order) and decrement count.
    return -1;
}

void kv_free(kv_t *db) {
    // free every key/value string, then the entries array, then db itself.
    // get the order right or you'll leak or double-free.
}
