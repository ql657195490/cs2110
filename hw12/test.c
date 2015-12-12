#include <stdlib.h>
#include <time.h>
#include "my_malloc.h"

typedef void* (*malloc_func_type)(size_t);
typedef void (*free_func_type)(void *);

void test(malloc_func_type my_malloc, free_func_type my_free) {
	/*
	 * Test code goes here, using my_malloc and my_free function pointers
	 */
}

int main() {
    /* you can change this number to modify how many times the function will be run */
    const long unsigned int NUM_RUNS = 1000;
    clock_t start_time = clock();
    for (long unsigned int i = 0; i < NUM_RUNS; i++)
        test(my_malloc_size_order, my_free_size_order);

    clock_t post_size_time = clock();
    for (long unsigned int i = 0; i < NUM_RUNS; i++)
        test(my_malloc_addr_order, my_free_addr_order);

    clock_t post_addr_time = clock();
    long unsigned int milli_seconds_size = (post_size_time - start_time) * 1000 / CLOCKS_PER_SEC;
    long unsigned int milli_seconds_addr = (post_addr_time - post_size_time) * 1000 / CLOCKS_PER_SEC;

    printf("Time to run %lu iterations in milliseconds:\n", NUM_RUNS);
    printf("sorted by size test: %lu\n", milli_seconds_size);
    printf("sorted by addr test: %lu\n", milli_seconds_addr);

	return 0;
}
