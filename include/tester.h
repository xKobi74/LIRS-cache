/** 
 \file 
 \brief Header file with description of functions for tester.c.
*/

/**
The function that allows you to read a number from a file and skips all the text before it.
    \param[in] file The FILE pointer to read.
	\return A read number.
*/
int getN(FILE * file);

/**
The function that runs tests from a file.
    \param[in] file The FILE pointer to read.
	\return A number of cache hits.
*/
unsigned long long tester (FILE * file);
