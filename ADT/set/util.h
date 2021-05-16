/*
util.h - utility header file
*/

#ifndef UTIL_H
#define UTIL_H

#include <stddef.h>

/*
	creates a new block of memory with error checking
	returned value should be freed by the calling function
*/
void *safe_malloc(size_t size);

/*
	resize a preexisting block of memory with error checking
	returned value should be freed by the calling function
*/	
void *safe_realloc(void *old_mem, size_t new_size);

/* you may define other utility functions for your code if you wish */

#endif	/* include guard */