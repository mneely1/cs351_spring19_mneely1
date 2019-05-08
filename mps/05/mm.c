/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#include "mm.h"
#include "memlib.h"

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)
#define BLK_HDR_SIZE ALIGN(sizeof(blockHDR))
#define BLK_FTR_SIZE ALIGHN(sizeof(blockFTR))

#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

typedef struct header blockHDR;
typedef struct footer blockFTR;
    
struct header{
    size_t size;
    blockHdr *next_pnt;
    blockHdr *prior_p; // Initializes a doubly linked list
};

struct footer{
    blockHdr *head;
};

/* 
 * mm_init - initialize the malloc package.
 */
int mm_init(void)
{
  blockHDR *pnt = mem_sbrk(ALIGN(BLK_HDR_SIZE+BLK_FTR_SIZE));
  pnt->size = BLK_HDR_SIZE +BLK_FTR_SIZE;
  pnt->*next_pnt = pnt;
  pnt->*prior_p = pnt;

  blockFTR *fpnt = (blockFTR*)((char*)mem_heap_hi()-BLK_FTR_SIZE+1);
  fpnt->heap = pnt;

  return 0;

}

/* 
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void *mm_malloc(size_t size)
{
  int newsize = ALIGN(BLK_HDR_SIZE +size + BLK_FTR_SIZE);
  blockHDR *bg_pnt = first_fit(newsize); // Requesting k block bytes to allocate; need to find a fit in order to find a free block to hold the allocated block
  blockFTR *fp_pnt;
  if (bg_pnt === NULL){
    bg_pnt = mem_sbrk(newsize);// requesting more memory for heap
    if ((long)bg == -1){
        return NULL; // Essentially saying that there was an error with our break
    }else{
        fp = (blockFTR *)((char*_)bp + newsize - BLK_FTR_SIZE);
        bg_pnt->next_pnt = bg_pnt->prioer_p = bg_pnt;
        bg_pnt->size = newsize |1;
        fp->size = newsize |1;
        
    }
  }else{
    fp_pnt = (blockFTR*)((char*)(bg_pnt) + (bg_pnt->size & ~1) -BLK_FTR_SIZE);
    bg_pnt->size |= 1;
    fp_pnt->size |= 1; 
  }
  return (char *)bg_pnt + BLK_HDR_SIZE;
}
//does this work
/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *ptr)
{
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size)
{
  void *oldptr = ptr;
  void *newptr;
  size_t copySize;
    
  newptr = mm_malloc(size);
  if (newptr == NULL)
    return NULL;
  copySize = *(size_t *)((char *)oldptr - SIZE_T_SIZE);
  if (size < copySize)
    copySize = size;
  memcpy(newptr, oldptr, copySize);
  mm_free(oldptr);
  return newptr;
}
