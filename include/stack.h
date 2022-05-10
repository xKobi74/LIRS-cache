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

void to_non_resident(int name, struct element_hash **hash);
char element_is_LIR(struct dlinked_list_element *down_element);
void print_stack_up(struct dlinked_list_element *down_element);
void print_stack_down(struct dlinked_list_element *upper_element);
void free_element_stack(struct dlinked_list_element *element);
struct dlinked_list_element *clear_stack_to_LIR(struct dlinked_list_element *down_element, struct element_hash **hash);
void move_up_stack(struct dlinked_list_element **upper_element, struct dlinked_list_element **down_element, struct dlinked_list_element *lift_element);

struct dlinked_list_element *new_upper_element(int name, enum state state_element, void *location_in_cache, 
                                               struct dlinked_list_element **upper_element, struct dlinked_list_element **down_element, 
                                               struct element_hash **hash);

void *LIRS_algorithm(int name, int len_LIR, struct dlinked_list_element **upper_element, struct dlinked_list_element **down_element, 
            struct element_hash **hash, struct  cache_storage_t *cache, 
            struct dlinked_list_element **upper_in_list, struct dlinked_list_element **down_in_list);

void first_filling(int name, int len_LIR, struct dlinked_list_element **upper_element, struct dlinked_list_element **down_element, 
                   struct element_hash **hash, struct  cache_storage_t *cache, 
                   struct dlinked_list_element **upper_in_list, struct dlinked_list_element **down_in_list);

void *first_entry(int name, struct dlinked_list_element **upper_element, struct dlinked_list_element **down_element, struct element_hash **hash, 
                  struct dlinked_list_element **upper_in_list, struct dlinked_list_element **down_in_list);

void only_in_list(int name, struct dlinked_list_element **upper_element, struct dlinked_list_element **down_element, struct element_hash **hash, 
                  struct dlinked_list_element **upper_in_list);

void resident_in_stack(int name, struct dlinked_list_element **down_element, struct element_hash **hash, 
                       struct dlinked_list_element **upper_in_list, struct dlinked_list_element *in_stack);

void *non_resident_in_stack(struct dlinked_list_element **down_element, struct element_hash **hash, 
                            struct dlinked_list_element **upper_in_list, struct dlinked_list_element **down_in_list, 
                            struct dlinked_list_element *in_stack);
#endif