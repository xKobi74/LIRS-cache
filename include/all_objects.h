#ifndef __ALL_OBJECTS_H__
#define __ALL_OBJECTS_H__

#include "cache_storage.h"

enum what_object{
    Stack,
    List
};

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

struct stack {
    struct dlinked_list_element **upper_element;
    struct dlinked_list_element **down_element;
};

struct list {
    struct dlinked_list_element **upper_element;
    struct dlinked_list_element **down_element;
};

struct element_hash {
    int name;
    struct dlinked_list_element *stack;
    struct dlinked_list_element *list;
    struct element_hash *next;
};

struct cache_storage_t {
	int capacity;
	int used;
	int unitsize;
	char *data;
	fgetdata_t fgetdata;
};

#endif