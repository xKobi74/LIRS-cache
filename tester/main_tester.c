#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#include"../include/tester.h"


int main(int argc, char ** argv) {
	if(argc < 3) {
		perror("You must enter mode and the file name");
		abort();
	}
	
	long long hits = 0;
	
	int u = atoi(argv[1]);
	
	FILE * file = fopen(argv[2], "r");
	assert(file);
	
	int N = getN(file);
	assert(N > 0);
	
	
	for(int i = 0; i < N; i++) {
		printf("Test #%d: ", i + 1);
		hits = tester(file, u);
		if (hits >= 0)
			printf("%lld hits\n", hits);
	}
	
	fclose(file);
	
	return 0;
}