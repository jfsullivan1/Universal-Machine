#ifndef EXECUTE_INCLUDED
#define EXECUTE_INCLUDED
#include <stdbool.h>
#include <stdint.h>
#include "segment.h"

/** Takes a single array with all instructions to compute
 * 
 */
void load_program(segment mem);

#endif