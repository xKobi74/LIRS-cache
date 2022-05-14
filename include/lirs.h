/** 
 \file 
 \brief Header file with description of functions for lirs.c.
*/

#ifndef __LIRS_H__
#define __LIRS_H__

/** 
The required signature of the function that writes data of the file to cache.
    \param[out] cacheunit The pointer on the location in bytes(char *) array where need to write data.
    \param[in] filenumber The name of the file which information need to write.
*/
typedef void (*fgetdata_t)(void *cacheunit, int filenumber);

struct lirs_t; ///< Declaration of the struct that need to be used in this functions. Its description is hidden.

/**
The function that create LIRS cache with required params.
    \param[in] lircapacity The size of LIR part of cache
    \param[in] hircapacity The size of HIR part of cache
    \param[in] datasize Maximum size in bytes of a single file.
    \param[in] fgetdata The pointer on a function that writes data of the file to cache.
    \return A pointer on the new lirs_t object.
*/
struct lirs_t *lirs_init(int lircapacity, int hircapacity, int datasize, fgetdata_t fgetdata);

/**
The function that delete LIRS cache and free all memory that in used.
	\param[out] lirs The pointer on the lirs_t object that need to delete.
*/
void lirs_delete(struct lirs_t *lirs);

/**
The function that gives a pointer on the file location in memory.
    \param[in] lirs The size of LIR part of cache
    \param[in] filenumber The name of the file which information is requested.
    \return A pointer on the file location in memory.
*/
void *lirs_getfile(struct lirs_t *lirs, int filenumber);

/**
The function that gives a pointer on the file location in memory and print log information.
    \param[in] lirs The size of LIR part of cache
    \param[in] filenumber The name of the file which information is requested.
    \return A pointer on the file location in memory.
*/
void *lirs_getfilewithlog(struct lirs_t *lirs, int filenumber);

/**
The function that gives a rate of cache missings.
    \param[in] lirs The size of LIR part of cache
    \return A rate of cache missings.
*/
float get_rate_of_lirs_cache_missing(struct lirs_t *lirs);

/**
The function that gives a count of cache hits.
    \param[in] lirs The size of LIR part of cache
    \return A count of cache hits.
*/
unsigned long long get_count_of_lirs_cache_hit(struct lirs_t *lirs);

#endif