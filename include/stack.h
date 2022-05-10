#ifndef __STACK_H__
#define __STACK_H__

enum state {
    LIR,
    Resident_HIR,
    Non_resident_HIR
};

struct element {
    int name;
    enum state state_element;
    void *location_in_cache;
};

struct dlinked_list_element {
    struct element element;
    struct dlinked_list_element *next;
    struct dlinked_list_element *previous;
};

struct cache_storage_t {
	int capacity;
	int used;
	int unitsize;
	char *data;
};

struct stack {
    struct dlinked_list_element **upper_element;
    struct dlinked_list_element **down_element;
};

struct list {
    struct dlinked_list_element **upper_element;
    struct dlinked_list_element **down_element;
};

void to_non_resident(int name, struct element_hash **hash);
void free_element_stack(struct dlinked_list_element *element);
char element_is_LIR(struct dlinked_list_element *down_element);
void print_stack_up(struct dlinked_list_element *down_element);
void print_stack_down(struct dlinked_list_element *upper_element);
void move_up_stack(struct stack stack, struct dlinked_list_element *lift_element);
void only_in_list(int name, struct stack stack, struct list list, struct element_hash **hash);
void *first_entry_in_full(int name, struct stack stack, struct list list, struct element_hash **hash);
struct dlinked_list_element *clear_stack_to_LIR(struct dlinked_list_element *down_element, struct element_hash **hash);
void *non_resident_in_stack(struct stack stack, struct list list, struct element_hash **hash, struct dlinked_list_element *in_stack);
void *in_stack(int name, struct stack stack, struct list list, struct element_hash **hash, struct dlinked_list_element *element_in_stack);
void resident_in_stack(int name, struct stack stack, struct list list, struct element_hash **hash, struct dlinked_list_element *in_stack);
void *first_entery(int name, int len_LIR, struct stack stack, struct list list, struct element_hash **hash, struct  cache_storage_t *cache);
void first_filling(int name, int len_LIR, struct stack stack, struct list list, struct element_hash **hash, struct  cache_storage_t *cache);
void *not_in_stack(int name, int len_LIR, struct stack stack, struct list list, struct element_hash **hash, struct  cache_storage_t *cache);
void *LIRS_algorithm(int name, int len_LIR, struct stack stack, struct list list, struct element_hash **hash, struct  cache_storage_t *cache);
struct dlinked_list_element *new_upper_element(int name, enum state state_element, void *location_in_cache, 
                                               struct stack stack, struct element_hash **hash);

#endif