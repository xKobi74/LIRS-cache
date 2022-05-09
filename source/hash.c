#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "hash.h"
#include "stack.h"

const int len_hash = 5;

#if 0
int main() {
    
    struct element_hash *element;
    struct element_hash **hash = make_hash();
    struct dlinked_list_element a;

    change_in_hash(11, NULL, hash, Stack);
    change_in_hash(6, NULL, hash, Stack);
    change_in_hash(16, NULL, hash, Stack);
    change_in_hash(3, NULL, hash, Stack);
    change_in_hash(72, NULL, hash, Stack);
    change_in_hash(84, NULL, hash, Stack);
    change_in_hash(37, NULL, hash, Stack);
    //element = new_element(3, NULL);

    /*printf("adress 11: %p\n", (hash[1])->list);
    change_in_hash(11, &a, hash, List);
    printf("adress 11: %p\n", (hash[1])->list);
    printf("adress 11: %p\n", find_element(11, hash, List));*/

    printf("\n\n");
    print_hash(hash);
    printf("\n\n");

    printf("%d\n", hash[1]->name);
    printf("%d\n", (hash[1]->next)->name);
    printf("%d\n\n", ((hash[1]->next)->next)->name);

    free_hash(hash);

    printf("\n\n");
    print_hash(hash);
    printf("\n\n");

    //delete_element_hash(6, hash);
    //printf("%d\n", delete_element_hash(13, hash));
    //printf("%d\n", delete_element_hash(11, hash));

    //printf("%d\n", hash[1]->name);
    //printf("%d\n", (hash[1]->next)->name);   

    //delete_element_hash(16, hash); 

    //printf("%d\n", hash[1]->name);

    //delete_element_hash(11, hash);

    free(hash);

    return 0;
}
#endif

struct element_hash **make_hash() {
    
    struct element_hash **hash;
    hash = (struct element_hash **) calloc(len_hash, sizeof(struct element_hash *));
    assert(hash != NULL);

    return hash;
}

struct element_hash *new_element(int name, struct dlinked_list_element *address) {
    
    //assert(address != NULL);

    struct element_hash *new;
    new = (struct element_hash *) calloc(1, sizeof(struct element_hash));
    assert(new != NULL);

    new->name = name;
    new->stack = address;
    new->next = NULL;

    return new;
}


void change_in_hash(int name, struct dlinked_list_element *address, struct element_hash **hash, enum what_object object) {

    assert(hash != NULL);
    
    int number = name % len_hash;
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

    (*current) = new_element(name, address);

}

struct dlinked_list_element *find_element(int name, struct element_hash **hash, enum what_object object) {
    
    assert(hash != NULL);
    
    int number = name % len_hash;
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

void free_hash(struct element_hash **hash) {

    for (int i = 0; i < len_hash; ++i) {
        if (hash[i] != NULL) {

            while (hash[i] != NULL) {
                delete_element_hash(hash[i]->name, hash);
            }
        }
    }
}

void print_hash(struct element_hash **hash) {

    struct element_hash *current;

    for (int i = 0; i < len_hash; ++i) {
        if (hash[i] != NULL) {
            
            printf("Cell number: %d\n", i);
            current = hash[i];
            while (current != NULL) {
                printf("\tName: %d, Stack: %p, List: %p\n", current->name, current->stack, current->list);
                current = current->next;
            }
        
        }
    }
}