#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "hash.h"
#include "list.h"
#include "cache_storage.h"
#include "stack.h"
#include "lirs.h"

struct lirs_t {
	int lircapacity;
	int hircapacity;
	struct cache_storage_t *cachestorage;
	struct stack stack;
	struct list list;
	struct element_hash **hash;

    unsigned long long count_of_rewritings;
    unsigned long long count_of_accessing;
};

struct lirs_t *lirs_init(int lircapacity, int hircapacity, int datasize, fgetdata_t fgetdata) {
	struct lirs_t *lirs = calloc(1, sizeof(struct lirs_t));

	lirs->lircapacity = lircapacity;
	lirs->hircapacity = hircapacity;

	lirs->cachestorage = cache_storage_init(lircapacity + hircapacity, datasize, fgetdata);
    
    ((lirs->stack).upper_element) = (struct dlinked_list_element **) calloc(1, sizeof(struct dlinked_list_element *));
    ((lirs->stack).down_element) = (struct dlinked_list_element **) calloc(1, sizeof(struct dlinked_list_element *));
    
    ((lirs->list).upper_element) = (struct dlinked_list_element **) calloc(1, sizeof(struct dlinked_list_element *));
    ((lirs->list).down_element) = (struct dlinked_list_element **) calloc(1, sizeof(struct dlinked_list_element *));
    
    lirs->hash = make_hash();

    lirs->count_of_rewritings = 0;
    lirs->count_of_accessing = 0;

    return lirs;
}

void lirs_delete(struct lirs_t *lirs) {
	free_hash(lirs->hash);
    free(lirs->hash);
    
    free(lirs->stack.upper_element);
    free(lirs->stack.down_element);
    
    free(lirs->list.upper_element);
    free(lirs->list.down_element);

    cache_storage_delete(lirs->cachestorage);
}

void *lirs_getfile(struct lirs_t *lirs, int filenumber) {
	char *ptr;
    ++(lirs-> count_of_accessing);
    ptr = LIRS_algorithm(filenumber, lirs->lircapacity, lirs->stack, lirs->list, lirs->hash, lirs->cachestorage);
    if (ptr == NULL)
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
