#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>

#include"generator.h"


void WriteTest(FILE * file, int m_max, int n_max, int p_max) {
	
	srand(rand());
	
	int n = rand() % n_max + 1;
	fprintf(file, "%d %d ", rand() % m_max + 1, n);
	
	for(int i = 0; i < n; i++) {
		fprintf(file, "%d ", rand() % (p_max + 1));
	}
	fprintf(file, "\n");
}


void Generator(FILE * file, int N, int m_max, int n_max, int p_max) {
	assert(file);
	
	fprintf(file, "Total number of tests in this file %d\n", N);
	srand(time(NULL));
	for(int i = 0; i < N; i++) {
		WriteTest(file, m_max, n_max, p_max);
	}
	
	
	
}
