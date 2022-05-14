/**
\file
\brief File with main() and static functions for start.
*/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "lirs.h"

const int datasize = 2; ///< Maximum size in bytes of a single file that will be requested.

/** 
The required function that writes data of the requested file to cache by its number.
    \param[out] cacheunit The pointer on the location in bytes(char *) array where need to write data.
    \param[in] filenumber The unique number of the file which information will bw written.
*/
void fgetdata(void *cacheunit, int filenumber) {
    ((char *)cacheunit) [0] = abs(filenumber) % 10 + '0';
}

/** 
The function that reads and writes by pointers two int numbers from the standard input.
    \param[out] xptr The pointer on the int where need to write first number.
    \param[out] yptr The pointer on the int where need to write first number.
*/
static void write_two_int(int *xptr, int *yptr) {
    int k;
    k = scanf("%d %d", xptr, yptr);
    if (k != 2)
        abort();
}

/** 
The function that read an int numbers from the standard input.
    \return The number that was read.
*/
static int read_one_int() {
    int x, k;
    k = scanf("%d", &x);
    if (k != 1)
        abort();
    return x;
}

int main() {
    int cachesize, filescount;
    write_two_int(&cachesize, &filescount);

    int lirsize, hirsize;
    hirsize = (cachesize + 3) / 4;
    lirsize = cachesize - hirsize;
    struct lirs_t *lirs = lirs_init(lirsize, hirsize, datasize, fgetdata);
    
    int i;
    for (i = 0; i < filescount; ++i)
        lirs_getfile(lirs, read_one_int());
    
    printf("%llu\n", get_count_of_lirs_cache_hit(lirs));

    lirs_delete(lirs);
    return 0;
}
