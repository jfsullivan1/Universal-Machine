#ifndef FILEREAD_INCLUDED
#define FILEREAD_INCLUDED
#include <stdbool.h>
#include <stdint.h>
#include "segment.h"

//OP 0                register       A      B     C
void conditional_move(unsigned *r, int A, int B, int C);

//OP 1              register     memory        A      B     C
void segment_load(unsigned *r, segment mem, int A, int B, int C);

//OP 2                register    memory        A      B     C
void segment_store(unsigned *r, segment mem, int A, int B, int C);

//OP 3        register       A      B     C
void addition(unsigned *r, int A, int B, int C);

//OP 4                register       A      B     C
void multiplication(unsigned *r,  int A, int B, int C);

//OP 5          register       A      B     C
void division(unsigned *r,  int A, int B, int C);

//OP 6             register       A      B     C
void bitwise_NAND(unsigned *r,  int A, int B, int C);

//OP 7
void halt();

//OP 8            register     memory         B     C
void map_segment(unsigned *r, segment mem, int B, int C);

//OP 9                register       memory    C
void unmap_segment(unsigned *r, segment mem, int C);

//OP 10       register     C
void output(unsigned *r, int C);

//OP 11       register    C
void input(unsigned *r, int C);

//OP 12          register       A      Value
void load_value(unsigned *r, int A, uint32_t value);

//OP 13               register      memory      B     C
void op_load_program(unsigned *r, segment mem, int B, int C);

#endif