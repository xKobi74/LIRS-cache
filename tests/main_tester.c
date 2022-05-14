#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#include"../include/tester.h"


int main(int argc, char ** argv) {
	if(argc < 2) {
		perror("You must enter the file name");
		abort();
	}
	
	FILE * file = fopen(argv[1], "r");
	assert(file);
	
	int N = getN(file);
	assert(N > 0);
	
	
	for(int i = 0; i < N; i++) {
		printf("Test #%d: ", i + 1);
		printf("%llu hits\n", tester(file));
	}
	
	return 0;
}