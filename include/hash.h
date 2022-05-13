#ifndef __HASH_H__
#define __HASH_H__

enum what_object{
    Stack,
    List
};

struct dlinked_list_element;

struct element_hash {
    int name;
    struct dlinked_list_element *stack;
    struct dlinked_list_element *list;
    struct element_hash *next;
};

struct element_hash **make_hash();
void free_hash(struct element_hash **hash);
void print_hash(struct element_hash **hash);
char delete_element_hash(int name, struct element_hash **hash);
struct element_hash *new_element(int name, struct dlinked_list_element *address, enum what_object object);
struct dlinked_list_element *find_element(int name, struct element_hash **hash, enum what_object object);
void change_in_hash(int name, struct dlinked_list_element *address, struct element_hash **hash, enum what_object object);

#endif