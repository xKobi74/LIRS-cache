#ifndef __STACK_H__
#define __STACK_H__

void print_stack_up(struct dlinked_list_element *down_element);
void print_stack_down(struct dlinked_list_element *upper_element);
void *LIRS_algorithm(int name, int len_LIR, struct stack stack, struct list list, struct element_hash **hash, struct  cache_storage_t *cache);

#endif