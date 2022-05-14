/** 
 \file 
 \brief File with the implementation of functions from the header file and static functions for the hash object
*/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "all_objects.h"
#include "hash.h"

#define LEN_HASH 5000 ///< Hash array length.

//--------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------
/**
Removes an element from a hash table collision.
    \param[in]      name The name of the input file.
    \param[in, out] hash The hash array in which changes will occur.
    \return 0 if the element was not found in the hash table.
    \return 1 if the element was found in the hash table and removed successfully.
*/
static char delete_element_hash(int name, struct element_hash **hash);

/**
Removes an element from a hash table collision.
    \param[in] name    The name of the input file.
    \param[in] address The address where the file is stored in the specified object.
    \param[in] object  The object whose address will be written.
    \return Pointer to the created element of the hash table
*/
static struct element_hash *new_element(int name, struct dlinked_list_element *address, enum what_object object);
//--------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------

struct element_hash **make_hash() {
    
    struct element_hash **hash;
    hash = (struct element_hash **) calloc(LEN_HASH, sizeof(struct element_hash *));
    if (hash == NULL)
        abort();

    return hash;
}

static struct element_hash *new_element(int name, struct dlinked_list_element *address, enum what_object object) {
    
    assert(address != NULL);

    struct element_hash *new;
    new = (struct element_hash *) calloc(1, sizeof(struct element_hash));
    if (new == NULL)
        abort();

    new->name = name;

    if (object == Stack) {
        new->stack = address;
    }
    else {
        new->list = address;
    }

    return new;
}

void change_in_hash(int name, struct dlinked_list_element *address, struct element_hash **hash, enum what_object object) {

    assert(hash != NULL);
    
    int number = abs(name % LEN_HASH);
    struct element_hash **current = &(hash[number]);

    while ((*current) != NULL) {
        if ((*current)->name == name) {
            if (object == Stack) {
                (*current)->stack = address;;
                return;
            }
            (*current)->list = address;
            return;
            
        }
        current = &((*current)->next);
    }

    (*current) = new_element(name, address, object);

}

struct dlinked_list_element *find_element(int name, struct element_hash **hash, enum what_object object) {
    
    assert(hash != NULL);
    
    int number = abs(name % LEN_HASH);
    struct element_hash *current = hash[number];

    while (current != NULL) {
        if (current->name == name) {
            if (object == Stack) {
                return current->stack;
            }
            return current->list;
        }
        current = current->next;
    }

    return NULL;
}

static char delete_element_hash(int name, struct element_hash **hash) {

    assert(hash != NULL);

    int number = abs(name % LEN_HASH);
    struct element_hash *current = hash[number];
    struct element_hash *previous = hash[number];

    while (current != NULL) {
        if (current->name == name) {
            free(current->list);
            free(current->stack);

            if (current != previous) {
                previous->next = current->next;
            }
            else {
                hash[number] = current->next;
            }
            
            free(current);

            return 1;
        }

        previous = current;
        current = current->next;
    }

    return 0;
}

void free_hash(struct element_hash **hash) {

    assert(hash != NULL);

    int delete = 0;

    for (int i = 0; i < LEN_HASH; ++i) {
        if (hash[i] != NULL) {

            while (hash[i] != NULL) {
                delete = delete_element_hash(hash[i]->name, hash);
                assert(delete == 1);
            }
        }
    }

    free(hash);
}

void print_hash(struct element_hash **hash) {

    struct element_hash *current;

    for (int i = 0; i < LEN_HASH; ++i) {
        if (hash[i] != NULL) {
            
            printf("Cell number: %d\n", i);
            current = hash[i];
            while (current != NULL) {
                printf("\tName: %d, Stack: %p, List: %p\n", current->name, (void *) current->stack, (void *) current->list);
                current = current->next;
            }
        
        }
    }
}