#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "execute.h"
#include "bitpack.h"
//#include "operator.h"
#include "segment.h"
#include "seq.h"


/*____________________________________________________________________________*
 *                           Implmented Functions                             *
 *____________________________________________________________________________*/

/** Runs the program
 * @param mem -> Segmanted memory
 */
void load_program(segment mem){ 
    //Pointer to the lsb of the word currently looking at
    int ptr = 0;
    uint32_t op, A, B, C, VALUE;
    //For input
    unsigned val;

    //Load a segment
    uint32_t buffer = ~0;
    uint32_t instr;
    uint32_t *temp;

    while(1){ 
        //Generates 1 instruction
        //instr = Segment_load(mem, 0, ptr);
        temp = Seq_get(mem->segments, 0);
        instr = temp[1 + ptr];
        //Set the new OP code
        op = instr >> 28;//OP
        A = (instr & ( (buffer << 29) >> 23 ) ) >> 6;
        B = (instr & ( (buffer << 29) >> 26 ) ) >> 3;
        C = instr & ( (buffer << 29) >> 29 );
        //Decide which operation to use
        switch(op){
            case 0:
                if(mem->r[C] != 0){
                    mem->r[A] = mem->r[B];
                }
                break;
            case 1:   
                //mem->r[A] = Segment_load(mem, mem->r[B], mem->r[C]);
                temp = Seq_get(mem->segments, mem->r[B]);
                mem->r[A] = temp[1 + mem->r[C]];
                break;
            case 2:
                Segment_store(mem, mem->r[A], mem->r[B], mem->r[C]);
                break;
            case 3:
                mem->r[A] = (mem->r[B] + mem->r[C]) % 4294967296;
                break;
            case 4:
                mem->r[A] = (mem->r[B] * (mem->r[C])) % 4294967296;
                break;
            case 5:
                mem->r[A] = mem->r[B] / mem->r[C];
                break;
            case 6:
                mem->r[A] = ~(mem->r[B] & mem->r[C]);
                break;
            case 7:
                Segment_free(&mem);
                exit(EXIT_SUCCESS);
                break;
            case 8:
                mem->r[B] = Segment_map(mem, mem->r[C]);
                break;
            case 9:
                Segment_unmap(mem, mem->r[C]);
                break;
            case 10:
                if(mem->r[C] < 256){
                    fprintf(stdout, "%c", (char)mem->r[C]);
                }
                break;
            case 11:
                val = getc(stdin);
                if (val == (unsigned) EOF) {
                        mem->r[C] = -1;
                }
                mem->r[C] = val;
                break;
            case 12: 
                if(mem->r[B] != 0){
                    Segment_loadprogram(mem, mem->r[B], 0);
                }
                ptr = (mem->r[C] - 1);
                break;
            case 13:
                VALUE = instr & ( (buffer << 7) >> 7 );//Value
                A = (instr & ( (buffer << 29) >> 4 ) ) >> 25;//A
                mem->r[A] = VALUE;
                break;
            default:
                fprintf(stderr, "ERROR: Not a valid instruction. \n");
                exit(EXIT_FAILURE);
        }

        //Iterating 32bits or (4*8)
        ptr+= 1;
    }
    Segment_free(&mem);
    return;
}