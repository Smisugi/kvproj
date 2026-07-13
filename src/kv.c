#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "kv.h"

kv_t *kv_init(size_t capacity){
  //probably wrong but oh well

  kv_pair_t *new_pair = malloc(capacity * sizeof(kv_pair_t));
  if(new_pair == NULL){
    printf("Error: Malloc failed for kv_pair_t.");
    return NULL;
  }
  kv_t *new_db = malloc(sizeof(kv_t));
  //malloc for kv_t
  if(new_db == NULL){
    printf("Error: Malloc failed for kv_t.");
    return NULL;
  }
  new_db->count = 0;
  new_db->capacity = capacity;
  return new_db;
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

    //need to check if key exists, run get func
    if (kv_get(db, key) != NULL) { //does not exist in db
    }
    return -1;

}

char *kv_get(kv_t *db, const char *key) {
    // linear scan for now (an array-backed store can't do better than O(n)
    // without adding a hash index - that's a good v2 upgrade later)

    for (size_t i = 0; i < db->count; i++) { //linear for now, improve later
      if (strcmp(key, db->entries[i].key) == 0) {
        return db->entries[i].val;
      }
    }
    printf("Key not found.");
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
