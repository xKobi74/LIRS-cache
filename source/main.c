#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "hash.h"
#include "list.h"
#include "cache_storage.h"
#include "stack.h"

void fgetdata(void *cacheunit, int filenumber) {
    ((char *)cacheunit) [0] = filenumber % 10 + '0';
}

int main() {
    struct cache_storage_t *cachestorage = cache_storage_init(10, 5, fgetdata);

    return 0;
}