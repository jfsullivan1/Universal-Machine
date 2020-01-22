#ifndef SEGMENT_INCLUDED
#define SEGMENT_INCLUDED
#include <stdbool.h>
#include <stdint.h>
#include "seq.h"
//typedef struct segment *segment;

/*____________________________________________________________________________*
 *                           Local Structure                                  *
 *____________________________________________________________________________*/

/** Segment with Sequence of segments and unmapped ID's 
 * 
 */
struct segment{ 
    Seq_T segments;
    Seq_T unmapped;
    uint32_t *r;
};
typedef struct segment *segment;

//New
segment Segment_new();
//Free
void Segment_free(segment * seg);
//Store
void Segment_store(segment mem, int seg_num, int seg_offset, uint32_t value);
//Length
int Segment_length(segment mem, int seg_num);


//Load          OP#1
uint32_t Segment_load(segment mem, int seg_num, int seg_offset);
//Map           OP#8
uint32_t Segment_map(segment mem, unsigned amount);
//Unmap         OP#9
void Segment_unmap(segment mem, uint32_t seg_num);
//Load Program  OP#12
void Segment_loadprogram(segment mem, uint32_t seg_num_source, uint32_t seg_num_destination);

#endif