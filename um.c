#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "execute.h"
#include "fileRead.h"
#include "bitpack.h"
#include "segment.h"
#include "assert.h"

/** Main
 * @param argc -> Expects to be 2 (./um + file)
 * @param argv -> File name
 */
int main(int argc, char * argv[]){ 
    if(argc != 2){ 
        fprintf(stderr, "Invalid input size\n");
    }else{
        //Load and execute program
        FILE* inputSize = fopen(argv[1], "r");
        int size = sizeGet(inputSize);
        //Load file again from new
        FILE* input = fopen(argv[1], "r");
        //New segmented memory 
        segment mem = Segment_new();
        //Execute the program
        assert(Segment_map(mem, size) == 0);
        //Segment_map(mem, size);
        read_input(input, size, mem);
        load_program(mem);
    }

    return 0;
}