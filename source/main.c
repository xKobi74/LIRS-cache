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
The function that reads from the standard input two int numbers and writes them by pointers.
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
The function that read and return an int number from the standard input.
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
    int cachesize; // The variable that will be equal to total size of cache. 
    int filescount; // The variable that will be equeal to total count of requested files. 
    write_two_int(&cachesize, &filescount); // The input of two params.

    int lirsize, hirsize; // The variables that will be equal to total size of LIR and HIR parts of cache, respectively. 
    hirsize = (cachesize + 3) / 4; // Equating hirsize to a quarter of the total cache size with rounding up.
    lirsize = cachesize - hirsize; // Equating lirsize to to the remaining space in the cache (about three-quarters of it).
    struct lirs_t *lirs = lirs_init(lirsize, hirsize, datasize, fgetdata); // Сreating a lirs cache with the required parameters.
    
    /*
    Processing of all requested files. 
    */
    int i; // The iterator variable.
    for (i = 0; i < filescount; ++i) // The cycle for process all requested files.
        lirs_getfile(lirs, read_one_int()); // Processing of one (current) requested files.
    
    printf("%llu\n", get_count_of_lirs_cache_hit(lirs)); // The output of total count of cache hits.

    lirs_delete(lirs); // Free all memory that keeped by lirs struct.
    return 0;
}
