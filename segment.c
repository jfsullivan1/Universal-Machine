#include "segment.h"
#include "seq.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "assert.h"
#include <string.h>

/*____________________________________________________________________________*
 *                           Implmented Functions                             *
 *____________________________________________________________________________*/

/** Create a new segment 
 * 
 */
segment Segment_new(){ 
    //Create the segment
    segment mem = malloc(sizeof(struct segment));
    //assert(mem != NULL);

    //Create the Seq_T
    Seq_T segments = Seq_new(100);

    //Create all unmapped segments
    Seq_T unmapped = Seq_new(100);
    for(uint32_t i = 0; i < 100; i++){ 
        Seq_addhi(unmapped, (void*)(uintptr_t)i);
    }

    //Set equal to mem struct
    mem->segments = segments;
    mem->unmapped = unmapped;

    //Registers
    uint32_t *r;
    r = calloc(8, sizeof(uint32_t));
    mem->r = r;
    return mem;
}

/** Free a segment 
 * @param mem -> Segmented memory
 */
void Segment_free(segment *mem){
    //assert(*mem);
    int SeqLen = Seq_length((*mem)->segments);
    //Loop through each segment and free it
    for(int i = 0; i < SeqLen; i++){
        free(Seq_get((*mem)->segments, i));
    }
    
    //Free both pointers
    Seq_free(&((*mem)->segments));
    Seq_free(&((*mem)->unmapped));

    //Free the struct
    free(*mem);

}

/** Store a segment 
 * @param mem -> Segmented memory
 * @param seg_num -> The ID of the segment
 * @param seg_offset -> The offset of the segment 
 * @param value -> The word to be store
 */
inline void Segment_store(segment mem, int seg_num, int seg_offset, uint32_t value){ 

    //Get the word where to store
    uint32_t *word = Seq_get(mem->segments, seg_num);

    //Set equal to the value
    word[1 + seg_offset] = value;
}

/** Load a segment 
 * @param mem -> segmented memory 
 * @param seg_num -> ID of the segment
 * @param seg_offset -> Offset of the segment 
 */
inline uint32_t Segment_load(segment mem, int seg_num, int seg_offset){ 

    //Retrive the word
    uint32_t * word = Seq_get(mem->segments, seg_num);

    //Return the desired value
    return word[1 + seg_offset];
}

/** Map segments 
 * @param mem -> segmented memory 
 * @param s -> size of the new segment
 */
uint32_t Segment_map(segment mem, unsigned s){

    //Initialize memory for the segment of s size
    uint32_t *newSeg = malloc(sizeof(uint32_t) * (s + 1));
    for (uint32_t i = 0; i < (s+1); i++){
        newSeg[i] = 0;
    }
    //assert(newSeg != NULL);
    newSeg[0] = s;

    //Create ID's and map 
    uint32_t ID;
    Seq_T segments = mem->segments;
    Seq_T unmapped = mem->unmapped;
    uint32_t unmappedLen = Seq_length(unmapped);
    uint32_t segLen = Seq_length(segments);
    if(unmappedLen == 0){
        for(uint32_t i = segLen; i < segLen + 100; i++){
            Seq_addhi(unmapped, (void*)(uintptr_t) i);
        }
    }
    
    //Get the lowest ID (starting a 1)
    ID = (uint32_t)(uintptr_t)Seq_remlo(unmapped);
    //If the ID is larger then mem->segments then add more to segments, else just put
    if(ID >= segLen)
        Seq_addhi(segments, newSeg);
    else
        Seq_put(segments, ID, newSeg);
    return ID;
}

/** Unmap segment 
 * @param mem -> segmented memory 
 * @param seg_num -> ID of the desired segment 
 */
void Segment_unmap(segment mem, uint32_t seg_num){ 
    //Add location to the unmapped
    Seq_addlo(mem->unmapped, (void*)(uintptr_t)seg_num);
    //Get current word in that position
    uint32_t *word = Seq_get(mem->segments, seg_num);
    //Free
    free(word);
    //Add NULL to previous location
    Seq_put(mem->segments, seg_num, NULL);
}

/** Load program 
 * @param mem -> Segmented memory 
 * @param seg_num_source -> Segment to retrieve 
 * @param seg_num_destination -> Location to put
 */
void Segment_loadprogram(segment mem, uint32_t seg_num_source, uint32_t seg_num_destination){ 
    // assert(mem);
    // assert(mem->segments);
    uint32_t *source = Seq_get(mem->segments, seg_num_source);
    uint32_t size = source[0];
    Segment_unmap(mem, seg_num_destination);
    assert (Segment_map(mem, size) == seg_num_destination);
    uint32_t *destination = Seq_get(mem->segments, seg_num_destination);
    memcpy(destination, source, ((size + 1) * sizeof(uint32_t)));
}