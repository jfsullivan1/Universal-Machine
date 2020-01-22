#ifndef FILEREAD_INCLUDED
#define FILEREAD_INCLUDED
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "segment.h"

/**  Read file and store instructions in mem
 * 
 */
void read_input(FILE * input, int size, segment mem);

/** Return file size 
 * 
 */
int sizeGet(FILE * input);

#endif