/** 
 \file 
 \brief File with the implementation of functions from the header file and lirs_t struct.
*/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "all_objects.h"
#include "hash.h"
#include "stack.h"
#include "lirs.h"

/// The description of the lirs_t struct.
struct lirs_t {
	int lircapacity; ///< The size of LIR part of cache.
	int hircapacity; ///< The size of HIR part of cache.
	struct cache_storage_t *cachestorage; ///< The pointer on cache storage where all files will be written. 
	struct stack stack; ///< The struct that will be used to interact with stack.
	struct list list; ///< The struct that will be used to interact with list.
	struct element_hash **hash; ///< The pointer on required hashmap.

    unsigned long long count_of_rewritings; ///< The total number of rewritings of files.
    unsigned long long count_of_accessing; ///< The total number of accessings of files.
};

struct lirs_t *lirs_init(int lircapacity, int hircapacity, int datasize, fgetdata_t fgetdata) {
    struct lirs_t *lirs = calloc(1, sizeof(struct lirs_t));
    if (lirs == NULL) {
        abort();
    }
        
	lirs->lircapacity = lircapacity;
	lirs->hircapacity = hircapacity;

	lirs->cachestorage = cache_storage_init(lircapacity + hircapacity, datasize, fgetdata);
    
    ((lirs->stack).upper_element) = (struct dlinked_list_element **) calloc(1, sizeof(struct dlinked_list_element *));
    if (((lirs->stack).upper_element) == NULL)
        abort();
    ((lirs->stack).down_element) = (struct dlinked_list_element **) calloc(1, sizeof(struct dlinked_list_element *));
    if (((lirs->stack).down_element) == NULL)
        abort();

    ((lirs->list).upper_element) = (struct dlinked_list_element **) calloc(1, sizeof(struct dlinked_list_element *));
    if (((lirs->list).upper_element) == NULL)
        abort();
    ((lirs->list).down_element) = (struct dlinked_list_element **) calloc(1, sizeof(struct dlinked_list_element *));
    if (((lirs->list).down_element) == NULL)
        abort();

    lirs->hash = make_hash();

    lirs->count_of_rewritings = 0;
    lirs->count_of_accessing = 0;

    return lirs;
}

void lirs_delete(struct lirs_t *lirs) {
	free_hash(lirs->hash);
    
    free(lirs->stack.upper_element);
    free(lirs->stack.down_element);
    
    free(lirs->list.upper_element);
    free(lirs->list.down_element);

    cache_storage_delete(lirs->cachestorage);

    free(lirs);
}

void *lirs_getfile(struct lirs_t *lirs, int filenumber) {
	char *ptr;
    ++(lirs->count_of_accessing);
    ptr = LIRS_algorithm(filenumber, lirs->lircapacity, lirs->stack, lirs->list, lirs->hash, lirs->cachestorage);
    if (ptr != NULL)
        ++(lirs->count_of_rewritings);
    cache_unit_change(lirs->cachestorage, ptr, filenumber);

    struct dlinked_list_element *objptr = find_element(filenumber, lirs->hash, List);
    if (objptr == NULL)
    	objptr = find_element(filenumber, lirs->hash, Stack);
    ptr = objptr->element.location_in_cache;

    return ptr;
}

void *lirs_getfilewithlog(struct lirs_t *lirs, int filenumber) {
    char *ptr = lirs_getfile(lirs, filenumber);

    printf("\n-------------------------------------------------------------------\n");
    cache_storage_data_print(lirs->cachestorage);
    print_hash(lirs->hash);
    printf("\n");
    printf("Stack:\n");
    print_stack_down(*lirs->stack.upper_element);
    printf("\nList:\n");
    if (*lirs->list.upper_element != NULL){
        print_stack_down(*lirs->list.upper_element); 
    }
    
    return ptr;
}

float get_rate_of_lirs_cache_missing(struct lirs_t *lirs) {
    if (cache_storage_isfull(lirs->cachestorage) == 0)
        return cache_storage_used(lirs->cachestorage) / (float) lirs->count_of_accessing;
    return (lirs->count_of_rewritings + cache_storage_used(lirs->cachestorage)) / (float) lirs->count_of_accessing;
}

unsigned long long get_count_of_lirs_cache_hit(struct lirs_t *lirs) {
    if (cache_storage_isfull(lirs->cachestorage) == 0)
        return lirs->count_of_accessing - cache_storage_used(lirs->cachestorage);
    return lirs->count_of_accessing - (lirs->count_of_rewritings + cache_storage_used(lirs->cachestorage));
}