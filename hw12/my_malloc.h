#ifndef __MY_MALLOC_H__
#define __MY_MALLOC_H__

/* we need this *ONLY* for the size_t typedef */
#include <stdio.h>
/* we need this for uintptr_t */
#include <stdint.h>

/* our metadata structure for use in the freelist.
 * you *MUST NOT* change this definition unless specified
 * in an official assignment update by the TAs.
 */
typedef struct metadata
{
  short in_use;
  short size;
  struct metadata* next;
  struct metadata* prev;
} metadata_t;
/* This is your error enum. The three
 * different types of errors for this homework are explained below.
 * If ANY function has a case where one of the errors described could
 * occur, it must set ERRNO to the appropriate enum.
 * In the case where a single request is too large and
 * the request results in an out of memory error as well, the
 * SINGLE_REQUEST_TOO_LARGE should take precedence. If any of the three
 * functions complete successfully, the error code should be set to
 * NO_ERROR. */
enum my_malloc_err {
	NO_ERROR,
	OUT_OF_MEMORY,
	SINGLE_REQUEST_TOO_LARGE
};
enum my_malloc_err ERRNO;

/* MALLOC
 *
 * this function should allocate a block that is big enough to hold the
 * specified size, and that is all. if there is not a block that is able
 * to satisfy the request, then you should attempt to grab more heap
 * space with a call to my_sbrk. if this succeeds, then you should continue
 * as normal. If it fails (by returning NULL), then you should return NULL.
 *
 * Two versions of this function:
 *  * my_malloc_size_order uses the freelist that is sorted in increasing order of size
 *  * my_malloc_addr_order uses the freelist that is sorted in increasing order of address
 */
void* my_malloc_size_order(size_t);
void* my_malloc_addr_order(size_t);

/* FREE
 *
 * this function should free the block of memory, recursively merging
 * buddies up the freelist until they can be merged no more.
 * Two versions of this function:
 *  * my_free_size_order uses the freelist that is sorted in increasing order of size
 *  * my_free_addr_order uses the freelist that is sorted in increasing order of address
 */
void my_free_size_order(void *);
void my_free_addr_order(void *);


/* this function will emulate the system call sbrk(2). if you do not
 * have enough free heap space to satisfy a memory request, then you
 * must call this function to allocate memory to your allocator.
 */
void* my_sbrk(int);

metadata_t* initList(void);
void* my_malloc(size_t size, int sorting);
void my_free(void* ptr, int sorting);

#endif /* __MY_MALLOC_H__ */
