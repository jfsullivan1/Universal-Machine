#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include <math.h>
#include <mem.h>
#include "bitpack.h"
#include "segment.h"
#include "assert.h"

/** Gets the amount of char in a file
 * @param input -> File with 32 bit instructions
 */
int sizeGet(FILE * input){ 
    FILE *sizeF = input;
    int size = 0;
    while(fgetc(sizeF) != EOF){ 
        size++;
    }
    return size;
}

/** Takes words and puts uint64_t reprsentation  TRIAL
 * @param input -> File with 32 bit instructions
 * @param size -> Size of file
 * @param mem -> Segmented memory
 */
void read_input(FILE * input, int size, segment mem){ 

    unsigned char c;
    int64_t part = 0;
    uint32_t word = 0;
    for(uint32_t i = 0; i < (uint32_t)(size/4); i++){ 
        uint64_t buffer = ~0;
        //LSB is 24
        c = getc(input);
        part = (int64_t)c;
        buffer = buffer << 56;
        buffer = buffer >> 32;
        part = part << 24;
        part = (part & buffer);
        word = (word & ~buffer);
        word = (word | part);
        //LSB is 16
        c = getc(input);
        buffer = ~0;
        part = (int64_t)c;
        buffer = buffer << 56;
        buffer = buffer >> 40;
        part = part << 16;
        part = (part & buffer);
        word = (word & ~buffer);
        word = (word | part);
        //LSB is 8 
        c = getc(input);
        buffer = ~0;
        part = (int64_t)c;
        buffer = buffer << 56;
        buffer = buffer >> 48;
        part = part << 8;
        part = (part & buffer);
        word = (word & ~buffer);
        word = (word | part);
        //LSB is 0
        c = getc(input);
        buffer = ~0;
        part = (int64_t)c;
        buffer = buffer << 56;
        buffer = buffer >> 56;
        part = (part & buffer);
        word = (word & ~buffer);
        word = (word | part);

        Segment_store(mem, 0, i, word);
        
    }
}