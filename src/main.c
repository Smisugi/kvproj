#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "kv.h"

int main(){
  printf("program start...");
  kv_t *db = kv_init(10);
  if (db == NULL) {
    printf("\nError, kv_init failed.");
    return 1;
  }
  printf("\ndb: %p\n", db);
  kv_get(db, "test");
  kv_free(db);
  return 0;
}
