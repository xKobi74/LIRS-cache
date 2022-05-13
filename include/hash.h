#ifndef __HASH_H__
#define __HASH_H__

struct element_hash **make_hash();
void free_hash(struct element_hash **hash);
void print_hash(struct element_hash **hash);
struct dlinked_list_element *find_element(int name, struct element_hash **hash, enum what_object object);
void change_in_hash(int name, struct dlinked_list_element *address, struct element_hash **hash, enum what_object object);

#endif