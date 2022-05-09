#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "hash.h"
#include "list.h"

#if 1  //Functions for print list for debug
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

void new_in_list(int name, void *location_in_cash, struct dlinked_list_element **upper_in_list, struct dlinked_list_element **down_in_list, struct element_hash **hash) {
    
    //assert(location_in_cash != NULL);

    struct dlinked_list_element *new_elem;
    new_elem = create_elem(name, location_in_cash);

    if ((*upper_in_list) == NULL) {
        *down_in_list = new_elem;
        *upper_in_list = new_elem;
        change_in_hash(name, new_elem, hash, List);
        return;
    }

    (*upper_in_list)->previous = new_elem;
    new_elem->next = *upper_in_list;
    *upper_in_list = new_elem;
    change_in_hash(name, new_elem, hash, List);
}

struct dlinked_list_element *create_elem(int name, void *location_in_cache) {

    //assert(location_in_cache != NULL);

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
    free((*del_elem)->element.location_in_cache);
    free(*del_elem);
}

struct element add_in_list(int name, struct dlinked_list_element **upper_in_list, struct dlinked_list_element **down_in_list , struct element_hash **hash) {

    void *loc_in_cash = (*down_in_list)->element.location_in_cache;
    struct element del_elem = (*down_in_list)->element;
    struct dlinked_list_element *new_down_in_list = (*down_in_list)->previous;

    (new_down_in_list)->next = NULL;
    delete_element(down_in_list, hash);
    
    new_in_list(name, loc_in_cash, upper_in_list, NULL, hash);
    
    *down_in_list = new_down_in_list;
    
    change_in_hash(name, (*upper_in_list), hash, List);

    return del_elem;
}

struct element move_up_list(int name, struct dlinked_list_element **upper_in_list, struct element_hash **hash) { // Не лучше ли передавать сам элемент? Мне нужен location in cash старого


    assert((*upper_in_list)->next != NULL);
    struct dlinked_list_element *move_elem = find_element(name, hash, List); 
    assert(move_elem != NULL);

    if ((move_elem->previous) == NULL){
        return move_elem->element;
    }

    if ((move_elem->next)!= NULL){
        (move_elem->next)->previous = move_elem->previous;
    }
    
    (move_elem->previous)->next = move_elem->next;

    move_elem->previous = NULL;
    move_elem->next = (*upper_in_list);
    (*upper_in_list)->previous = move_elem; 

    *upper_in_list = move_elem;
    
    return move_elem ->element;

}

void change_in_list(struct element add, int name_delite, struct dlinked_list_element **upper_in_list, struct element_hash **hash) {

    struct dlinked_list_element *del_elem = find_element(name_delite, hash, List);

    del_elem->previous->next = del_elem->next;
    del_elem->next->previous = del_elem->previous;

    new_in_list(add.name, del_elem->element.location_in_cache, upper_in_list, NULL, hash);
    delete_element(&del_elem, hash); 
}

#if 1
int main() {
    
    struct dlinked_list_element *upper = NULL;
    struct dlinked_list_element *down = NULL;
    struct element_hash **hash = make_hash();
    
    struct element change_elem;
    change_elem.name = 16;
    change_elem.location_in_cache = NULL;
    change_elem.state_element = Resident_HIR; 

    struct element check_struct;
    check_struct.location_in_cache = NULL;
    check_struct.name = 0;
    check_struct.state_element = LIR;


    new_in_list(1, NULL, &upper, &down, hash);
    new_in_list(2, NULL, &upper, &down, hash);
    new_in_list(3, NULL, &upper, &down, hash);
    new_in_list(4, NULL, &upper, &down, hash);
    new_in_list(5, NULL, &upper, &down, hash);

    printf("Before functions:\n");
    print_stack_down(upper);


    // check_struct = add_in_list(6, &upper, &down, hash);

    // printf("\n");
    // print_stack_down(upper);
    // printf("Return name after add: %d\n", check_struct.name);


    check_struct = move_up_list(3, &upper, hash);

    printf("\n");
    print_stack_down(upper);
    printf("Return name after move: %d\n", check_struct.name);


    printf("\n");  
    
    print_hash(hash);
    
    // printf("\n");
    // print_stack_down(upper);
    // printf("\n");
    // print_stack_up(down);

    free_hash(hash);
    free(hash);
    return 0;
}
#endif