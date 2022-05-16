/**
    \file
    \brief A header file with a description of enumerations and structures that are needed in different files.
*/

#ifndef __ALL_OBJECTS_H__
#define __ALL_OBJECTS_H__

#include "cache_storage.h"

/// A set of possible object states showing which object will be worked with in functions that are universal for working with stack and list.
enum what_object{
    Stack, ///< Specifies that the element will be identified as a stack element.
    List ///< Specifies that the element will be identified as a list element.
};

/// A set of possible states of an object tracked by LIRS-algorithm. It will be worked with according to his condition.
enum state {
    LIR, ///< The element is marked as LIR. 
    Resident_HIR, ///< The element is marked as Resident_HIR.
    Non_resident_HIR///< The element is marked as Non_resident_HIR.
};

///Description of struct dlinked_list_element's element.
struct element {
    int name; ///< Stores the name of the element
    enum state state_element; ///< Stores the state of the element.
    void *location_in_cache;///< Stores the location in cache of the element.
};

///Description of struct element of doubly linked list.
struct dlinked_list_element {
    struct element element; ///< Stores the information of the element.
    struct dlinked_list_element *next; ///< Points to the next element of a doubly linked list.
    struct dlinked_list_element *previous; ///< Points to the previous element of a doubly linked list.
};

/// A structure that stores the upper and down elements of the stack.
/// \warning According to the description of the algorithm on the basis of which the implementation was based, the object is called a stack. But from the point of view of tasks and implementation, this name is not strict.
struct stack {
    struct dlinked_list_element **upper_element; ///< Points to the upper element of the stack.
    struct dlinked_list_element **down_element; ///< Points to the down element of the stack.
};

/// A structure that stores the upper and down elements of the list.
struct list {
    struct dlinked_list_element **upper_element; ///< Points to the upper element of the list.
    struct dlinked_list_element **down_element; ///< Points to the down element of the list.
};

/// The structure of the element stored in the hash table.
struct element_hash {
    int name; ///< Stores the name of the element.
    struct dlinked_list_element *stack; ///< Points to the element in the stack. If it is NULL, it's not in stack.
    struct dlinked_list_element *list; ///< Points to the element in the list . If it is NULL, it's not in list.
    struct element_hash *next; ///< Points to the next element in collision.
};

/// List structure in a hash table.
struct hash_list {
    struct element_hash *top; ///< Points to the top element in the hash table list.
    float size; ///< The current size of the hash table list.
};

/// The hash table structure containing the array parameters and the hash table list structure.
struct hash {
    struct element_hash **array; ///< Array hash table.
    int capacity; ///< Hash table array capacity.
    float size; ///< The current number of elements in the hash table array.
    struct hash_list list; ///< Hash table list structure.
};

#endif
