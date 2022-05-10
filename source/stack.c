#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "hash.h"
#include "list.h"
//#include "cache_storage.h"
#include "stack.h"

#if 1
int main(){

    struct dlinked_list_element result;
    struct dlinked_list_element *res = NULL;
    struct dlinked_list_element *upper_element = NULL, *down_element = NULL;
    struct dlinked_list_element *upper_element_list = NULL, *down_element_list = NULL;
    struct element_hash **hash = make_hash();
    struct  cache_storage_t *cache;
    int len_Lir = 3;

    for (int i = 0; i < 10; ++i) {
        if (i == 0) {
            upper_element = new_upper_element(-1, LIR, NULL, &upper_element, &down_element, hash);
        }
        upper_element = new_upper_element(i, Resident_HIR, NULL, &upper_element, &down_element, hash);
        if (i >= 5) {
            upper_element->element.state_element = Non_resident_HIR;
        }
        if (i == 3) {
            upper_element = new_upper_element(15, LIR, NULL, &upper_element, &down_element, hash);
        }
        if (i == 5) {
            upper_element = new_upper_element(16, LIR, NULL, &upper_element, &down_element, hash);
        }
        if (i == 6) {
            upper_element = new_upper_element(22, LIR, NULL, &upper_element, &down_element, hash);
        }
    }

    for (int i = 0; i < 5; ++i) {
        new_in_list(i, NULL, &upper_element_list, &down_element_list, hash);
        if (i == 3){
            new_in_list(17, NULL, &upper_element_list, &down_element_list, hash);
            new_in_list(12, NULL, &upper_element_list, &down_element_list, hash);
        }

    }
    

    print_stack_down(upper_element);
    printf("\n");
    print_stack_up(down_element);
    printf("\n\n");
    print_stack_down(upper_element_list);
    printf("\n");
    print_stack_up(down_element_list);
    printf("\n");

    //printf("Delete: %p\n", stack(18, len_Lir, &upper_element, &down_element, hash, cache, &upper_element_list, &down_element_list));
    LIRS_algorithm(5, len_Lir, &upper_element, &down_element, hash, cache, &upper_element_list, &down_element_list);
    LIRS_algorithm(6, len_Lir, &upper_element, &down_element, hash, cache, &upper_element_list, &down_element_list);

    print_hash(hash);
    printf("\n");
    print_stack_down(upper_element);
    printf("\n\tstate:%d\n", upper_element->element.state_element);
    print_stack_down(upper_element_list);

    
    /*(15, len_Lir, &upper_element, &down_element, hash, cache, &upper_element_list, &down_element_list);

    printf("-------------up element 15-------------\n\n");
    print_hash(hash);
    printf("\n");
    print_stack_down(upper_element);
    printf("\nstate:%d\n", upper_element->element.state_element);
    print_stack_down(upper_element_list);
    printf("------------------end------------------\n\n");*/

    free_hash(hash);
    free(hash);

    /*struct dlinked_list_element result;
    struct dlinked_list_element *res = NULL;
    struct dlinked_list_element *element3, *down_at_all;
    struct element_hash **hash = make_hash();

    for (int i = 0; i < 10; ++i) {
        res = new_upper_element(i, Resident_HIR, NULL, res, hash);
        if (i == 3) {
            element3 = res;
        }
        if (i == 4) {
            res->element.state_element = LIR;
        }
        if (i == 0) {
            down_at_all = res;
        }
    }

    printf("Status: %d\n", find_element(8, hash, Stack)->element.state_element);
    to_non_resident(8, hash);
    printf("Status: %d\n", find_element(8, hash, Stack)->element.state_element);

    print_hash(hash);

    move_up_stack(res, element3);
    print_stack_down(element3);
    printf("\n");

    down_at_all = clear_stack_to_LIR(down_at_all, hash);

    print_hash(hash);

    print_stack_down(element3);
    printf("\n");
    print_stack_up(down_at_all);

    free_hash(hash);
    free(hash);*/


    return 0;
}
#endif

char cache_storage_isfull(struct  cache_storage_t *cache) {
    return 1;
}

void *cache_unit_add(struct  cache_storage_t *cache, int name) {
    return NULL;
}

int cache_storage_used(struct  cache_storage_t *cache) {
    return 2;
}

void *LIRS_algorithm(int name, int len_LIR, struct dlinked_list_element **upper_element, struct dlinked_list_element **down_element, struct element_hash **hash, struct  cache_storage_t *cache, struct dlinked_list_element **upper_in_list, struct dlinked_list_element **down_in_list) {

    struct dlinked_list_element *in_stack = find_element(name, hash, Stack);

    if (in_stack == NULL) {
        if (find_element(name, hash, List) == NULL) {
            if (cache_storage_isfull(cache) != 0) {

                return first_entry(name, upper_element, down_element, hash, upper_in_list, down_in_list);
            }
            else {
                
                first_filling(name, len_LIR, upper_element, down_element, hash, cache, upper_in_list, down_in_list);
                return NULL;
            }
        }
        else {
            
            only_in_list(name, upper_element, down_element, hash, upper_in_list);
            return NULL;
        }
    }
    else {

        move_up_stack(upper_element, down_element, in_stack);
    
        if (in_stack->element.state_element == LIR) {
            
            *down_element = clear_stack_to_LIR(*down_element, hash);
            return NULL;
        }
        else if (in_stack->element.state_element == Resident_HIR) {

            resident_in_stack(name, down_element, hash, upper_in_list, in_stack);
            return NULL;
        }
        else {

            return non_resident_in_stack(down_element, hash, upper_in_list, down_in_list, in_stack);
        }   
    }
}

void first_filling(int name, int len_LIR, struct dlinked_list_element **upper_element, struct dlinked_list_element **down_element, struct element_hash **hash, struct  cache_storage_t *cache, struct dlinked_list_element **upper_in_list, struct dlinked_list_element **down_in_list) {
    
    struct dlinked_list_element *new;
    void *new_in_cash;

    new_in_cash = cache_unit_add(cache, name);
    //assert(new_in_cash != NULL);
    
    if (cache_storage_used(cache) < len_LIR) {

        new = new_upper_element(name, LIR, new_in_cash, upper_element, down_element, hash);
        change_in_hash(name, new, hash, Stack);
    }
    else {
        
        new = new_upper_element(name, Resident_HIR, new_in_cash, upper_element, down_element, hash);
        change_in_hash(name, new, hash, Stack);

        new_in_list(name, new_in_cash, upper_in_list, down_in_list, hash);
    }

    *upper_element = new;
}

void *first_entry(int name, struct dlinked_list_element **upper_element, struct dlinked_list_element **down_element, struct element_hash **hash, struct dlinked_list_element **upper_in_list, struct dlinked_list_element **down_in_list) {

    struct element delete;
    struct dlinked_list_element *new;

    delete = add_in_list(name, upper_in_list, down_in_list, hash);
    to_non_resident(delete.name, hash);
    
    new = new_upper_element(name, Resident_HIR, delete.location_in_cache, upper_element, down_element, hash);
    *upper_element = new;

    change_in_hash(name, new, hash, Stack);

    return delete.location_in_cache;
}

void only_in_list(int name, struct dlinked_list_element **upper_element, struct dlinked_list_element **down_element, struct element_hash **hash, struct dlinked_list_element **upper_in_list) {
    
    struct dlinked_list_element *new;
    struct element move_up = move_up_list(name, upper_in_list, hash);

    new = new_upper_element(name, Resident_HIR, move_up.location_in_cache, upper_element, down_element, hash);
    *upper_element = new;

    change_in_hash(name, new, hash, Stack);
}

void resident_in_stack(int name, struct dlinked_list_element **down_element, struct element_hash **hash, struct dlinked_list_element **upper_in_list, struct dlinked_list_element *in_stack) {

    change_in_list((*down_element)->element, name, upper_in_list, hash);

    in_stack->element.state_element = LIR;

    (*down_element)->element.state_element = Resident_HIR;
    change_in_hash((*down_element)->element.name, NULL, hash, Stack);

    *down_element = clear_stack_to_LIR(*down_element, hash);
}

void *non_resident_in_stack(struct dlinked_list_element **down_element, struct element_hash **hash, struct dlinked_list_element **upper_in_list, struct dlinked_list_element **down_in_list, struct dlinked_list_element *in_stack) {

    struct element delete;

    delete = add_in_list((*down_element)->element.name, upper_in_list, down_in_list, hash);
    to_non_resident(delete.name, hash);
    
    in_stack->element.state_element = LIR;

    (*down_element)->element.state_element = Resident_HIR;
    change_in_hash((*down_element)->element.name, NULL, hash, Stack);

    *down_element = clear_stack_to_LIR(*down_element, hash);

    return delete.location_in_cache;
}

struct dlinked_list_element *new_upper_element(int name, enum state state_element, void *location_in_cache, struct dlinked_list_element **upper_element, struct dlinked_list_element **down_element, struct element_hash **hash) {

    struct dlinked_list_element *new = (struct dlinked_list_element *) calloc(1, sizeof(struct dlinked_list_element));

    if (*down_element == NULL) {
        *down_element = new;
    }
    if (*upper_element != NULL) {
        (*upper_element)->previous = new;
    }

    new->previous = NULL;
    new->next = (*upper_element);

    new->element.name = name;
    new->element.state_element = state_element;
    new->element.location_in_cache = location_in_cache;

    change_in_hash(name, new, hash, Stack);

    return new;    
}

void move_up_stack(struct dlinked_list_element **upper_element, struct dlinked_list_element **down_element, struct dlinked_list_element *lift_element) {

    assert(upper_element != NULL);
    assert(down_element != NULL);

    struct dlinked_list_element *upper_elem = *upper_element;

    assert(*down_element != NULL);
    assert(upper_elem != NULL);
    assert(lift_element != NULL);

    if (*down_element == lift_element) {
        *down_element = lift_element->previous;
    }

    (lift_element->previous)->next = lift_element->next;
    if (lift_element->next != NULL) {
        (lift_element->next)->previous = lift_element->previous;
    }

    upper_elem->previous = lift_element;

    lift_element->previous = NULL;
    lift_element->next = upper_elem;

    *upper_element = lift_element;
}

char element_is_LIR(struct dlinked_list_element *down_element) {
    
    assert(down_element != NULL);
    
    if (down_element->element.state_element == LIR) {
        return 1;
    }
    return 0;
}

struct dlinked_list_element *clear_stack_to_LIR(struct dlinked_list_element *down_element, struct element_hash **hash) {
    
    assert(down_element != NULL);

    struct dlinked_list_element *current = down_element, *previous;

    while (element_is_LIR(current) != 1) {
        
        previous = current->previous;
        change_in_hash(current->element.name, NULL, hash, Stack);
        free_element_stack(current);
        current = previous;
    }

    current->next = NULL;

    return current;
}

void free_element_stack(struct dlinked_list_element *element) {
    
    free(element->element.location_in_cache);
    free(element);
}

void to_non_resident(int name, struct element_hash **hash) {
    
    struct dlinked_list_element *element = find_element(name, hash, Stack);
    
    if (element != NULL) {
        element->element.state_element = Non_resident_HIR;
        element->element.location_in_cache = NULL;
    }
}

void print_stack_down(struct dlinked_list_element *upper_element) {
    
    assert(upper_element != NULL);

    struct dlinked_list_element *current = upper_element;
    
    printf("element: %d\n", current->element.name);

    while (current->next != NULL) {
        current = current->next;
        printf("element: %d\n", current->element.name);
    }
    
}

void print_stack_up(struct dlinked_list_element *down_element) {
    
    assert(down_element != NULL);

    struct dlinked_list_element *current = down_element;
    
    printf("element: %d\n", current->element.name);

    while (current->previous != NULL) {
        current = current->previous;
        printf("element: %d\n", current->element.name);
    }
    
}