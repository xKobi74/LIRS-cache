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

int input_filenumber() {
    int x, k;
    k = scanf("%d", &x);
    if (k != 1)
        abort();
    return x;
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
	
	struct lirs_t *lirs = lirs_init(LEN_LIR, LEN_HIR, DATASIZE, fgetdata);
	
	for(int i = 0; i < n; i++) {
		lirs_getfile(lirs, input_filenumber());
	}
	
	printf("%llu\n", get_count_of_lirs_cache_hit(lirs));
	
	lirs_delete(lirs);
	
}