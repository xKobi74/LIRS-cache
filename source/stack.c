#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "all_objects.h"
#include "hash.h"
#include "list.h"
#include "stack.h"

static void to_non_resident(int name, struct element_hash **hash);
static void free_element_stack(struct dlinked_list_element *element);
static char element_is_LIR(struct dlinked_list_element *down_element);
static void move_up_stack(struct stack stack, struct dlinked_list_element *lift_element);
static void only_in_list(int name, struct stack stack, struct list list, struct element_hash **hash);
static void *first_entry_in_full(int name, struct stack stack, struct list list, struct element_hash **hash);
static struct dlinked_list_element *clear_stack_to_LIR(struct dlinked_list_element *down_element, struct element_hash **hash);
static void *non_resident_in_stack(struct stack stack, struct list list, struct element_hash **hash, struct dlinked_list_element *in_stack);
static void *in_stack(int name, struct stack stack, struct list list, struct element_hash **hash, struct dlinked_list_element *element_in_stack);
static void resident_in_stack(int name, struct stack stack, struct list list, struct element_hash **hash, struct dlinked_list_element *in_stack);
static void *first_entery(int name, int len_LIR, struct stack stack, struct list list, struct element_hash **hash, struct  cache_storage_t *cache);
static void first_filling(int name, int len_LIR, struct stack stack, struct list list, struct element_hash **hash, struct  cache_storage_t *cache);
static void *not_in_stack(int name, int len_LIR, struct stack stack, struct list list, struct element_hash **hash, struct  cache_storage_t *cache);
static struct dlinked_list_element *new_upper_element(int name, enum state state_element, void *location_in_cache, 
                                               struct stack stack, struct element_hash **hash);

void *LIRS_algorithm(int name, int len_LIR, struct stack stack, struct list list, struct element_hash **hash, struct  cache_storage_t *cache) {

    struct dlinked_list_element *element_in_stack = find_element(name, hash, Stack);

    if (element_in_stack == NULL) {
        
        return not_in_stack(name, len_LIR, stack, list, hash, cache);
    }
    else {

        return in_stack(name, stack, list, hash, element_in_stack);  
    }
}

static void *in_stack(int name, struct stack stack, struct list list, struct element_hash **hash, struct dlinked_list_element *element_in_stack) {

    move_up_stack(stack, element_in_stack);
    
    if (element_in_stack->element.state_element == LIR) {
        
        *stack.down_element = clear_stack_to_LIR(*stack.down_element, hash);
        return NULL;
    }
    else if (element_in_stack->element.state_element == Resident_HIR) {

        resident_in_stack(name, stack, list, hash, element_in_stack);
        return NULL;
    }
    else {

        return non_resident_in_stack(stack, list, hash, element_in_stack);
    } 
}

static void *not_in_stack(int name, int len_LIR, struct stack stack, struct list list, struct element_hash **hash, struct  cache_storage_t *cache) {
    
    if (find_element(name, hash, List) == NULL) {
        
        return first_entery(name, len_LIR, stack, list, hash, cache);
    }
    else {
        
        only_in_list(name, stack, list, hash);
        return NULL;
    }
}

static void *first_entery(int name, int len_LIR, struct stack stack, struct list list, struct element_hash **hash, struct  cache_storage_t *cache) {
    if (cache_storage_isfull(cache) != 0) {

        return first_entry_in_full(name, stack, list, hash);
    }
    else {
        
        first_filling(name, len_LIR, stack, list, hash, cache);
        return NULL;
    }
}

static void first_filling(int name, int len_LIR, struct stack stack, struct list list, struct element_hash **hash, struct  cache_storage_t *cache) {
    
    struct dlinked_list_element *new;
    void *new_in_cash;

    new_in_cash = cache_unit_add(cache, name);
    assert(new_in_cash != NULL);
    
    if (cache_storage_used(cache) <= len_LIR) {

        new = new_upper_element(name, LIR, new_in_cash, stack, hash);
        change_in_hash(name, new, hash, Stack);
    }
    else {
        
        new = new_upper_element(name, Resident_HIR, new_in_cash, stack, hash);
        change_in_hash(name, new, hash, Stack);

        new_in_list(name, new_in_cash, list, hash);
    }

    *stack.upper_element = new;
}

static void *first_entry_in_full(int name, struct stack stack, struct list list, struct element_hash **hash) {

    struct element delete;
    struct dlinked_list_element *new;

    delete = add_in_list(name, list, hash);
    to_non_resident(delete.name, hash);
    
    new = new_upper_element(name, Resident_HIR, delete.location_in_cache, stack, hash);
    *stack.upper_element = new;

    change_in_hash(name, new, hash, Stack);

    return delete.location_in_cache;
}

static void only_in_list(int name, struct stack stack, struct list list, struct element_hash **hash) {
    
    struct dlinked_list_element *new;
    struct element move_up = move_up_list(name, list, hash);

    new = new_upper_element(name, Resident_HIR, move_up.location_in_cache, stack, hash);
    *stack.upper_element = new;

    change_in_hash(name, new, hash, Stack);
}

static void resident_in_stack(int name, struct stack stack, struct list list, struct element_hash **hash, struct dlinked_list_element *element_in_stack) {

    assert(element_in_stack != NULL);

    struct dlinked_list_element *down_elem = *stack.down_element;

    change_in_list(down_elem->element, name, list, hash);

    element_in_stack->element.state_element = LIR;

    down_elem->element.state_element = Resident_HIR;
    change_in_hash(down_elem->element.name, NULL, hash, Stack);

    *stack.down_element = clear_stack_to_LIR(down_elem, hash);
}

static void *non_resident_in_stack(struct stack stack, struct list list, struct element_hash **hash, struct dlinked_list_element *element_in_stack) {

    assert(element_in_stack != NULL);

    struct element delete;

    delete = add_in_list((*stack.down_element)->element.name, list, hash);
    to_non_resident(delete.name, hash);
    
    element_in_stack->element.state_element = LIR;

    (*stack.down_element)->element.state_element = Resident_HIR;
    change_in_hash((*stack.down_element)->element.name, NULL, hash, Stack);

    *stack.down_element = clear_stack_to_LIR(*stack.down_element, hash);

    return delete.location_in_cache;
}

static struct dlinked_list_element *new_upper_element(int name, enum state state_element, void *location_in_cache, struct stack stack, 
                                               struct element_hash **hash) {

    assert(location_in_cache != NULL);

    struct dlinked_list_element *new = (struct dlinked_list_element *) calloc(1, sizeof(struct dlinked_list_element));
    if (new == NULL)
        abort();

    if ((*stack.down_element) == NULL) {
        *stack.down_element = new;
    }
    if ((*stack.upper_element) != NULL) {
        (*stack.upper_element)->previous = new;
    }

    new->previous = NULL;
    new->next = (*stack.upper_element);

    new->element.name = name;
    new->element.state_element = state_element;
    new->element.location_in_cache = location_in_cache;

    change_in_hash(name, new, hash, Stack);

    return new;    
}

static void move_up_stack(struct stack stack, struct dlinked_list_element *lift_element) {

    assert(stack.upper_element != NULL);
    assert(stack.down_element != NULL);

    struct dlinked_list_element *upper_elem = *stack.upper_element;

    assert(*stack.down_element != NULL);
    assert(upper_elem != NULL);
    assert(lift_element != NULL);

    if (*stack.upper_element == lift_element)
        return;

    if (*stack.down_element == lift_element) {
        *stack.down_element = lift_element->previous;
    }

    (lift_element->previous)->next = lift_element->next;
    if (lift_element->next != NULL) {
        (lift_element->next)->previous = lift_element->previous;
    }

    upper_elem->previous = lift_element;

    lift_element->previous = NULL;
    lift_element->next = upper_elem;

    *stack.upper_element = lift_element;
}

static char element_is_LIR(struct dlinked_list_element *down_element) {
    
    assert(down_element != NULL);
    
    if (down_element->element.state_element == LIR) {
        return 1;
    }
    return 0;
}

static struct dlinked_list_element *clear_stack_to_LIR(struct dlinked_list_element *down_element, struct element_hash **hash) {
    
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

static void free_element_stack(struct dlinked_list_element *element) {

    assert(element != NULL);
    
    free(element);
}

static void to_non_resident(int name, struct element_hash **hash) {
    
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