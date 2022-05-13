#ifndef __LIRS_H__
#define __LIRS_H__

struct lirs_t;

//function that writes data of file to cacheunit
typedef void (*fgetdata_t)(void *cacheunit, int filenumber);

//create and return pointer on struct lirs_t
struct lirs_t *lirs_init(int lircapacity, int hircapacity, int datasize, fgetdata_t fgetdata);

//free memory of struct lirs_t by pointer  
void lirs_delete(struct lirs_t *lirs);

//get pointer on data of file  
void *lirs_getfile(struct lirs_t *lirs, int filenumber);

//get pointer on data of file (and print log information)
void *lirs_getfilewithlog(struct lirs_t *lirs, int filenumber);

#endif