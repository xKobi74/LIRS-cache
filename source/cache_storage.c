#include <stdio.h>

#include "../include/cache_storage.h"

struct cache_storage_t {
	int capacity;
	int used;
	int unitsize;
	char *data;
	fgetdata_t fgetdata;
};
