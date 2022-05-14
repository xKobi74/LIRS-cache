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
		fscanf(file, "%*s");
		i = fscanf(file, "%d", &N);
	}
	return N;
}

void fgetdata(void *cacheunit, int filenumber) {
    ((char *)cacheunit) [0] = filenumber % 10 + '0';
}

int tester (FILE * file) {

	assert(file);
	int m, n;
	
	fscanf(file, "%d%d", &m, &n);
	
	int LEN_HIR = (m + 3)/ 4;
	int LEN_LIR = m - LEN_HIR;
	int x;
	struct lirs_t *lirs = lirs_init(LEN_LIR, LEN_HIR, DATASIZE, fgetdata);
	
	for(int i = 0; i < n; i++) {
		fscanf(file, "%d", &x);
		/*printf("%s\n", (char *) */lirs_getfile(lirs, x);
	}
	
	lirs_delete(lirs);
	
}