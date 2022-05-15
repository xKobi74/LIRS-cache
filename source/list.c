/** 
 \file 
 \brief File with the implementation of functions from the header file and static functions for the list object.
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "all_objects.h"
#include "hash.h"
#include "list.h"

/**
Created a new dlinked_list_element for list. Assigns it to him location_in_cash.
    \param[in] name The created element will have this name.
    \param[in] location_in_cache This will be assigned to element.location_in_cache.
    \return Pointer to the created dlinked_list_element.
*/
static struct dlinked_list_element *create_elem(int name, void *location_in_cache);

/**
Free element from list and changed information about it in hash.
    \param[in] del_elem This element will be deleted.
    \param[in] hash In hash will be changed info about the element.
*/
static void delete_element(struct dlinked_list_element **del_elem, struct hash *hash);


void new_in_list(int name, void *location_in_cash, struct list list, struct hash *hash) {

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

static struct dlinked_list_element *create_elem(int name, void *location_in_cache) {

    assert(location_in_cache != NULL);

    struct dlinked_list_element *new_elem = (struct dlinked_list_element *)calloc(1, sizeof(struct dlinked_list_element));
    if (new_elem == NULL)
        abort();
    assert(new_elem != NULL);
    new_elem->element.name = name;
    new_elem->element.state_element = Resident_HIR;
    new_elem->element.location_in_cache = location_in_cache;
    new_elem->next = NULL;
    new_elem->previous = NULL;

    return new_elem;
}

static void delete_element(struct dlinked_list_element **del_elem, struct hash *hash) {

    change_in_hash((*del_elem)->element.name, NULL, hash, List);
    free(*del_elem);
}

struct element add_in_list(int name, struct list list, struct hash *hash) {

    void *loc_in_cash = (*list.down_element)->element.location_in_cache;
    struct element delete = (*list.down_element)->element;    
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

    return delete;
}

struct element move_up_list(int name, struct list list, struct hash *hash) {

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

void change_in_list(struct element add, int name_delete, struct list list, struct hash *hash) {

    struct dlinked_list_element *del_elem = find_element(name_delete, hash, List);
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
