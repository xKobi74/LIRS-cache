/** 
 \file 
 \brief File with the implementation of functions from the header file, static functions for the cache_storage_t object and cache_storage_t struct.
*/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "cache_storage.h"

/// The description of the cache_storage_t struct.
struct cache_storage_t {
	int capacity; ///< Total count of cache units.
	int used; ///< Current count of used cache units.
	int unitsize; ///< Size in bytes (chars) of single cache unit.
	char *data; ///< The pointer on the start of cache units array.
	fgetdata_t fgetdata; ///< The pointer on the function that writes file's data by its number.
};

/**
The function that gives the pointer on the cache unit with current index.
    \param[in] cachestorage The pointer on the cache_storage_t object where you find cache unit.
    \param[in] cacheunitindex The index of the cache unit that you find.
    \return The pointer on the cache unit with current index.
*/
static void *cache_unit_pointer(struct cache_storage_t *cachestorage, int cacheunitindex);

/**
The function that delete the data of the cache unit by its pointer and writes zeros to it.
    \param[in] cachestorage The pointer on the cache_storage_t object where you need to clear cache unit.
    \param[out] cacheunit The pointer on the cache unit that you need to clear.
*/
static void cache_unit_clear(struct cache_storage_t *cachestorage, void *cacheunit);


struct cache_storage_t *cache_storage_init(int capacity, int unitsize, fgetdata_t fgetdata) {
	struct cache_storage_t *cachestorage = malloc(sizeof(struct cache_storage_t));
	if (cachestorage == NULL)
		abort();
	cachestorage->capacity = capacity;
	cachestorage->used = 0;
	cachestorage->unitsize = unitsize;
	cachestorage->data = calloc(capacity, unitsize);
	if (cachestorage->data == NULL)
		abort();
	cachestorage->fgetdata = fgetdata;
	return cachestorage;
}

void cache_storage_delete(struct cache_storage_t *cachestorage) {
	free(cachestorage->data);
	free(cachestorage);
}

char cache_storage_isfull(struct cache_storage_t *cachestorage) {
	return cachestorage->used == cachestorage->capacity;
}


int cache_storage_used(struct cache_storage_t *cachestorage) {
	return cachestorage->used;
}

static void *cache_unit_pointer(struct cache_storage_t *cachestorage, int cacheunitindex) {
	if (cacheunitindex < 0 || cacheunitindex >= cachestorage->capacity) 
		return NULL;
	return cachestorage->data + cachestorage->unitsize * cacheunitindex;
}

void *cache_unit_add(struct cache_storage_t *cachestorage, int filenumber) {
	char *cacheunit = cache_unit_pointer(cachestorage, cachestorage->used);
	if (cacheunit == NULL)
		return NULL;
	(cachestorage->fgetdata)(cacheunit, filenumber);
	++(cachestorage->used);
	return cacheunit;
}

static void cache_unit_clear(struct cache_storage_t *cachestorage, void *cacheunit) {
	if (cacheunit == NULL)
		return;
	memset((char *) cacheunit, '\0', cachestorage->unitsize);
}

void cache_unit_change(struct cache_storage_t *cachestorage, void *cacheunit, int newfilenumber) {
	if (cacheunit == NULL)
		return;
	cache_unit_clear(cachestorage, cacheunit);
	(cachestorage->fgetdata)(cacheunit, newfilenumber);
}

void cache_storage_data_print(struct cache_storage_t *cachestorage) {
	int i;
	for (i = 0; i < cachestorage->used; ++i)
		printf("%s ", (char *) cache_unit_pointer(cachestorage, i));
	printf("\n");
}