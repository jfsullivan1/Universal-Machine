#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "operator.h"
#include <stdio.h>
#include "segment.h"
#include "seq.h"

/*____________________________________________________________________________*
 *                           Implmented Functions                             *
 *____________________________________________________________________________*/

/** Conditional move 
 * @param r -> registers
 * @param A -> A value 
 * @param B -> B value 
 * @param C -> C value
 */
void conditional_move(unsigned *r, int A, int B, int C){ 
    if(r[C] != 0){
        r[A] = r[B];
    }
    return;
}

/** Segment load
 * @param r -> registers
 * @param mem -> segmented memory
 * @param A -> A value 
 * @param B -> B value 
 * @param C -> C value
 */
void segment_load(unsigned *r, segment mem, int A, int B, int C){ 
    r[A] = Segment_load(mem, r[B], r[C]);
    return;
}

/** Segment store
 * @param r -> registers
 * @param mem -> segmented memory
 * @param A -> A value 
 * @param B -> B value 
 * @param C -> C value
 */
void segment_store(unsigned *r, segment mem, int A, int B, int C){ 
    Segment_store(mem, r[A], r[B], r[C]);
    return;
}

/** Addition
 * @param r -> registers
 * @param A -> A value 
 * @param B -> B value 
 * @param C -> C value
 */
void addition(unsigned *r, int A, int B, int C){ 
    r[A] = (r[B] + r[C]) % 4294967296;
    return;
}

/** Multiplication
 * @param r -> registers
 * @param A -> A value 
 * @param B -> B value 
 * @param C -> C value
 */
void multiplication(unsigned *r,  int A, int B, int C){ 
    r[A] = (r[B] * (r[C])) % 4294967296;
    return;
}

/** Division
 * @param r -> registers
 * @param A -> A value 
 * @param B -> B value 
 * @param C -> C value
 */
void division(unsigned *r,  int A, int B, int C){ 
    r[A] = r[B] / r[C];
    return;
}

/** NAND
 * @param r -> registers
 * @param A -> A value 
 * @param B -> B value 
 * @param C -> C value
 */
void bitwise_NAND(unsigned *r,  int A, int B, int C){ 
    r[A] = ~(r[B] & r[C]);
    return;
}

/** Halt
 * 
 */
void halt(){ 
    exit(EXIT_SUCCESS);
}

/** Map Segment
 * @param r -> registers
 * @param mem -> segmented memory
 * @param B -> B value 
 * @param C -> C value
 */
void map_segment(unsigned *r, segment mem, int B, int C){ 
     r[B] = Segment_map(mem, r[C]);
     return;
}

/** Unmap segment
 * @param r -> registers
 * @param mem -> segmented memory
 * @param C -> C value
 */
void unmap_segment(unsigned *r, segment mem, int C){ 
    Segment_unmap(mem, r[C]);
    return;
}

/** Output
 * @param r -> registers
 * @param C -> C value
 */
void output(unsigned *r, int C){ 
    if(r[C] < 256){
        fprintf(stdout, "%c", (char)r[C]);
    }
    return;
}

/** Input
 * @param r -> registers
 * @param C -> C value
 */
void input(unsigned *r, int C){ 
    unsigned val = getc(stdin);
    if (val == (unsigned) EOF) {
            r[C] = -1;
    }
    r[C] = val;
    return;
}

/** Load Value
 * @param r -> registers
 * @param A -> A value 
 * @param value -> value to store
 */
void load_value(unsigned *r, int A, uint32_t value){ 
    r[A] = value;
    return;
}

/** Load program
 * @param r -> registers
 * @param mem -> segmented memory
 * @param B -> B value 
 * @param C -> C value
 */
void op_load_program(unsigned *r, segment mem, int B, int C){
    if(r[B] != 0){
        Segment_loadprogram(mem, r[B], 0);
    }
    (void)C;
}