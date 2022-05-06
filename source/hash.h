const int len_hash = 5;

struct element_hash {
    int name;
    struct stack_element *stack;
    struct list_element *list;
    struct element_hash *next;
};

struct element_hash **make_hash();
char delete_element_hash(int name, struct element_hash **hash);
struct element_hash *new_element(int name, struct stack_element *address);
struct list_element *element_in_list(int name, struct element_hash **hash);
struct stack_element *element_in_stack(int name, struct element_hash **hash);
void change_list(int name, struct list_element *address, struct element_hash **hash);
void change_stack(int name, struct stack_element *address, struct element_hash **hash);