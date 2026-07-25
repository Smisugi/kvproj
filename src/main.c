#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "kv.h"

int main(){
  printf("program start...\n");
  kv_t *db = kv_init(3);
  if (db == NULL) {
    printf("\nError, kv_init failed.");
    return 1;
  }
  kv_put(db, "a", "first");
  kv_put(db, "b", "second");
  kv_put(db, "c", "third");
  kv_put(db, "d", "fourth");
  printf("running get... \nfound value: %s\n", kv_get(db, "d"));
  printf("putting new val in existing key... %d", kv_put(db, "a", "newfirst"));
  printf("capacity at: %d\n", (int)db->capacity);
  kv_free(db);
  return 0;
}
