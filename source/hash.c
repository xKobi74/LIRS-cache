#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "hash.h"
#include "stack.h"

struct element_hash **make_hash() {
    
    struct element_hash **hash;
    hash = (struct element_hash **) calloc(len_hash, sizeof(struct element_hash *));
    assert(hash != NULL);

    return hash;
}

struct element_hash *new_element(int name, struct stack_element *address) {
    
    assert(address != NULL);

    struct element_hash *new;
    new = (struct element_hash *) calloc(1, sizeof(struct element_hash));
    assert(new != NULL);

    new->name = name;
    new->stack = address;
    new->next = NULL;

    return new;
}


void change_stack(int name, struct stack_element *address, struct element_hash **hash) {

    assert(hash != NULL);
    assert(address != NULL);
    
    int number = name % len_hash;
    struct element_hash **current = &(hash[number]);

    while ((*current) != NULL) {
        if ((*current)->name == name) {
            (*current)->stack = address;
            return;
        }
        current = &((*current)->next);
    }

    (*current) = new_element(name, address);

}

void change_list(int name, struct list_element *address, struct element_hash **hash) {

    assert(hash != NULL);
    assert(address != NULL);

    int number = name % len_hash;
    struct element_hash *current = hash[number];

    while (current != NULL) {
        if (current->name == name) {
            current->list = address;
            return;
        }
        current = current->next;
    }

    assert(current != NULL);

}

struct stack_element *element_in_stack(int name, struct element_hash **hash) {
    
    assert(hash != NULL);
    
    int number = name % len_hash;
    struct element_hash *current = hash[number];

    while (current != NULL) {
        if (current->name == name) {
            return current->stack;
        }
        current = current->next;
    }

    return NULL;
}

struct list_element *element_in_list(int name, struct element_hash **hash) {
    
    assert(hash != NULL);

    int number = name % len_hash;
    struct element_hash *current = hash[number];

    while (current != NULL) {
        if (current->name == name) {
            return current->list;
        }
        current = current->next;
    }

    return NULL;
}

char delete_element_hash(int name, struct element_hash **hash) {

    assert(hash != NULL);

    int number = name % len_hash;
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
