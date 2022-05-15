#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>

#include"../include/generator.h"


void writetest(FILE * file, int m_max, int n_max, int p_max) {
	
	srand(rand());
	
	int n = rand() % n_max + 1;
	fprintf(file, "%d %d ", rand() % m_max + 2, n);
	
	for(int i = 0; i < n; i++) {
		fprintf(file, "%d ", rand() % (2 * p_max) - p_max);
	}
	fprintf(file, "\n");
}


void generator(FILE * file, int N, int m_max, int n_max, int p_max) {
	assert(file);
	
	fprintf(file, "Total number of tests in this file %d\n", N);
	srand(time(NULL));
	for(int i = 0; i < N; i++) {
		writetest(file, m_max, n_max, p_max);
	}
	
	
	
}
