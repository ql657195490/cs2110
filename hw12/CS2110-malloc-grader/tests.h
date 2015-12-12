#include <string.h>
#include <unistd.h>
#include "grader.h"
#include "malloc_common.h"

#define SBRK_SIZE 2048


/**********************************************************
 * if you add a test function to tests.c, add its name here
 * This list is how we delcare them below and how we setup
 * an array, an enum, and the switch statement in grader.c
 * so that they all get run.
 *********************************************************/
#define TEST_FUNCTION_LIST \
X(check_malloc_1_size)\
X(check_malloc_1_addr)\
X(check_malloc_2_size)\
X(check_malloc_2_addr)\
X(check_malloc_3_size)\
X(check_malloc_3_addr)\
X(check_free_1_size)\
X(check_free_1_addr)\
X(check_free_2_size)\
X(check_free_2_addr)\
X(check_free_3_size)\
X(check_free_3_addr)\
X(check_free_4_size)\
X(check_free_4_addr)\
X(check_free_5_size)\
X(check_free_5_addr)\
X(check_EC_1_size)\
X(check_EC_1_addr)\
X(check_EC_2_size)\
X(check_EC_2_addr)\
X(check_EC_3_size)\
X(check_EC_3_addr)

/* here's an example of how this macro works -
 * This will declare each function as void and
 * taking no parameters */
#define X(test_func) void test_func();
TEST_FUNCTION_LIST
#undef X

void printList();

/* students methods */
void* my_malloc_size_order(size_t);
void* my_malloc_addr_order(size_t);
void my_free_size_order(void *);
void my_free_addr_order(void *);

/* the freelist */
extern metadata_t* freelist;

/* Point distribution. The total must add up to TOTAL_POINTS_POSSIBLE. */
#define TOTAL_POINTS_POSSIBLE 100

// these are set at about half their normal values because we're testing it twice
#define M_IN_USE_POINTS     2
#define M_SIZE_POINTS       2
#define M_FREELIST_POINTS   6 /* First check wrong */
#define M_FREELIST2_POINTS  3 /* Second check wrong */
#define M_FREELIST3_POINTS  2 /* Third check wrong */
#define MALLOC_STRESS       5
#define MALLOC_EDGE_MAX     2
#define MALLOC_EDGE_MAX1    2
#define MALLOC_EDGE_HUGE    2
#define MALLOC_OOM          2

#define F_IN_USE_POINTS     2
#define F_NO_COMBINE        2
#define F_COMBINE           2
#define F_COMBINE_RECURSE   2
#define F_DIFF_SIZE         2
#define FREE_MULTI_HEAD     2
#define FREE_MULTI_MID      2
#define FREE_MULTI_TAIL     2

#define ERR_NO_ERROR_POINTS 2
#define ERR_OUT_OF_MEMORY_POINTS 2
#define ERR_SINGLE_REQUEST_TOO_LARGE_POINTS 2

