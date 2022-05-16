/** 
 \file 
 \brief File with the implementation of functions from the header file and static functions for the hash object.
*/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <limits.h>

#include "all_objects.h"

#define MAX_RATIO 2         ///< The maximum possible ratio between the number of elements in the hash table list and the hash table array.
#define START_LEN_HASH 100000 ///< Start hash array length.

/**
Increases the length of the table's hash array by START_LEN_HASH, binds all the elements in the list, and binds them to the table. 
Clears elements that do not exist in any structure.
    \param[in, out] hash The hash table in which changes will occur.
*/
static void rehash(struct hash *hash);

/**
Releases all elements of the list hash table and pointers to the location of all elements in the rest of the objects.
    \param[in, out] hash The hash table in which changes will occur.
*/
static void free_list(struct hash *hash);

/**
Increases the length of the hash table array by START_LEN_HASH. Fills all elements with NULL.
    \param[in, out] hash The hash table in which changes will occur.
*/
static void realloc_hash(struct hash *hash);

/**
Checks if an element is in collision with hash value number.
    \param[in] name     The name of the element being checked.
    \param[in] capacity The current capacity of the hash table array.
    \param[in] number   Hash value number.
    \return 0 If element in not this collision.
    \return 1 If element in this collision.
*/
static inline char in_this_collision(int name, int capacity, int number);

/**
Removes an element from a hash table collision.
    \param[in] name    The name of the input file.
    \param[in] address The address where the file is stored in the specified object.
    \param[in] object  The object whose address will be written.
    \return Pointer to the created element of the hash table.
*/
static struct element_hash *new_element(int name, struct dlinked_list_element *address, enum what_object object);

/**
When rehashing, removes an element and rebinds pointers if that element is not used in other objects.
    \param[in, out] hash     The hash table in which changes will occur.
    \param[in, out] current  The current element in the hash table list.
    \param[in, out] previous The previous element in the hash table list.
*/
static void delete_element_list(struct hash *hash, struct element_hash **current, struct element_hash **previous);

/**
Creates an element in number collision where previously it was empty.
    \param[in]      name    The name of the input file.
    \param[in]      number  Hash value number.
    \param[in]      address The address where the file is stored in the specified object.
    \param[in, out] hash    The hash table in which changes will occur.
    \param[in]      object  The object whose address will be written.
*/
static void first_in_collision(int name, int number, struct dlinked_list_element *address, struct hash *hash, enum what_object object);



struct hash *make_hash() {
    
    struct hash *hash = (struct hash *) calloc(1, sizeof(struct hash));

    hash->capacity = START_LEN_HASH;

    hash->array = (struct element_hash **) calloc(START_LEN_HASH, sizeof(struct element_hash *));
    if (hash->array == NULL)
        abort();

    return hash;
}

static void rehash(struct hash *hash) {
    static int iteration = 0;
    printf("rehash: %d\n", ++iteration);

    realloc_hash(hash);

    struct element_hash *current = hash->list.top;
    struct element_hash *previous = hash->list.top;
    int number = 0;

    while (current != NULL) {
        number = abs(current->name % hash->capacity);

        if (current->list == NULL && current->stack == NULL) {
            delete_element_list(hash, &current, &previous);
        }
        else {
            if (hash->array[number] == NULL) {
                
                hash->size += 1;
                hash->array[number] = current;
                previous = current;
                current = current->next;
            }
            else {
                if (abs(previous->name % hash->capacity) == number) {
                    previous = current;
                    current = current->next;
                }
                else {
                    previous->next = current->next;
                    current->next = (hash->array[number])->next;
                    (hash->array[number])->next = current;
                    current = previous->next;
                }
            }
        }
    }
}

static void realloc_hash(struct hash *hash) {
    
    hash->capacity <<= 1;
    hash->size = 0;
    hash->array = (struct element_hash **) realloc(hash->array, (hash->capacity) * sizeof(struct element_hash *));
    if (hash->array == NULL) {
        abort();
    }

    for (int i = 0; i < hash->capacity; ++i) {
        hash->array[i] = NULL;
    }
}

static void delete_element_list(struct hash *hash, struct element_hash **current, struct element_hash **previous) {
    
    --hash->list.size;
    struct element_hash *temporary = *current;
    if (*current == *previous) {
        hash->list.top = (*current)->next;
        *previous = (*current)->next;
        *current = (*current)->next;
    }
    else {
        (*previous)->next = (*current)->next;
        *current = (*current)->next;
    }
    free(temporary);
}

void free_hash(struct hash *hash) {
    
    free_list(hash);
    free(hash->array);
    free(hash);
}

static void free_list(struct hash *hash) {
    
    struct element_hash *previous;
    struct element_hash *list_top = hash->list.top;

    while(list_top != NULL) {
        
        previous = list_top;
        list_top = list_top->next;
        
        free(previous->stack);
        free(previous->list);
        free(previous);
    }
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

static void first_in_collision(int name, int number, struct dlinked_list_element *address, struct hash *hash, enum what_object object) {
    
    struct element_hash *new = new_element(name, address, object);
    struct element_hash **top = &(hash->list.top);

    ++hash->size;
    ++hash->list.size;

    new->next = *top;
    *top = new;
    hash->array[number] = hash->list.top;
}

void change_in_hash(int name, struct dlinked_list_element *address, struct hash *hash, enum what_object object) {

    assert(hash != NULL);
    
    int number = abs(name % hash->capacity);

    if ((hash->array[number]) == NULL){
        
        first_in_collision(name, number, address, hash, object);
        return;
    }
    
    struct element_hash **current = &(hash->array[number]);
    struct element_hash **previous = current;
    
    while (*current != NULL && in_this_collision((*current)->name, hash->capacity, number)) {
        if ((*current)->name == name) {
            if (object == Stack) {
                (*current)->stack = address;;
                return;
            }
            (*current)->list = address;
            return;
            
        }
        previous = current;
        current = &((*current)->next);
    }
    
    struct element_hash *new = new_element(name, address, object);

    ++hash->list.size;
    new->next = *current;
    (*previous)->next = new;

    if (hash->capacity <= 2 * hash->size) {
        rehash(hash);
    }
}

static inline char in_this_collision(int name, int capacity, int number) {
    
    return (abs(name % capacity) == number);
}

struct dlinked_list_element *find_element(int name, struct hash *hash, enum what_object object) {
    
    assert(hash != NULL);
    
    int number = abs(name % hash->capacity);
    struct element_hash *current = hash->array[number];

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

void print_hash(struct hash *hash) {

    struct element_hash *current;

    for (int i = 0; i < hash->capacity; ++i) {
        if (hash->array[i] != NULL) {
            
            printf("Cell number: %d\n", i);
            current = hash->array[i];
            while (current != NULL && in_this_collision((current->name), (hash->capacity), i)) {
                printf("\tName: %d, Stack: %p, List: %p\n", current->name, (void *) current->stack, (void *) current->list);
                current = current->next;
            }
        
        }
    }
}
