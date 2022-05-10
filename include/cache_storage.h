#pragma once

struct cache_storage_t;

//function that writes data of file to cacheunit
typedef void (*fgetdata_t)(void *cacheunit, int filenumber);

//create and return pointer on struct cache_storage_t
struct cache_storage_t *cache_storage_init(int capacity, int unitsize, fgetdata_t);

//free memory of struct cache_storage_t by pointer  
void cache_storage_delete(struct cache_storage_t *);

//1 - full, 0 - there is empty space
char cache_storage_isfull(struct cache_storage_t *);

//return number of used cache units 
int cache_storage_used(struct cache_storage_t *);

//return pointer of cacheunit by its index (or NULL if number is uncorrect)
void *cache_unit_pointer(struct cache_storage_t *, int cacheunitindex);

//add data of file in cache_storage_t and return pointer on it (or NULL if cache storage is full)
void *cache_unit_add(struct cache_storage_t *, int filenumber);

//writes zeros in cache unit by pointer
void cache_unit_clear(struct cache_storage_t *, void *cacheunit);

//replace data in cache unit to data of newfilenumber
void cache_unit_change(struct cache_storage_t *, void *cacheunit, int newfilenumber);

//print cache_storage data
void cache_storage_data_print(struct cache_storage_t *cachestorage);
