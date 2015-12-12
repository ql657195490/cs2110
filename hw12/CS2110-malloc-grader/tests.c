#include "tests.h"

size_t total_freelist_size() {
    size_t total = 0;
    for (metadata_t *t = freelist; t; t = t->next)
        total += t->size;
    return total;
}
size_t total_freelist_count() {
    size_t total = 0;
    for (metadata_t *t = freelist; t; t = t->next)
        total++;
    return total;
}
int freelist_ordered_general(int is_size) {
    for (metadata_t *t = freelist; t; t = t->next)
        if (t->next && (is_size ? t->size > t->next->size : t > t->next))
            return 0;
    return 1;
}
int freelist_ordered_size() { return freelist_ordered_general(1); }
int freelist_ordered_addr() { return freelist_ordered_general(0); }

/* Thoroughly checks their test_malloc function */
void check_malloc_general_1(void*(*test_malloc)(size_t), void(*test_free)(void*), int(*freelist_ordered)(void), const char *tag) {

    int size1 = 10, size2 = 100, size3 = 500, size4 = 1200;

    /* Malloc a 64-byte chunk of memory. */
    metadata_t *arr1 = test_malloc(size1);

    /* Check in_use, size flags */
    if (NULL == arr1 || (arr1 - 1)->in_use != 1) {
        deduct_points(M_IN_USE_POINTS, tag, "the in_use field of the metadata was "
                "not set to 1 when returned;");
    } else {
        add_points(M_IN_USE_POINTS, tag, "the in_use field of the metadata was "
                "set to 1 when returned;");
    }
    if (NULL == arr1 ||
            (arr1 - 1)->size != size1+sizeof(metadata_t)) {
        deduct_points(M_SIZE_POINTS, tag, "the block of data was not malloced to "
                "the proper size;");
    }  else {
        add_points(M_SIZE_POINTS, tag, "the block of data was malloced to "
                "the proper size;");
    }

    /* Check the total free list size */
    {
        if (total_freelist_size() != SBRK_SIZE - (size1 + sizeof(metadata_t)) ) {
            deduct_points(M_FREELIST_POINTS, tag, "the freelist is not what it "
                    "should be, which will throw off everything else in your "
                    "library;");
        } else if (!freelist_ordered()) {
            deduct_points(M_FREELIST_POINTS, tag, "the freelist is not what it "
                    "should be, which will throw off everything else in your "
                    "library;NOT ORDERED");
        } else {
            add_points(M_FREELIST_POINTS, tag, "the freelist is what it "
                    "should be");
        }
    }

    /* test 2 malloc (serious test) */
    metadata_t *arr2 = test_malloc(size2);
    
    metadata_t *arr3 = test_malloc(size3);
    
    metadata_t *arr4 = test_malloc(size4);

    test_free(arr2);

    test_free(arr4);    

    {
        if (total_freelist_size(freelist) != SBRK_SIZE - (size1+size3 + sizeof(metadata_t)*2) || !freelist_ordered()) {
            deduct_points(M_FREELIST2_POINTS, tag, "the freelist is not what it "
                    "should be after a couple of calls to malloc;");
        } else {
            add_points(M_FREELIST2_POINTS, tag, "the freelist is what it "
                    "should be after a couple of calls to malloc;");
        }
    }

    /* malloc enough to make it allocate another block */
    arr2 = test_malloc(size3+size4);
    {
        if (total_freelist_size(freelist) != 2*SBRK_SIZE - (size1+size3*2 + size4 + sizeof(metadata_t)*3) || !freelist_ordered()) {
            deduct_points(M_FREELIST3_POINTS, tag, "the freelist is not what it "
                    "should be after a couple more calls to malloc;");
        } else {
            add_points(M_FREELIST3_POINTS, tag, "the freelist is what it "
                    "should be after a couple more calls to malloc;");
        }
    }
}
void check_malloc_1_size() {
    check_malloc_general_1(my_malloc_size_order, my_free_size_order, freelist_ordered_size, "check_malloc_1_size");
}
void check_malloc_1_addr() {
    check_malloc_general_1(my_malloc_addr_order, my_free_addr_order, freelist_ordered_addr, "check_malloc_1_addr");
}

void check_malloc_general_2(void*(*test_malloc)(size_t), void(*test_free)(void*), int(*freelist_ordered)(void), const char *tag) {
    /* Malloc's edge cases. */
    metadata_t *it = test_malloc(SBRK_SIZE - sizeof(metadata_t));
    if (it == NULL)
        deduct_points(MALLOC_EDGE_MAX, tag, "Did not allocate max size;");
    else
        add_points(MALLOC_EDGE_MAX, tag, "Did allocate max size;");
    test_free(it);

    it = test_malloc(SBRK_SIZE - sizeof(metadata_t) + 1);
    if (it != NULL)
        deduct_points(MALLOC_EDGE_MAX1, tag, "Allocated max size + 1;");
    else
        add_points(MALLOC_EDGE_MAX1, tag, "Did not allocat max size + 1;");

    it = test_malloc(1000000);
    if (it != NULL)
        deduct_points(MALLOC_EDGE_HUGE, tag, "Allocated 1000000 bytes;");
    else
        add_points(MALLOC_EDGE_HUGE, tag, "Did not allocate 1000000 bytes;");

    int i;
    void *mem[5];
    for (i = 0; i < 5; i++)
        mem[i] = test_malloc(SBRK_SIZE - sizeof(metadata_t));
    if (mem[4] != NULL)
        deduct_points(MALLOC_OOM, tag, "Did not return NULL for OOM;");
    else
        add_points(MALLOC_OOM, tag, "Did return NULL for OOM;");
}
void check_malloc_2_size() {
    check_malloc_general_2(my_malloc_size_order, my_free_size_order, freelist_ordered_size, "check_malloc_2_size");
}
void check_malloc_2_addr() {
    check_malloc_general_2(my_malloc_addr_order, my_free_addr_order, freelist_ordered_addr, "check_malloc_2_addr");
}

void check_malloc_general_3(void*(*test_malloc)(size_t), void(*test_free)(void*), int(*freelist_ordered)(void), const char *tag) {
    char* last_data = NULL;
    for (size_t i = 0; i < 1000; i++) {
        size_t size = (i*i)%1000 + 1;
        char* data = test_malloc(size);
        for (size_t j = 0; j < size; j++)
            data[j] = i*j;
        if (last_data) {
            size_t old_size = ((i-1)*(i-1))%1000 + 1;
            for (size_t j = 0; j < old_size; j++)
                if (last_data[j] != (char)((i-1)*j)) {
                    deduct_points(MALLOC_STRESS, tag, "Did not pass stress test");
                    return;
                }
            test_free(last_data);
        }
        last_data = data;
    }
    test_free(last_data);
    add_points(MALLOC_STRESS, tag, "Did not pass stress test");
}
void check_malloc_3_size() {
    check_malloc_general_3(my_malloc_size_order, my_free_size_order, freelist_ordered_size, "check_malloc_3_size");
}
void check_malloc_3_addr() {
    check_malloc_general_3(my_malloc_addr_order, my_free_addr_order, freelist_ordered_addr, "check_malloc_3_addr");
}

/*[> Thoroughly checks their test_free function <]*/
void check_free_1_general(void*(*test_malloc)(size_t), void(*test_free)(void*), int(*freelist_ordered)(void), const char *tag) {
    metadata_t *arr1, *arr2, *arr3, *arr4;
    arr1 = test_malloc(1);
    arr2 = test_malloc(1);
    arr3 = test_malloc(1);
    arr4 = test_malloc(1);

    /*[> Free flag <]*/
    test_free(arr2);
    if ((arr2 - 1)->in_use != 0) {
        deduct_points(F_IN_USE_POINTS, tag, "the in_use field was not set to 0 when "
                "freed;");
    } else {
        add_points(F_IN_USE_POINTS, tag, "the in_use field was set to 0 when freed;");
    }

    /*[> Now, make sure that they didn't combine the nodes <]*/
    if ((arr2 - 1)->size != (1+sizeof(metadata_t))) {
        deduct_points(F_NO_COMBINE, tag, "Combined the size improperly;");
    } else {
        if (total_freelist_size() != SBRK_SIZE - 3*(1 + sizeof(metadata_t)) || !freelist_ordered()) {
            deduct_points(F_NO_COMBINE, tag, "freelist is not correct after one "
                    "free;");
        } else {
            add_points(F_NO_COMBINE, tag, "freelist is correct after one free;");
        }
    }

    /*[> Combine two nodes into one <]*/
    test_free(arr1);
    if ((arr1 - 1)->size == 1+sizeof(metadata_t) && (arr2 - 1)->size == 1+sizeof(metadata_t)) {
        deduct_points(F_COMBINE, tag, "Did not combine two nodes into one;");
    } else {
        if (total_freelist_size() != SBRK_SIZE - 2*(1 + sizeof(metadata_t)) || !freelist_ordered()) {
            deduct_points(F_COMBINE, tag, "the freelist is not what it should be "
                    "after combining one node;");
        } else {
            add_points(F_COMBINE, tag, "the freelist is what it should be "
                    "after combining one node;");
        }
    }

    /*[> Combine all of the way to 2048 <]*/
    test_free(arr3);
    test_free(arr4);
    {
        if (total_freelist_size() != SBRK_SIZE || total_freelist_count() != 1 || !freelist_ordered()) {
            deduct_points(F_COMBINE_RECURSE, tag, "the freelist is not correct after"
                    " combining all to 2048;");
        } else {
            add_points(F_COMBINE_RECURSE, tag, "the freelist is correct after"
                    " combining all to 2048;");
        }
    }
}
void check_free_1_size() {
    check_free_1_general(my_malloc_size_order, my_free_size_order, freelist_ordered_size, "check_free_1_size");
}
void check_free_1_addr() {
    check_free_1_general(my_malloc_addr_order, my_free_addr_order, freelist_ordered_addr, "check_free_1_addr");
}

void check_free_2_general(void*(*test_malloc)(size_t), void(*test_free)(void*), int(*freelist_ordered)(void), const char *tag) {
    /*[> The next check is to make sure we do combine with a different size. <]*/
    metadata_t *arr1 = test_malloc(64);
    metadata_t *arr3 = test_malloc(32);
    metadata_t *arr4 = test_malloc(32);
    test_free(arr3);
    test_free(arr1);
    if (arr1 == NULL || (arr1 - 1)->size == 64+sizeof(metadata_t)) {
        deduct_points(F_DIFF_SIZE, tag, "Did not combine two nodes into one;");
    } else {
        if (total_freelist_size() != SBRK_SIZE - (32+sizeof(metadata_t)) || total_freelist_count() != 2 || !freelist_ordered()) {
            deduct_points(F_DIFF_SIZE, tag, "the freelist is not correct after "
                    "freeing a buddy of different size;");
        } else {
            add_points(F_DIFF_SIZE, tag, "the freelist is correct after "
                    "freeing a buddy of different size;");
        }
    }
}
void check_free_2_size() {
    check_free_2_general(my_malloc_size_order, my_free_size_order, freelist_ordered_size, "check_free_2_size");
}
void check_free_2_addr() {
    check_free_2_general(my_malloc_addr_order, my_free_addr_order, freelist_ordered_addr, "check_free_2_addr");
}
void check_free_3_general(void*(*test_malloc)(size_t), void(*test_free)(void*), int(*freelist_ordered)(void), const char *tag) {

    /* The next set of test cases is essentially test code for the linked list
     * free list implementations. So far, in all of the above, the frees only
     * removed the only element from the list. The next three tests will have
     * three free list nodes, one of which is the buddy being freed.
     */
    metadata_t *arr1 = test_malloc(1);
    metadata_t *arr2 = test_malloc(1);
    test_malloc(1); //[> Prevent recombination <]
    metadata_t *arr3 = test_malloc(1);
    test_malloc(1); //[> Prevent recombination <]
    metadata_t *arr4 = test_malloc(1);
    test_free(arr2);
    test_free(arr3);
    test_free(arr4);
    test_free(arr1);
    if (total_freelist_size() != SBRK_SIZE - 2*(1+sizeof(metadata_t)) || total_freelist_count() != 3 || !freelist_ordered()) {
        deduct_points(FREE_MULTI_HEAD, tag, "freelist not correct if buddy is "
                "first in list;");
    } else {
        add_points(FREE_MULTI_HEAD, tag, "freelist correct if buddy is "
                "first in list;");
    }
}
void check_free_3_size() {
    check_free_3_general(my_malloc_size_order, my_free_size_order, freelist_ordered_size, "check_free_3_size");
}
void check_free_3_addr() {
    check_free_3_general(my_malloc_addr_order, my_free_addr_order, freelist_ordered_addr, "check_free_3_addr");
}
void check_free_4_general(void*(*test_malloc)(size_t), void(*test_free)(void*), int(*freelist_ordered)(void), const char *tag) {
    metadata_t *arr1 = test_malloc(1);
    metadata_t *arr2 = test_malloc(1);
    test_malloc(1); //[> Prevent recombination <]
    metadata_t *arr3 = test_malloc(1);
    test_malloc(1); //[> Prevent recombination <]
    metadata_t *arr4 = test_malloc(1);
    test_free(arr3);
    test_free(arr2);
    test_free(arr4);

    test_free(arr1);
    {
        if (total_freelist_size() != SBRK_SIZE - 2*(1+sizeof(metadata_t)) || total_freelist_count() != 3 || !freelist_ordered()) {
            deduct_points(FREE_MULTI_MID, tag, "freelist not correct if buddy is "
                    "second in list;");
        } else {
            add_points(FREE_MULTI_MID, tag, "freelist correct if buddy is "
                    "second in list;");
        }
    }
}
void check_free_4_size() {
    check_free_4_general(my_malloc_size_order, my_free_size_order, freelist_ordered_size, "check_free_4_size");
}
void check_free_4_addr() {
    check_free_4_general(my_malloc_addr_order, my_free_addr_order, freelist_ordered_addr, "check_free_4_addr");
}

void check_free_5_general(void*(*test_malloc)(size_t), void(*test_free)(void*), int(*freelist_ordered)(void), const char *tag) {
    metadata_t *arr1 = test_malloc(1);
    metadata_t *arr2 = test_malloc(1);
    test_malloc(1); //[> Prevent recombination <]
    metadata_t *arr3 = test_malloc(1);
    test_malloc(1); //[> Prevent recombination <]
    metadata_t *arr4 = test_malloc(1);
    test_free(arr3);
    test_free(arr4);
    test_free(arr2);
    test_free(arr1);
    {
        if (total_freelist_size() != SBRK_SIZE - 2*(1+sizeof(metadata_t)) || total_freelist_count() != 3 || !freelist_ordered()) {
            deduct_points(FREE_MULTI_TAIL, tag, "freelist not correct if buddy is "
                    "last in list;");
        } else {
            add_points(FREE_MULTI_TAIL, tag, "freelist correct if buddy is "
                    "last in list;");
        }
    }

    /*test_free(NULL);*/
}
void check_free_5_size() {
    check_free_5_general(my_malloc_size_order, my_free_size_order, freelist_ordered_size, "check_free_5_size");
}
void check_free_5_addr() {
    check_free_5_general(my_malloc_addr_order, my_free_addr_order, freelist_ordered_addr, "check_free_5_addr");
}
void *c1,*c2,*c3,*c4,*c5,*c6,*c7,*c8;
enum my_malloc_err e1, e2, e3,e4,e5,e6,e7,e8;
void check_EC_1_general(void*(*test_malloc)(size_t), void(*test_free)(void*), int(*freelist_ordered)(void), const char *tag) {
    e1 = e2 = e3 = e4 = 999;

    printf("Testing 16\n");
    c1 = test_malloc(2048);
    e1 = ERRNO;

    printf("Testing 17\n");
    c2 = test_malloc(2048-sizeof(metadata_t)+1);
    e2 = ERRNO;
    printf("Testing 18\n");
    c3 = test_malloc(2048-sizeof(metadata_t));
    e3 = ERRNO;

    printf("Testing 19\n");
    c4 = test_malloc(512);
    e4 = ERRNO;

    printf("Finished EC part 1\n");
    if(	((e1!=SINGLE_REQUEST_TOO_LARGE)||
                (e2!=SINGLE_REQUEST_TOO_LARGE)||
                (e3==SINGLE_REQUEST_TOO_LARGE)||
                (e4==SINGLE_REQUEST_TOO_LARGE))
      )
        deduct_points(ERR_SINGLE_REQUEST_TOO_LARGE_POINTS, tag, "Error code SINGLE_REQUEST_TOO_LARGE not used correctly.");
    else
        add_points(ERR_SINGLE_REQUEST_TOO_LARGE_POINTS, tag, "Error code SINGLE_REQUEST_TOO_LARGE used correctly.");

}
void check_EC_1_size() {
    check_EC_1_general(my_malloc_size_order, my_free_size_order, freelist_ordered_size, "check_EC_1_size");
}
void check_EC_1_addr() {
    check_EC_1_general(my_malloc_addr_order, my_free_addr_order, freelist_ordered_addr, "check_EC_1_addr");
}

void check_EC_2_general(void*(*test_malloc)(size_t), void(*test_free)(void*), int(*freelist_ordered)(void), const char *tag) {
    /*[>check out of memory<]*/
    printf("Testing 20\n");
    c1 = test_malloc(2000);
    c2 = test_malloc(2000);
    /*[> need more calls <]*/
    c2 = test_malloc(2000);
    c2 = test_malloc(2000);
    c3 = test_malloc(1);

    e1 = ERRNO;
    if(e1!=OUT_OF_MEMORY)
        deduct_points(ERR_OUT_OF_MEMORY_POINTS, tag, "Error code OUT_OF_MEMORY not used correctly.");
    else
        add_points(ERR_OUT_OF_MEMORY_POINTS, tag, "Error code OUT_OF_MEMORY used correctly.");

    printf("Finished EC part 2\n");
}
void check_EC_2_size() {
    check_EC_2_general(my_malloc_size_order, my_free_size_order, freelist_ordered_size, "check_EC_2_size");
}
void check_EC_2_addr() {
    check_EC_2_general(my_malloc_addr_order, my_free_addr_order, freelist_ordered_addr, "check_EC_2_addr");
}
void check_EC_3_general(void*(*test_malloc)(size_t), void(*test_free)(void*), int(*freelist_ordered)(void), const char *tag) {
    c1 = test_malloc(48);
    e1 = ERRNO;
    test_free(c1);
    /*[>Quick No_ERROR test<]*/
    if(e1!=NO_ERROR)
        deduct_points(ERR_NO_ERROR_POINTS, tag, "Error code NO_ERROR not used correctly.");
    else
        add_points(ERR_NO_ERROR_POINTS, tag, "Error code NO_ERROR used correctly.");
}
void check_EC_3_size() {
    check_EC_3_general(my_malloc_size_order, my_free_size_order, freelist_ordered_size, "check_EC_3_size");
}
void check_EC_3_addr() {
    check_EC_3_general(my_malloc_addr_order, my_free_addr_order, freelist_ordered_addr, "check_EC_3_addr");
}

/*[>prints out what the freeList should look like<]*/
void printList() {
    int i;
    metadata_t *temp;
    printf("------LIST-----\n");
    for (temp = freelist; temp != NULL; temp = temp->next) {
        printf("%d->", temp->size);
    }
    printf("NULL\n");
    printf("------END------\n");
}
