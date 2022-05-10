#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "hash.h"
#include "list.h"
#include "cache_storage.h"
#include "stack.h"

#define LEN_CACHE 6
#define LEN_LIR 3

void fgetdata(void *cacheunit, int filenumber) {
    ((char *)cacheunit) [0] = filenumber % 10 + '0';
}
void iteration(int name, int len_LIR, struct stack stack, struct list list, struct element_hash **hash, struct  cache_storage_t *cachestorage);

int main() {

    struct cache_storage_t *cachestorage = cache_storage_init(LEN_CACHE, 5, fgetdata);

    struct stack stack;
    (stack.upper_element) = (struct dlinked_list_element **) calloc(1, sizeof(struct dlinked_list_element *));
    (stack.down_element) = (struct dlinked_list_element **) calloc(1, sizeof(struct dlinked_list_element *));
    struct list list;
    (list.upper_element) = (struct dlinked_list_element **) calloc(1, sizeof(struct dlinked_list_element *));
    (list.down_element) = (struct dlinked_list_element **) calloc(1, sizeof(struct dlinked_list_element *));

    struct element_hash **hash = make_hash();
    int input[10] = {1, 4, 2, 3, 2, 1, 4, 1, 5, 4};

    for (int i = 0; i < 11; ++i) {
        iteration(input[i], LEN_LIR, stack, list, hash, cachestorage);
        
    }

    
    free_hash(hash);
    free(hash);

    free(stack.upper_element);
    free(stack.down_element);
    free(list.upper_element);
    free(list.down_element);

    cache_storage_delete(cachestorage);

    return 0;
}

void iteration(int name, int len_LIR, struct stack stack, struct list list, struct element_hash **hash, struct  cache_storage_t *cachestorage) {
    char *ptr;

    ptr = LIRS_algorithm(name, len_LIR, stack, list, hash, cachestorage);
    cache_unit_change(cachestorage, ptr, name);
    printf("\n-------------------------------------------------------------------\n");
    cache_storage_data_print(cachestorage);
    print_hash(hash);
    printf("\n");
    printf("Stack:\n");
    print_stack_down(*stack.upper_element);
    printf("\nList:\n");
    if (*list.upper_element != NULL){
        print_stack_down(*list.upper_element); 
    }
}