#include "my_malloc.h"

/* You *MUST* use this macro when calling my_sbrk to allocate the
 * appropriate size. Failure to do so may result in an incorrect
 * grading!
 */
#define SBRK_SIZE 2048
#define INF 1.0/0.0

/* If you want to use debugging printouts, it is HIGHLY recommended
 * to use this macro or something similar. If you produce output from
 * your code then you may receive a 20 point deduction. You have been
 * warned.
 */
#ifdef DEBUG
#define DEBUG_PRINT(x) printf x
#else
#define DEBUG_PRINT(x)
#endif


/* our freelist structure - this is where the current freelist of
 * blocks will be maintained. failure to maintain the list inside
 * of this structure will result in no credit, as the grader will
 * expect it to be maintained here.
 * Technically this should be declared static for the same reasons
 * as above, but DO NOT CHANGE the way this structure is declared
 * or it will break the autograder.
 */
  metadata_t* freelist;
  metadata_t* remain;
 


//helper function to initialize the list
metadata_t* initList(void) {
	metadata_t *temp = my_sbrk(SBRK_SIZE);
		if (temp == NULL) {
			ERRNO = OUT_OF_MEMORY;
			return NULL;
		}
	temp->in_use = 0;
	temp->size = SBRK_SIZE;
	temp->prev = NULL;
	temp->next = NULL;
	ERRNO = NO_ERROR;
	return temp;
}

// helper function, if sorting==0 size order, if sorting==1 addr order
 void* my_malloc(size_t size, int sorting) {
 	//calculating size to be allocated and checking if it's too large
	size_t real_size = size + sizeof(metadata_t);
 	if (real_size > SBRK_SIZE) {
 		ERRNO = SINGLE_REQUEST_TOO_LARGE;
 		return NULL;
 	}
 	//initiallizing freelist or requesting more memory
 	if(freelist == NULL) { 
		freelist = initList();
		if (freelist == NULL) {
			ERRNO = OUT_OF_MEMORY;
			return NULL;
		}
	}
	//allocating the smallest chunk the user requested
	metadata_t *current = freelist;
	short min = SBRK_SIZE;
	metadata_t *minPtr = NULL;
	while (current != NULL) {
		if (current->size <= min && current->size >= real_size) {
			min = current->size;
			minPtr = current;
		}
		if (current->next != NULL) {
			current = current->next;
		} else {
			break;
		}
	}
	if (minPtr == NULL) {
		metadata_t *newchunk = initList();
		if (newchunk == NULL) {
			ERRNO = OUT_OF_MEMORY;
			return NULL;
		}
		minPtr = newchunk;
	}
	// if (minPtr == freelist) {
	// 	freelist = NULL;
	// }
	// if (minPtr->prev != NULL && minPtr->next != NULL) {
	// 	minPtr->prev->next = minPtr->next;
	// 	minPtr->next->prev = minPtr->prev;
	// }
	//split the block
	if (minPtr->size - real_size == 0) {
		freelist = NULL;
		remain = NULL;
	} else {
		remain = (metadata_t*)((uintptr_t)minPtr + (char*)real_size);
		remain->in_use = 0;
		remain->prev = NULL;
		remain->next = NULL;
		remain->size = minPtr->size - real_size;
	}
	//insert the remaining block back into list
	if (freelist == NULL || freelist == minPtr) {
		//remain->next = freelist->next;
		//remain->prev = freelist->prev;
		freelist = remain;

	} else {
		current = freelist;
		int inserted = 0;
		if (!sorting) {			//size_order
			while (current->next != NULL) {
				if (current->size >= remain->size) {
					remain->prev = current->prev;
					remain->next = current;
					current->prev = remain;
					inserted =1;
					break;
				} else {
					current = current->next;
				}
			}
			if (!inserted) {
				if (current->size <= remain->size) {
					current->next = remain;
					remain->prev = current;
				} else {
					if (current->prev != NULL) {
						current->prev->next = remain;
						remain->prev = current->prev;
					}
					current->prev = remain;
					remain->next = current;
				}
			}
		} else {
			while (current->next != NULL) {
				if (current >= remain) {
					remain->prev = current->prev;
					remain->next = current;
					current->prev = remain;
					inserted = 1;
					break;
				} else {
					current = current->next;
				}
			}
			if (!inserted) {
				if (current <= remain) {
					current->next = remain;
					remain->prev = current;
				} else {
					if (current->prev != NULL) {
						current->prev->next = remain;
						remain->prev = current->prev;
					}
					current->prev = remain;
					remain->next = current;
				}
			}
		}
	}

	ERRNO = NO_ERROR;


	//processing the pointer returned
	minPtr->in_use = 1;
	minPtr->size = real_size;
	//minPtr->next = NULL;
	//minPtr->prev = NULL;
	void* ret = (void*)((uintptr_t) minPtr + sizeof(metadata_t));
	//freelist = freelist;

 	return ret;
 	
 }

 void* my_malloc_size_order(size_t size)
 {
 	return my_malloc(size, 0);
 }

 void* my_malloc_addr_order(size_t size)
 {
  	return my_malloc(size, 1);
 }

 //generic free function, sorting==0 size_order, sorting==1 addr_order
 void my_free(void* ptr, int sorting) {
 	if (ptr == NULL) {
 		return;
 	}
 	//freelist = freelist;
 	metadata_t* metaptr = (metadata_t*)((uintptr_t)ptr - sizeof(metadata_t));
 	metaptr->in_use = 0;
 	metaptr->prev = NULL;
 	metaptr->next = NULL;
 	metadata_t* right = (metadata_t*)((uintptr_t)metaptr + metaptr->size);
 	//find the block to the left of the block being freed
 	metadata_t* left = NULL;
 	metadata_t* current = NULL;
 	if (freelist != NULL) {
 		current = freelist;
	 	while (current != NULL) {
	 		if ((current + current->size) == metaptr) {
	 			left = current;
	 		} else {
	 			current = current->next;
	 		}
	 	}	
 	}
 	int mergeleft = 0;
 	int mergeright = 0;
 	if (right->in_use == 0) {
 		mergeright = 1;
 		//right->in_use = 0;
 		//right->size = 0;
 		if (right->prev != NULL && right->next != NULL) {
 			right->prev->next = right->next;
 			right->next->prev = right->prev;
 		} else if (right->prev != NULL && right->next == NULL) {
 			right->prev->next = NULL;
 		} else if (right->next != NULL && right->prev == NULL) {
 			right->next->prev = NULL;
 		}
 		right->prev = NULL;
 		right->next = NULL;
 	}
 	if (left != NULL) {
 		mergeleft = 1;
 		//left ->in_use = 0;
 		//left->size = 0;
 		if (left->prev != NULL && left->next != NULL) {
 			left->prev->next = left->next;
 			left->next->prev = left->prev;
 		} else if (left->prev != NULL && left->next == NULL) {
 			left->prev->next = NULL;
 		} else if (left->next != NULL && left->prev == NULL) {
 			left->next->prev = NULL;
 		}
 		left->prev = NULL;
 		left->next = NULL;
 	}


 	//merging with left and right
 	if (!mergeleft && mergeright) {		//case 1 left in use and right not in use
 		size_t rightsize = right->size;
 		size_t metaptrsize = metaptr->size;
 		metaptr->size = rightsize + metaptrsize;
 		// right = NULL;
 		// right->prev->next = right->next;
 		// right->next->prev = right->prev;
 	} else if (mergeleft && !mergeright) {	//case 2 left not in use right in use
 		size_t leftsize = left->size;
 		size_t metaptrsize = metaptr->size;
 		metaptr -= (char)leftsize;
 		metaptr->size = leftsize + metaptrsize;
 		if (freelist == left) {
 			freelist = metaptr;
 		}
 		// left = NULL;
 		// left->prev->next = left->next;
 		// left->next->prev = left->prev;
 	} else if (mergeleft && mergeright) {	//case 3 left and right not in use
 		size_t leftsize = left->size;
 		size_t metaptrsize = metaptr->size;
 		metaptr -= (char)leftsize;
 		if (freelist == left) {
 			freelist = metaptr;
 		}
 		metaptr->size = leftsize + metaptrsize + right->size;
 		// right = NULL;
 		// left = NULL;
 		// left->prev->next = left->next;
 		// left->next->prev = left->prev;
 		// right->prev->next = right->next;
 		// right->next->prev = right->prev;
 	}
 	if (!sorting) {		//size_order
 		if (freelist == NULL) {
 			freelist = metaptr;
 		} else {
	 		current = freelist;
	 		int inserted = 0;
	 		while (current->next != NULL) {
	 			if (current->size > metaptr->size) {
	 				metaptr->next = current;
	 				metaptr->prev = current->prev;
	 				current->prev = metaptr;
	 				inserted = 1;
	 				break;
	 			} else {
	 				current = current->next;
	 			}
	 		}
	 		if (!inserted) {
				if (current->size <= metaptr->size) {
					current->next = metaptr;
					metaptr->prev = current;
				} else {
					if (current->prev != NULL) {
						current->prev->next = metaptr;
						metaptr->prev = current->prev;
					}
					current->prev = metaptr;
					metaptr->next = current;
				}
			}
			while (freelist->prev != NULL) {
				freelist = freelist->prev;
			}
	 	}
 	} else {		//addr_order
 		if (freelist == NULL) {
 			freelist = metaptr;
 		} else {
	 		current = freelist;
	 		int inserted = 0;
	 		while (current->next != NULL) {
	 			if (current > metaptr) {
	 				metaptr->next = current;
	 				metaptr->prev = current->prev;
	 				current->prev = metaptr;
	 				inserted = 1;
	 				break;
	 			} else {
	 				current = current->next;
	 			}
	 		}
	 		if (!inserted) {
				if (current <= metaptr) {
					current->next = metaptr;
					metaptr->prev = current;
				} else {
					if (current->prev != NULL) {
						current->prev->next = metaptr;
						metaptr->prev = current->prev;
					}
					current->prev = metaptr;
					metaptr->next = current;
				}
			}
			while (freelist->prev != NULL) {
				freelist = freelist->prev;
			}
	 	}
 	}
 	//freelist = freelist;
 }

 void my_free_size_order(void* ptr)
 {
  my_free(ptr, 0);
 }

 void my_free_addr_order(void* ptr)
 {
  my_free(ptr, 1);
 }

