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

void to_non_resident(int name, struct element_hash **hash);
char element_is_LIR(struct dlinked_list_element *down_element);
void print_stack_up(struct dlinked_list_element *down_element);
void print_stack_down(struct dlinked_list_element *upper_element);
void free_stack(struct dlinked_list_element *upper_element, struct element_hash **hash);
void free_element_stack(struct dlinked_list_element *element, struct element_hash **hash);
void move_up_stack(struct dlinked_list_element *upper_element, struct dlinked_list_element *lift_element);
struct dlinked_list_element *clear_stack_to_LIR(struct dlinked_list_element *down_element, struct element_hash **hash);
struct dlinked_list_element *new_upper_element(int name, enum state state_element, void *location_in_cache, 
                                               struct dlinked_list_element *last_upper_element);
void *stack(int name, int len_LIR, struct dlinked_list_element **upper_element, struct dlinked_list_element **down_element, 
            struct element_hash **hash, struct  cache_storage_t *cache, 
            struct list_element **upper_in_list, struct list_element **penultimate_in_list);