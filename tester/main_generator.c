#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>

#include"../include/generator.h"


int main(int argc, char ** argv) {
	
	int N = 5;
	int m_max = 20;
	int n_max = 100;
	int p_max = 40;
	
	if(argc < 2) {
		perror("You must enter the file name");
		abort();
	}
	
	FILE * file = fopen(argv[1], "w");
	assert(file);
	
	if(argc > 5) {
		p_max = atoi(argv[5]);
		assert(p_max);
	} 
	if(argc > 4) {
		n_max = atoi(argv[4]);
		assert(n_max);
	}
	if(argc > 3) {
		m_max = atoi(argv[3]);
		assert(m_max);
	} 
	if(argc > 2) {
		N = atoi(argv[2]);
		assert(N);
	}
	
	generator(file, N, m_max, n_max, p_max);
	
	fclose(file);
	
	return 0;
}