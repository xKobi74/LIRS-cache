#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/cache_storage.h"

struct cache_storage_t {
	int capacity;
	int used;
	int unitsize;
	char *data;
	fgetdata_t fgetdata;
};

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

void *cache_unit_pointer(struct cache_storage_t *cachestorage, int cacheunitindex) {
	char *cacheunitptr;
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

void cache_unit_clear(struct cache_storage_t *cachestorage, void *cacheunit) {
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
		printf("%s ", cache_unit_pointer(cachestorage, i));
	printf("\n");
}