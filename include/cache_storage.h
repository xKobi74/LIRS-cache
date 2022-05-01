#pragma once

struct cache_storage_t;

//function that writes data of file to cacheunit
typedef void (*fgetdata_t)(int filenumber, void *cacheunit);

//create and return pointer on struct cache_storage_t
struct cache_storage_t *cache_storage_init(int capacity, int unitsize, fgetdata_t);
//free memory of struct cache_storage_t by pointer  
void cache_storage_delete(struct cache_storage_t *);
//1 - full, 0 - there is empty space
char cache_storage_isfull(struct cache_storage_t *);
//return number of used cache units 
int cache_storage_used(struct cache_storage_t *);
//write data of file in cache_storage_t
void *cache_unit_write(struct cache_storage_t *, int filenumber);
//writes zeros in cache unit by pointer
void cache_unit_clear(struct cache_storage_t *, void *cacheunit);
//replace data in cache unit to data of newfilenumber
void cache_unit_change(struct cache_storage_t *, void *cacheunit, int newfilenumber);
