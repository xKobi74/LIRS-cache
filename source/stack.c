/** 
 \file 
 \brief File with the implementation of functions from the header file and static functions for the stack object.
*/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "all_objects.h"
#include "hash.h"
#include "list.h"
#include "stack.h"

/**
Removes a pointer to stack from the hash of the specified element and changes its status to Non_resident_HIR.
    \param[in]      name The name of the input file.
    \param[in, out] hash The hash table in which changes will occur.
    \return Void * pointer to the location in the cache where the incoming file should be written. NULL if the file has already been written.
*/
static void to_non_resident(int name, struct hash *hash);

/**
Releases an element from stack.
    \param[in] element Pointer to the element to be removed.
*/
static void free_element_stack(struct dlinked_list_element *element);

/**
Checks if the specified element has LIR status.
    \param[in] down_element Pointer to the down element of a doubly linked list.
    \return 0 if the element does not have the LIR status.
    \return 1 if the have the LIR status.
*/
static char element_is_LIR(struct dlinked_list_element *down_element);

/**
Implements the entire algorithm for writing elements to various program objects and clearing objects if necessary.
    \param[in, out] stack        The stack structure in which changes will occur.
    \param[in]      lift_element Pointer to the element to be raised on the stack.
*/
static void move_up_stack(struct stack stack, struct dlinked_list_element *lift_element);

/**
Implementation of a part of the algorithm when an element comes to the input that is written only in the list.
    \param[in]      name    The name of the input file.
    \param[in, out] stack   The stack structure in which changes will occur.
    \param[in, out] list    The list structure in which changes will occur.
    \param[in, out] hash    The hash table in which changes will occur.
*/
static void only_in_list(int name, struct stack stack, struct list list, struct hash *hash);

/**
Implementation of a part of the algorithm when an element comes to the input that is not stored in cache and the cache is full.
    \param[in]      name    The name of the input file.
    \param[in, out] stack   The stack structure in which changes will occur.
    \param[in, out] list    The list structure in which changes will occur.
    \param[in, out] hash    The hash table in which changes will occur.
    \return Void * pointer to the location in the cache where the incoming file should be written.
*/
static void *first_entry_in_full(int name, struct stack stack, struct list list, struct hash *hash);

/**
Implements the entire algorithm for writing elements to various program objects and clearing objects if necessary.
    \param[in, out] down_element Pointer to the down element of the stack.
    \param[in, out] hash         The hash table in which changes will occur.
    \return Pointer to the new down element in stack.
*/
static struct dlinked_list_element *clear_stack_to_LIR(struct dlinked_list_element *down_element, struct hash *hash);

/**
Implementation of a part of the algorithm when an element comes to the input that is written to the stack with the Non_resident_HIR status.
    \param[in, out] stack            The stack structure in which changes will occur.
    \param[in, out] list             The list structure in which changes will occur.
    \param[in, out] hash             The hash table in which changes will occur.
    \param[in, out] element_in_stack Pointer to the location of the incoming element on the stack.
    \return Void * pointer to the location in the cache where the incoming file should be written.
*/
static void *non_resident_in_stack(struct stack stack, struct list list, struct hash *hash, struct dlinked_list_element *element_in_stack);

/**
Implementation of a part of the algorithm when an element comes to the input that is written to the stack.
    \param[in]      name             The name of the input file.
    \param[in, out] stack            The stack structure in which changes will occur.
    \param[in, out] list             The list structure in which changes will occur.
    \param[in, out] hash             The hash table in which changes will occur.
    \param[in, out] element_in_stack Pointer to the location of the incoming element on the stack.
    \return Void * pointer to the location in the cache where the incoming file should be written.
*/
static void *in_stack(int name, struct stack stack, struct list list, struct hash *hash, struct dlinked_list_element *element_in_stack);

/**
Implementation of a part of the algorithm when an element comes to the input that is written to the stack with the Resident_HIR status.
    \param[in]      name    The name of the input file.
    \param[in, out] stack   The stack structure in which changes will occur.
    \param[in, out] list    The list structure in which changes will occur.
    \param[in, out] hash    The hash table in which changes will occur.
    \param[in, out] element_in_stack Pointer to the location of the incoming element on the stack.
*/
static void resident_in_stack(int name, struct stack stack, struct list list, struct hash *hash, struct dlinked_list_element *element_in_stack);

/**
Implementation of a part of the algorithm when an element comes to the input that is not stored in cache.
    \param[in]      name    The name of the input file.
    \param[in]      len_LIR Length of the LIR memory area.
    \param[in, out] stack   The stack structure in which changes will occur.
    \param[in, out] list    The list structure in which changes will occur.
    \param[in, out] hash    The hash table in which changes will occur.
    \param[in, out] cache   The cache array where all files are stored.
    \return Void * pointer to the location in the cache where the incoming file should be written.
*/
static void *first_entery(int name, int len_LIR, struct stack stack, struct list list, struct hash *hash, struct  cache_storage_t *cache);

/**
Implementation of a part of the algorithm when an element comes to the input that is not stored in cache and the cache is not yet full.
    \param[in]      name    The name of the input file.
    \param[in]      len_LIR Length of the LIR memory area.
    \param[in, out] stack   The stack structure in which changes will occur.
    \param[in, out] list    The list structure in which changes will occur.
    \param[in, out] hash    The hash table in which changes will occur.
    \param[in, out] cache   The cache array where all files are stored.
*/
static void first_filling(int name, int len_LIR, struct stack stack, struct list list, struct hash *hash, struct  cache_storage_t *cache);

/**
Implementation of a part of the algorithm when an element comes to the input that is not written to the stack.
    \param[in]      name    The name of the input file.
    \param[in]      len_LIR Length of the LIR memory area.
    \param[in, out] stack   The stack structure in which changes will occur.
    \param[in, out] list    The list structure in which changes will occur.
    \param[in, out] hash    The hash table in which changes will occur.
    \param[in, out] cache   The cache array where all files are stored.
    \return Void * pointer to the location in the cache where the incoming file should be written.
*/
static void *not_in_stack(int name, int len_LIR, struct stack stack, struct list list, struct hash *hash, struct  cache_storage_t *cache);

/**
Implementation of a part of the algorithm when an element comes to the input that is not written to the stack.
    \param[in]      name              The name of the input file.
    \param[in]      state_element     The state element to add.
    \param[in]      location_in_cache The address where the element is stored in the cache
    \param[in, out] stack             The stack structure in which changes will occur.
    \param[in, out] hash              The hash table in which changes will occur.
    \return Void * pointer to the location in the cache where the incoming file should be written.
*/
static struct dlinked_list_element *new_upper_element(int name, enum state state_element, void *location_in_cache, 
                                                      struct stack stack, struct hash *hash);

void *LIRS_algorithm(int name, int len_LIR, struct stack stack, struct list list, struct hash *hash, struct  cache_storage_t *cache) {

    struct dlinked_list_element *element_in_stack = find_element(name, hash, Stack);

    if (element_in_stack == NULL) {
        
        return not_in_stack(name, len_LIR, stack, list, hash, cache);
    }
    else {

        return in_stack(name, stack, list, hash, element_in_stack);  
    }
}

static void *in_stack(int name, struct stack stack, struct list list, struct hash *hash, struct dlinked_list_element *element_in_stack) {

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

static void *not_in_stack(int name, int len_LIR, struct stack stack, struct list list, struct hash *hash, struct  cache_storage_t *cache) {
    
    if (find_element(name, hash, List) == NULL) {
        
        return first_entery(name, len_LIR, stack, list, hash, cache);
    }
    else {
        
        only_in_list(name, stack, list, hash);
        return NULL;
    }
}

static void *first_entery(int name, int len_LIR, struct stack stack, struct list list, struct hash *hash, struct  cache_storage_t *cache) {
    if (cache_storage_isfull(cache) != 0) {

        return first_entry_in_full(name, stack, list, hash);
    }
    else {
        
        first_filling(name, len_LIR, stack, list, hash, cache);
        return NULL;
    }
}

static void first_filling(int name, int len_LIR, struct stack stack, struct list list, struct hash *hash, struct  cache_storage_t *cache) {
    
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

static void *first_entry_in_full(int name, struct stack stack, struct list list, struct hash *hash) {

    struct element delete;
    struct dlinked_list_element *new;

    delete = add_in_list(name, list, hash);
    to_non_resident(delete.name, hash);
    
    new = new_upper_element(name, Resident_HIR, delete.location_in_cache, stack, hash);
    *stack.upper_element = new;

    change_in_hash(name, new, hash, Stack);

    return delete.location_in_cache;
}

static void only_in_list(int name, struct stack stack, struct list list, struct hash *hash) {
    
    struct dlinked_list_element *new;
    struct element move_up = move_up_list(name, list, hash);

    new = new_upper_element(name, Resident_HIR, move_up.location_in_cache, stack, hash);
    *stack.upper_element = new;

    change_in_hash(name, new, hash, Stack);
}

static void resident_in_stack(int name, struct stack stack, struct list list, struct hash *hash, struct dlinked_list_element *element_in_stack) {

    assert(element_in_stack != NULL);

    struct dlinked_list_element *down_elem = *stack.down_element;

    change_in_list(down_elem->element, name, list, hash);

    element_in_stack->element.state_element = LIR;

    down_elem->element.state_element = Resident_HIR;
    change_in_hash(down_elem->element.name, NULL, hash, Stack);

    *stack.down_element = clear_stack_to_LIR(down_elem, hash);
}

static void *non_resident_in_stack(struct stack stack, struct list list, struct hash *hash, struct dlinked_list_element *element_in_stack) {

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
                                               struct hash *hash) {

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

static struct dlinked_list_element *clear_stack_to_LIR(struct dlinked_list_element *down_element, struct hash *hash) {
    
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

static void to_non_resident(int name, struct hash *hash) {
    
    struct dlinked_list_element *element = find_element(name, hash, Stack);
    
    if (element != NULL) {
        element->element.state_element = Non_resident_HIR;
        element->element.location_in_cache = NULL;
    }
}

void print_down(struct dlinked_list_element *upper_element) {
    
    assert(upper_element != NULL);

    struct dlinked_list_element *current = upper_element;
    
    printf("element: %d\n", current->element.name);

    while (current->next != NULL) {
        current = current->next;
        printf("element: %d\n", current->element.name);
    }
    
}

void print_up(struct dlinked_list_element *down_element) {
    
    assert(down_element != NULL);

    struct dlinked_list_element *current = down_element;
    
    printf("element: %d\n", current->element.name);

    while (current->previous != NULL) {
        current = current->previous;
        printf("element: %d\n", current->element.name);
    }
    
}
