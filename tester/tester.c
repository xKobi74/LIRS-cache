/** 
 \file 
 \brief File with the implementation of functions from the header file.
*/

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#include"../include/tester.h"
#include"../include/lirs.h"




#define DATASIZE 2

int getN(FILE * file) {
	assert(file);
	
	int N = -1;
	
	for(int i = fscanf(file, "%d", &N); i == 0;) {
		i = fscanf(file, "%*s");
		i = fscanf(file, "%d", &N);
	}
	return N;
}

/** 
The required function that writes data of the requested file to cache by its number.
    \param[out] cacheunit The pointer on the location in bytes(char *) array where need to write data.
    \param[in] filenumber The unique number of the file which information will bw written.
*/
void fgetdata(void *cacheunit, int filenumber) {
    ((char *)cacheunit) [0] = filenumber % 10 + '0';
}

long long tester (FILE * file, int u) {

	assert(file);
	int m, n, i;
	long long count, ans;
	if(u == 1) {
		i = fscanf(file, "%lld", &ans);
		if(i != 1)
			abort();
	}
	m = getN(file);
	n = getN(file);
	
	int LEN_HIR = (m + 3)/ 4;
	int LEN_LIR = m - LEN_HIR;
	
	struct lirs_t *lirs = lirs_init(LEN_LIR, LEN_HIR, DATASIZE, fgetdata);
	
	for(i = 0; i < n; i++) {
		lirs_getfile(lirs, getN(file));
	}
	
	count = get_count_of_lirs_cache_hit(lirs);
	
	lirs_delete(lirs);
	
	if(u == 1 && count != ans) {
		printf("Wrong answer: %lld, correct answer: %lld\n", count, ans);
		return -1;
	}
	
	return count;
	
}
