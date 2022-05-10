#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "hash.h"
#include "stack.h"
#include "list.h"


void new_in_list(int name, void *location_in_cash, struct list list, struct element_hash **hash) {
    
    //assert(location_in_cash != NULL);

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

struct element add_in_list(int name, struct list list, struct element_hash **hash) {

    void *loc_in_cash = (*list.down_element)->element.location_in_cache;
    struct element del_elem = (*list.down_element)->element;
    struct dlinked_list_element *new_down_in_list = (*list.down_element)->previous;

    (new_down_in_list)->next = NULL;
    delete_element(list.down_element, hash);
    
    new_in_list(name, loc_in_cash, list, hash);
    
    *list.down_element = new_down_in_list;
    
    change_in_hash(name, (*list.upper_element), hash, List);

    return del_elem;
}

struct element move_up_list(int name, struct list list, struct element_hash **hash) { // Не лучше ли передавать сам элемент? Мне нужен location in cash старого


    assert((*list.upper_element)->next != NULL);
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
    move_elem->next = (*list.upper_element);
    (*list.upper_element)->previous = move_elem; 

    *list.upper_element = move_elem;
    
    return move_elem ->element;

}

void change_in_list(struct element add, int name_delite, struct list list, struct element_hash **hash) {

    struct dlinked_list_element *del_elem = find_element(name_delite, hash, List);

    del_elem->previous->next = del_elem->next;
    del_elem->next->previous = del_elem->previous;

    new_in_list(add.name, del_elem->element.location_in_cache, list, hash);
    delete_element(&del_elem, hash); 
}