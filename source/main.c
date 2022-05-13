#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "lirs.h"

#define LEN_CACHE 3
#define LEN_LIR 2
#define DATASIZE 2

void fgetdata(void *cacheunit, int filenumber) {
    ((char *)cacheunit) [0] = filenumber % 10 + '0';
}

int main() {
    struct lirs_t *lirs = lirs_init(LEN_CACHE, LEN_CACHE - LEN_LIR, DATASIZE, fgetdata);

    int input[10] = {1, 4, 2, 3, 2, 1, 4, 1, 5, 4};

    for (int i = 0; i < 10; ++i)
        printf("%s\n", (char *) lirs_getfile(lirs, input[i]));

    lirs_delete(lirs);

    return 0;
}
