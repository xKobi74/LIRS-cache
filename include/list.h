/** 
    \file 
    \brief Header file with description of functions for list.c.
*/

#ifndef __LIST_H__
#define __LIST_H__

/**
Created a new element in list. It is added to the top.
    \param[in] name The created element will have this name.
    \param[in] location_in_cash The created element will be stored at this address in the cache.
    \param[in, out] list The element will be added to this list.
    \param[out] hash For add information about a new element to the hash.
*/
void new_in_list(int name, void *location_in_cash, struct list list, struct hash *hash);

/**
Created a new element at the top of the list and deleted at the bottom. The new element will be stored in location_in_chach of deleted elem.   
    \param[in] name The created element will have this name.
    \param[in, out] list The actions will be happened in this list.
    \param[out] hash For change information about new and old elements in the hash.
    \return A copy of the deleted structure
*/
struct element add_in_list(int name, struct list list, struct hash *hash); //return struct deleted element.

/**
Moved the specified element to the top, return a copy of its structure.
    \param[in] name The moved element has this name.
    \param[in, out] list The actions will be happened in this list.
    \param[in, out] hash For change information about the element in the hash and find information about moved element.
    \return The move element(struct element).
*/
struct element move_up_list(int name, struct list list, struct hash *hash);

/**
Created a new element at the top of the list and deleted specified one. The new element will be stored in location_in_chach of deleted elem.
    \param[in] add The structure of the added element.
    \param[in] name_delete The deleted element has this name.
    \param[in, out] list The actions will be happened in this list.
    \param[in,out] hash For change information about the element in the hash and find information about deleted element.
*/
void change_in_list(struct element add, int name_delete, struct list list, struct hash *hash);
#endif
