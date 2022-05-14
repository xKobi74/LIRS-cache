/** 
 \file 
 \brief Header file with description of functions for hash.c.
*/

#ifndef __HASH_H__
#define __HASH_H__

/**
Creates an array for the hash table.
    \return Pointer to created array.
*/
struct element_hash **make_hash();

/**
Releases a hash table with all collisions and pointers to store elements in other objects.
    \param[in] hash The hash array in which changes will occur.
*/
void free_hash(struct element_hash **hash);

/**
Prints to the console the elements in the hash table and their pointers to other objects.
    \param[in] hash The hash array to be printed.
*/
void print_hash(struct element_hash **hash);

/**
Searches for a pointer to an element in the specified object.
    \param[in] name    The name of the input file.
    \param[in] hash    Hash array in which to search.
    \param[in] object  The object whose address will be written.
    \return A pointer to an element in the specified object. Or NULL if there is no pointer.
*/
struct dlinked_list_element *find_element(int name, struct element_hash **hash, enum what_object object);

/**
Creates a new element in the hash table if there isn't one already. Or changes information about an existing one.
    \param[in] name    The name of the input file.
    \param[in] address The address where the file is stored in the specified object.
    \param[in] hash    Hash array in which to search.
    \param[in] object  The object whose address will be written.
*/
void change_in_hash(int name, struct dlinked_list_element *address, struct element_hash **hash, enum what_object object);

#endif