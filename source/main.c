#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "lirs.h"


const int datasize = 2;

void fgetdata(void *cacheunit, int filenumber) {
    ((char *)cacheunit) [0] = filenumber % 10 + '0';
}

void input_configs(int *cachesize, int *filescount) {
    int k;
    k = scanf("%d %d", cachesize, filescount);
    if (k != 2)
        abort();
}

int input_filenumber() {
    int x, k;
    k = scanf("%d", &x);
    if (k != 1)
        abort();
    return x;
}

int main() {
    int cachesize, filescount;
    input_configs(&cachesize, &filescount);

    int lirsize, hirsize;
    hirsize = (cachesize + 3) / 4;
    lirsize = cachesize - hirsize;
    struct lirs_t *lirs = lirs_init(lirsize, hirsize, datasize, fgetdata);
    
    int i;
    for (i = 0; i < filescount; ++i)
        lirs_getfile(lirs, input_filenumber());
    
    printf("%llu\n", get_count_of_lirs_cache_hit(lirs));

    lirs_delete(lirs);
    return 0;
}
