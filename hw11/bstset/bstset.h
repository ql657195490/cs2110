/**
 * CS 2110 - Fall 2015 - Homework #11
 * Andrew Wilder
 * bstset.h
 */

#ifndef BSTSET_H
#define BSTSET_H

/************************
 * Datatype Definitions *
 * DO NOT TOUCH THESE   *
 ************************/

/* Forward declaration of type struct bnode
 * Don't know what forward declaration is? Consult the fountain of knowledge:
 * http://en.wikipedia.org/wiki/Forward_declaration
 */
struct bnode_t;

/* The bstset struct. Has a root and a size only. */
typedef struct bstset_t {
	struct bnode_t *root;
	unsigned int size;
} bstset;

/* A function pointer type for functions that take in void* and return nothing
 * Such a function may be useful for doing something to modify the data
 * The name of this type is "bst_op"
 */
typedef void (*bst_op)(void*);

/* A function pointer type for functions that take in two const void* and return an int
 * Such a function may be useful for comparing data
 * The name of this type is "bst_pred" (short for predicate)
 */
typedef int (*bst_comp)(const void*, const void*);

/********************************************
 * Prototypes for bst set library functions *
 * For more details on their functionality, *
 * see the documentation in bstset.c        *
 ********************************************/

bstset *create_bstset(void);
int add(bstset *bst, void *data, bst_comp comp_func);
void *min(bstset *bst);
void *max(bstset *bst);
int contains(bstset *bst, void *data, bst_comp comp_func);
void traverse(bstset *bst, bst_op do_func);
void destroy(bstset *bst, bst_op free_func);
#endif

