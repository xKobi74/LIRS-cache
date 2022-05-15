/** 
 \file 
 \brief Header file with description of functions for stack.c.
*/

#ifndef __STACK_H__
#define __STACK_H__

/**
Prints to the console the names of the elements in the object from the bottom of the doubly linked list.
    \param[in] down_element Pointer to the down element of a doubly linked list.
*/
void print_up(struct dlinked_list_element *down_element);

/**
Prints to the console the names of the elements in the object from the top of the doubly linked list.
    \param[in] upper_element Pointer to the upper element of a doubly linked list.
*/
void print_down(struct dlinked_list_element *upper_element);

/**
Implements the entire algorithm for writing elements to various program objects and clearing objects if necessary.
    \param[in]      name    The name of the input file.
    \param[in]      len_LIR Length of the LIR memory area.
    \param[in, out] stack   The stack structure in which changes will occur.
    \param[in, out] list    The list structure in which changes will occur.
    \param[in, out] hash    The hash table in which changes will occur.
    \param[in, out] cache   The cache array where all files are stored.
    \return Void * pointer to the location in the cache where the incoming file should be written. NULL if the file has already been written.
*/
void *LIRS_algorithm(int name, int len_LIR, struct stack stack, struct list list, struct hash *hash, struct  cache_storage_t *cache);

#endif