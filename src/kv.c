#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "kv.h"
#define _POSIX_C_SOURCE 200809L

kv_t *kv_init(size_t capacity){
  //probably wrong but oh well

  
  kv_t *new_db = malloc(sizeof(kv_t));
  //malloc for kv_t
  if(new_db == NULL){
    printf("Error: Malloc failed for kv_t.");
    return NULL;
  }
  
  new_db->entries = malloc(capacity * sizeof(kv_pair_t));
  if(new_db->entries == NULL){
    printf("Error: Malloc failed for kv_pair_t.");
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
    printf("new put\n");
    for (int i = 0; i < db->count; i++){
      if (strcmp(db->entries[i].key, key) == 0){
        free(db->entries[i].val);
        db->entries[i].val = strdup(value);
        return 1;
      }
    }
    //does not exist in db
    //if size exceeded (count == capacity)
    if (db->count == db->capacity){
      int new_capacity = (db->capacity == 0) ? 4 : db->capacity * 2;
      kv_pair_t *tmp = realloc(db->entries, new_capacity * sizeof(kv_pair_t));
      if (tmp == NULL) {
        printf("Error: realloc failed\n");
        return -1;
      }
      db->entries = tmp;
      db->capacity = new_capacity;
    }
      //else append new pair
    printf("appending new pair...\n");
    db->entries[db->count].key = strdup(key);
    if (db->entries[db->count].key == NULL){
      printf("Error: Malloc failed for key");
      return -1;
    }
        
    db->entries[db->count].val = strdup(value);
    if (db->entries[db->count].val == NULL){
      printf("Error: Malloc failed for val");
      return -1;
    }
    printf("append success\n");
    db->count++;
    return 1;
}


char *kv_get(kv_t *db, const char *key) {
    // linear scan for now (an array-backed store can't do better than O(n)
    // without adding a hash index - that's a good v2 upgrade later)

    for (size_t i = 0; i < db->count; i++) { //linear for now, improve later
      if (strcmp(key, db->entries[i].key) == 0) {
        return db->entries[i].val;
      }
    }
    return NULL;
}

int kv_delete(kv_t *db, const char *key) {
    // find the entry, free its key and value strings,
    // then shift everything after it left by one slot (or swap-with-last
    // if you don't care about order) and decrement count.
    
    //getter func
    for (size_t i = 0; i < db->count; i++){
      if (strcmp(db->entries[i].key, key) == 0){
          free(db->entries[i].key);
          free(db->entries[i].val);

          for (size_t j = i; j < db->count - 1; j++){
              db->entries[j] = db->entries[j-1];
          }
      }   
      db->count--;
      return 1;
    }
    printf("Error: Key not found.\n");
    return -1;
}

void kv_free(kv_t *db) {
    // free every key/value string, then the entries array, then db itself.
    // get the order right or you'll leak or double-free.
    for (size_t i = db->count - 1; i > 0; i--){
      printf("freeing value %s at index %ld", db->entries[i].val, i);
    
      free(db->entries[i].key);
      free(db->entries[i].val);
    }
    free(db->entries);
    free(db);
}
