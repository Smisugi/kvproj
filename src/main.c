#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "kv.h"

int main(){
  printf("program start...");
  kv_t *db = kv_init(3);
  if (db == NULL) {
    printf("\nError, kv_init failed.");
    return 1;
  }
  printf("\ndb: %p\n", db);
  printf("db entries: %p\n", db->entries);
  kv_put(db, "a", "first");
  kv_put(db, "b", "second");
  kv_put(db, "c", "third");
  kv_put(db, "d", "fourth");
  printf("running get... \nfound value: %s\n", kv_get(db, "a"));
  printf("capacity at: %d", db->capacity);
  kv_free(db);
  return 0;
}
