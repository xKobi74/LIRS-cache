/** 
 \file 
 \brief Header file with description of functions for cache_storage.c.
*/


#ifndef __CACHE_STORAGE_H__
#define __CACHE_STORAGE_H__

/** 
The required signature of the function that writes data of the file to cache.
	\param[out] cacheunit The pointer on the location in bytes(char *) array where need to write data.
	\param[in] filenumber The name of the file which information need to write.
*/
typedef void (*fgetdata_t)(void *cacheunit, int filenumber);

struct cache_storage_t; ///< Declaration of the struct that need to be used in this functions. Its description is hidden.

/**
The function that create cache storage with required params.
    \param[in] capacity The total count of files wich can be storaged.
    \param[in] unitsize Maximum size in bytes of a file.
    \param[in] fgetdata The pointer on a function that writes data of the file to cache.
    \return A pointer on the new cache_storage_t object.
*/
struct cache_storage_t *cache_storage_init(int capacity, int unitsize, fgetdata_t fgetdata);

/**
The function that delete cache storage and free all memory that in used.
	\param[out] cachestorage The pointer on the cache_storage_t object that need to delete.
*/
void cache_storage_delete(struct cache_storage_t *cachestorage);

/**
The function that indicate if cache storage is full.
    \param[in] cachestorage The pointer on the cache_storage_t object that state you need to know.
    \return 1 if cache storage is full, else 0.
*/
char cache_storage_isfull(struct cache_storage_t *cachestorage);

/**
The function that indicate the total number of used cache units.
    \param[in] cachestorage The pointer on the cache_storage_t object that state you need to know.
    \return The total number of used cache units.
*/
int cache_storage_used(struct cache_storage_t *cachestorage);

/**
The function that writes the data of the file with current filenumber if the cache storage is not full.
    \param[out] cachestorage The pointer on the cache_storage_t object where you need to write the file.
    \param[in] filenumber The unique number of the file that you need to write.
    \return The pointer on the location in the cache storage where file's data will be written. Or NULL pointer if cache storage is full.
*/
void *cache_unit_add(struct cache_storage_t *cachestorage, int filenumber);

/**
The function that writes the data of the new file with current filenumber in replace to an old file in the cache unit.
    \param[out] cachestorage The pointer on the cache_storage_t object where you need to overwrite the file.
    \param[in] cacheunit The pointer on the cache unit that you need to overwrite.
    \param[in] newfilenumber The unique number of the file that you need to write in replace to an old.
*/
void cache_unit_change(struct cache_storage_t *cachestorage, void *cacheunit, int newfilenumber);

/**
The function that print the data of all written cache units. Data will be interpritated as ASCII string. 
    \param[in] cachestorage The pointer on the cache_storage_t object that you need to display.
*/
void cache_storage_data_print(struct cache_storage_t *cachestorage);

#endif