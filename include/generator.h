/** 
 \file 
 \brief Header file with description of functions for generator.c.
*/

/**
The function that randomly generates and writes tests to a file.
    \param[in] file The FILE pointer to write.
	\param[in] N Number of tests to write to the file
    \param[in] m_max Maximum possible cache size.
    \param[in] n_max Maximum possible number of requests.
    \param[in] p_max Maximum possible page number.
*/
void generator(FILE * file, int N, int m_max, int n_max, int p_max);

/**
The function that randomly generates and writes one test to a file.
    \param[in] file The FILE pointer to write.
    \param[in] m_max Maximum possible cache size.
    \param[in] n_max Maximum possible number of requests.
    \param[in] p_max Maximum possible page number.
*/
void writetest(FILE * file, int m_max, int n_max, int p_max);

