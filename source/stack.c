#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "stack.h"
#include "hash.h"
#include "cache_storage.h"
#include "list.h"

#if 0
int main(){

    struct dlinked_list_element result;
    struct dlinked_list_element *res = NULL;
    struct dlinked_list_element *element3, *down_at_all;
    struct element_hash **hash = make_hash();

    for (int i = 0; i < 10; ++i) {
        res = new_upper_element(i, Non_resident_HIR, NULL, res);
        if (i == 3) {
            element3 = res;
        }
        if (i == 4) {
            res->element.state_element = LIR;
        }
        if (i == 0) {
            down_at_all = res;
        }
    }

    /*new_upper_element(&result, 1, Non_resident_HIR, NULL, NULL);
    new_upper_element(&result1, 2, LIR, NULL, &result);
    new_upper_element(&result2, 18, Non_resident_HIR, NULL, &result1);
    new_upper_element(&result3, -7, Non_resident_HIR, NULL, &result2);
    new_upper_element(&result4, 12, Non_resident_HIR, NULL, &result3);
    */

    move_up_stack(res, element3);

    down_at_all = clear_stack_to_LIR(down_at_all, hash);


    print_stack_down(element3);
    printf("\n");
    print_stack_up(down_at_all);

    free_stack(element3, hash);

    return 0;
}
#endif


void *stack(int name, int len_LIR, struct dlinked_list_element **upper_element, struct dlinked_list_element **down_element, struct element_hash **hash, struct  cache_storage_t *cache, struct list_element **upper_in_list, struct list_element **penultimate_in_list) {
    
    struct dlinked_list_element *in_stack = find_element(name, hash, Stack);

    if (in_stack == NULL) {
        if (find_element(name, hash, List) == NULL) {
            if (cache_storage_isfull(cache) == 1) {
                
                struct element delete;
                struct dlinked_list_element *new;

                delete = add_in_list(name, upper_in_list, penultimate_in_list);
                to_non_resident(delete.name, hash);
                
                new = new_upper_element(name, Resident_HIR, delete.location_in_cache, *upper_element);
                *upper_element = new;

                change_in_hash(name, new, hash, Stack);

                return delete.location_in_cache;
            }
            else {
                
                struct dlinked_list_element *new;
                void *new_in_cash;

                new_in_cash = cache_unit_add(cache, name);
                
                if (cache_storage_used(cache) < len_LIR) {

                    new = new_upper_element(name, LIR, new_in_cash, *upper_element);
                    change_in_hash(name, new, hash, Stack);
                }
                else {
                    
                    new = new_upper_element(name, Resident_HIR, new_in_cash, *upper_element);
                    change_in_hash(name, new, hash, Stack);

                    new_in_list(name, new_in_cash, upper_in_list, penultimate_in_list);
                }

                *upper_element = new;
                
                return NULL;
            }
        }
        else {

            struct dlinked_list_element *new;
            struct element move_up = move_up_list(name, upper_in_list, penultimate_in_list);

            new = new_upper_element(name, Resident_HIR, move_up.location_in_cache, *upper_element);
            *upper_element = new;

            change_in_hash(name, new, hash, Stack);
            
            return NULL;
        }
    }
    else {
        
        move_up_stack(*upper_element, in_stack);
        *upper_element = in_stack;
        
        if (in_stack->element.state_element == LIR) {
            
            *down_element = clear_stack_to_LIR(*down_element, hash);

            return NULL;
        }
        else if (in_stack->element.state_element == Resident_HIR) {

            change_in_list((*down_element)->element, name, upper_in_list, penultimate_in_list);

            in_stack->element.state_element = LIR;

            (*down_element)->element.state_element = Resident_HIR;
            change_in_hash((*down_element)->element.name, NULL, hash, Stack);

            *down_element = clear_stack_to_LIR(*down_element, hash);

            return NULL;
        }
        else {

            struct element delete;

            delete = add_in_list(name);                         //Функция возвращет структуру удалённого элемента
            to_non_resident(delete.name, hash);
            
            in_stack->element.state_element = LIR;

            (*down_element)->element.state_element = Resident_HIR;
            change_in_hash((*down_element)->element.name, NULL, hash, Stack);

            *down_element = clear_stack_to_LIR(*down_element, hash);

            return delete.location_in_cache;
        }
        
    }


}

struct dlinked_list_element *new_upper_element(int name, enum state state_element, void *location_in_cache, struct dlinked_list_element *last_upper_element) {

    struct dlinked_list_element *new = (struct dlinked_list_element *) calloc(1, sizeof(struct dlinked_list_element));

    if (last_upper_element != NULL) {
        last_upper_element->previous = new;
    }

    new->previous = NULL;
    new->next = last_upper_element;

    new->element.name = name;
    new->element.state_element = state_element;
    new->element.location_in_cache = location_in_cache;

    return new;    
}

void move_up_stack(struct dlinked_list_element *upper_element, struct dlinked_list_element *lift_element) {

    assert(upper_element != NULL);
    assert(lift_element != NULL);

    (lift_element->previous)->next = lift_element->next;
    if (lift_element->next != NULL) {
        (lift_element->next)->previous = lift_element->previous;
    }

    upper_element->previous = lift_element;

    lift_element->previous = NULL;
    lift_element->next = upper_element;
}

char element_is_LIR(struct dlinked_list_element *down_element) {
    
    assert(down_element != NULL);
    
    if (down_element->element.state_element == LIR) {
        return 1;
    }
    return 0;
}


struct dlinked_list_element *clear_stack_to_LIR(struct dlinked_list_element *down_element, struct element_hash **hash) {
    
    assert(down_element != NULL);

    struct dlinked_list_element *current = down_element, *previous;

    while (element_is_LIR(current) != 1) {
        
        previous = current->previous;
        change_in_hash(current->element.name, NULL, hash, Stack);                                  //изменение значение элемента в хэше
        free_element_stack(current, hash);
        current = previous;
    }

    current->next = NULL;

    return current;
}

void free_stack(struct dlinked_list_element *upper_element, struct element_hash **hash){
    
    assert(upper_element != NULL);

    struct dlinked_list_element *current = upper_element;
    struct dlinked_list_element *next;

    while (current != NULL) {
        
        next = current->next;

        free_element_stack(current, hash);

        current = next;
    }
    
}

void free_element_stack(struct dlinked_list_element *element, struct element_hash **hash) {
    
    free(element->element.location_in_cache);
    free(element);
    delete_element_hash(element->element.name, hash);

}

void to_non_resident(int name, struct element_hash **hash) {
    
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