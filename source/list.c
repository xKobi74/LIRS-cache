#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "hash.h"
#include "stack.h"
#include "list.h"

// #include "../include/hash.h"
// #include "../include/stack.h"
// #include "../include/list.h"

#if 0
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

#endif

void new_in_list(int name, void *location_in_cash, struct list list, struct element_hash **hash) {

    assert(location_in_cash != NULL);

    struct dlinked_list_element *new_elem;
    new_elem = create_elem(name, location_in_cash);

    if ((*list.upper_element) == NULL) {
        *list.down_element = new_elem;
        *list.upper_element = new_elem;
        change_in_hash(name, new_elem, hash, List);
        return;
    }

    (*list.upper_element)->previous = new_elem;
    new_elem->next = *list.upper_element;
    *list.upper_element = new_elem;
    change_in_hash(name, new_elem, hash, List);
}

struct dlinked_list_element *create_elem(int name, void *location_in_cache) {

    assert(location_in_cache != NULL);

    struct dlinked_list_element *new_elem = (struct dlinked_list_element *)calloc(1, sizeof(struct dlinked_list_element));
    assert(new_elem != NULL);
    new_elem->element.name = name;
    new_elem->element.state_element = Resident_HIR;
    new_elem->element.location_in_cache = location_in_cache;
    new_elem->next = NULL;
    new_elem->previous = NULL;

    return new_elem;
}

void delete_element(struct dlinked_list_element **del_elem, struct element_hash **hash) {

    change_in_hash((*del_elem)->element.name, NULL, hash, List);
    free(*del_elem);
}

struct element add_in_list(int name, struct list list, struct element_hash **hash) {

    void *loc_in_cash = (*list.down_element)->element.location_in_cache;
    struct element delite = (*list.down_element)->element;    
    struct dlinked_list_element **del_elem;
    
    struct dlinked_list_element *new_down_in_list;
    del_elem = list.down_element;

    if ((*list.upper_element)->next == NULL) {
        new_in_list(name, loc_in_cash, list, hash);
        (*list.upper_element)->next = NULL;
        new_down_in_list = (*list.upper_element);
        
    }
    else {
        new_in_list(name, loc_in_cash, list, hash);
        new_down_in_list = (*list.down_element)->previous;
        (new_down_in_list)->next = NULL;
    }

    
    delete_element(del_elem, hash);
    *list.down_element = new_down_in_list;
    change_in_hash(name, (*list.upper_element), hash, List);

    return delite;
}

struct element move_up_list(int name, struct list list, struct element_hash **hash) {

    struct dlinked_list_element *move_elem = find_element(name, hash, List);
    assert(move_elem != NULL);

    if ((move_elem->previous) == NULL) {
        return move_elem->element;
    }
    if ((move_elem->next) != NULL) {
        (move_elem->next)->previous = move_elem->previous;
    }
    else {
        *list.down_element = move_elem->previous;
    }

    (move_elem->previous)->next = move_elem->next;
    move_elem->previous = NULL;
    move_elem->next = (*list.upper_element);
    (*list.upper_element)->previous = move_elem;

    *list.upper_element = move_elem;

    return move_elem->element;
}

void change_in_list(struct element add, int name_delite, struct list list, struct element_hash **hash) {

    struct dlinked_list_element *del_elem = find_element(name_delite, hash, List);
    new_in_list(add.name, del_elem->element.location_in_cache, list, hash);
    if ((del_elem->previous) != NULL) {
        del_elem->previous->next = del_elem->next;
    }
    if ((del_elem->next) != NULL) {
        del_elem->next->previous = del_elem->previous;
    }
    if ((del_elem->next) == NULL) {
        *list.down_element = del_elem->previous;
    }
    delete_element(&del_elem, hash);
}

#if 0
int main() {

    struct dlinked_list_element *upper = NULL;
    struct dlinked_list_element *down = NULL;
    struct element_hash **hash = make_hash();

    struct element change_elem;
    change_elem.name = 16;
    change_elem.location_in_cache = NULL;
    change_elem.state_element = Resident_HIR; 

    list.upper_element = &upper;
    list.down_element = &down;

    new_in_list(2, &change_elem.name, list, hash);
    new_in_list(1, &change_elem.name, list, hash);

    change_in_list(change_elem, 1, list, hash);

    // struct element check_struct;
    // check_struct.location_in_cache = NULL;
    // check_struct.name = 0;
    // check_struct.state_element = LIR;
 

    printf("------Print-down:\n");
    print_stack_down(upper);

    //printf("Return name after move: %d\n", check_struct.name);
    printf("\n");

    printf("------HASH\n");  

    print_hash(hash);

    free_hash(hash);
    free(hash);
    return 0;
 }
#endif
