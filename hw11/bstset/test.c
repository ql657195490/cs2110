#include "bstset.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
 
/* Here we are going to write some functions to support a bst set that stores
 * person data (name, age)
 */
typedef struct person_t {
	char *name;
	int age;
} person;
 
/**
 * Simple struct for some ints
 * written by: Nate G.
 */
typedef struct number_t {
	int value;
} number;
 
 
static int comparisons;
 
//test prototypes
void TA_cases(void);
void additional_cases(void);
void edge_cases(void); //not necessarily ALL of the edge cases
person *create_person(const char*, int);
void print_person(void*);
void free_person(void*);
int person_age_comp(const void*, const void*);
int person_name_comp(const void*, const void*);
number *create_int(const int);
int compare_numbers(const void*, const void*);
void free_int(void*);
void print_int(void*);
 
 
/**
 * Where we call the cases
 */
int main(void) {
	edge_cases();
	additional_cases();
	TA_cases();
 
	return 0;
}
 
 
//using a data structure of simple ints
//will test for a left-heavy and right-heavy tree (where runtime becomes O(n))
//written by: Nate G.
void edge_cases(void) {
	printf("\nedge_cases");
	//Righ-heavy BST
	bstset *intsBSTR = create_bstset();
	number *arrOfInts[15];
	for (int i = 0; i < 15; i++) {
		arrOfInts[i] = create_int(i + 1);
	}
	printf("\nCreate a right-sided tree.");
	printf("\nAdding 1-15 to the BST. Should return 0 for every element added. Test will halt if this isn't true.");
	//Will look like this: http://i.imgur.com/VToKoyI.gif
	//except with values 1-15
	for (int e = 0; e < (int)(sizeof(arrOfInts) / sizeof(arrOfInts[0])); e++) {
		assert(!(add(intsBSTR, arrOfInts[e], compare_numbers)));
	}
 
	printf("\n\ncontains(8) should return 1.\nReturned: %i", contains(intsBSTR, arrOfInts[7], compare_numbers));
	number *nineteen = create_int(19);
	printf("\n\ncontains(19) should return 0.\nReturned: %i", contains(intsBSTR, nineteen, compare_numbers));
	free_int(nineteen);
 
	printf("\n\nmin()/max() should return 1 and 15.\nReturned:\n");
	printf("min(): ");
	print_int(min(intsBSTR));
	printf("max(): ");
	print_int(max(intsBSTR));
 
	printf("\n\nShould print the numbers 1-15\n");
	traverse(intsBSTR, print_int);
 
	printf("\ndestroy() ints right-tree");
	destroy(intsBSTR, free_int);
	printf("\n***END OF RIGHT-SIDED TESTS**\n");
 
 
	//Left-heavy BST
	bstset *intsBSTL = create_bstset();
	number *arrOfInts2[15];
	for (int i = 0; i < 15; i++) {
		arrOfInts2[i] = create_int(i + 1);
	}
	printf("\n\nCreate a left-sided tree.");
	printf("\nAdding 15-1 to the BST. Should return 0 for every element added. Test will halt if this isn't true.");
	//Will look like this: http://i.imgur.com/VToKoyI.gif (mirrored)
	//except with values 15-1 (15 should be the root)
	for (int e = 14; e >= 0; e--) {
		assert(!(add(intsBSTL, arrOfInts2[e], compare_numbers)));
	}
 
	printf("\n\ncontains(8) should return 1.\nReturned: %i", contains(intsBSTL, arrOfInts2[7], compare_numbers));
	number *twentyone = create_int(21);
	printf("\n\ncontains(21) should return 0.\nReturned: %i", contains(intsBSTL, twentyone, compare_numbers));
	free_int(twentyone);
 
	printf("\n\nmin()/max() should return 1 and 15.\nReturned:\n");
	printf("min(): ");
	print_int(min(intsBSTL));
	printf("max(): ");
	print_int(max(intsBSTL));
 
	printf("\n\nShould print the numbers 1-15\n");
	traverse(intsBSTL, print_int);
 
	printf("\ndestroy() ints left-tree.");
	destroy(intsBSTL, free_int);
	printf("\n***END OF LEFT-SIDED TESTS**\n\n\n");
}
 
 
//run these in addition to TA_cases for more exhaustive testing!
//written by: Nate G.
void additional_cases(void) {
	printf("\n\n\nadditional_cases");
	printf("\nCreate an empty BST.");
	bstset *emptyBST= create_bstset();
 
	printf("\n\nmin() and max() of empty BST should return NULL (nil).\nReturned:");
	printf("\nmin(): %p", min(emptyBST));
	printf("\nmax(): %p", max(emptyBST));
 
	person *op = create_person("OP", 14);
	printf("\n\ncontains() of empty BST should return 0.\nReturned: %i", contains(emptyBST, op, person_name_comp));
	free_person(op);
 
	printf("\n\ntraversing an emptyBST should print nothing.\nReturned:\n");
	traverse(emptyBST, print_person);
 
	printf("\ndestroy() an emptyBST.");
	destroy(emptyBST, free_person);
	printf("\n***END OF TESTS REGARDING EMPTY SETS***");
 
 
	//Avengers
	printf("\n\n\n\nCreate Avengers BST.");
	bstset *avengersBST = create_bstset();
	person *tony = create_person("Tony", 53);
	person *steve = create_person("Steve", 97);
	person *bruce = create_person("Bruce", 45);
	person *natasha = create_person("Natasha", 30);
	person *thor = create_person("Thor", 1001);
	person *clint = create_person("Clint", 44);
	person *nick = create_person("Fury", 63);
	person *wanda = create_person("Wanda", 21);
	person *sam = create_person("Sam", 37);
	person *james = create_person("James", 46);
 
	//Add all of the Avengers to the BST
	add(avengersBST, tony, person_age_comp);
	add(avengersBST, steve, person_age_comp);
	add(avengersBST, bruce, person_age_comp);
	add(avengersBST, natasha, person_age_comp);
	add(avengersBST, thor, person_age_comp);
	add(avengersBST, clint, person_age_comp);
	add(avengersBST, nick, person_age_comp);
	add(avengersBST, wanda, person_age_comp);
	add(avengersBST, sam, person_age_comp);
	add(avengersBST, james, person_age_comp);
 
 
	printf("\n\nAvengers should have size 10.\nReturned size: %i\n", avengersBST -> size);
 
	person *ironman = create_person("Tony", 53);
	printf("\nAdding a duplicate of Tony should return 1.\nReturned: %i", add(avengersBST, ironman, person_age_comp));
	free_person(ironman);
 
	printf("\n\nFinding min and max of a BST with multiple values in BST:");
	printf("\nMin should be Wanda, age 21.\nmin() returned: ");
	print_person(min(avengersBST));
	printf("\nMax should be Thor, age 1001.\nmax() returned: ");
	print_person(max(avengersBST));
 
	printf("\n\ncontains(sam) should return 1.\nReturned: %i", contains(avengersBST, sam, person_age_comp));
	printf("\n\ncontains(tony) should return 1.\nReturned: %i", contains(avengersBST, tony, person_age_comp));
	person *ultron = create_person("Ultron", 1);
	printf("\n\ncontains(ultron) should return 0.\nReturned: %i", contains(avengersBST, ultron, person_age_comp));
	free_person(ultron);
 
	printf("\n\nShould be the Avengers sorted by age.\n");
	traverse(avengersBST, print_person);
	printf("\n");
 
 
	printf("destroy() Avengers tree.");
	destroy(avengersBST, free_person);
 
	printf("\n***END OF AVENGERS TESTING***\n\n\n");
}
 
 
//stock, base cases (non-exhaustive) that came with the assignment
void TA_cases(void) {
	printf("\nTA_cases");
	printf("\nTEST CASE 1\nAn empty bst should have size 0:\n");
	bstset *bst1 = create_bstset();
	printf("Size: %d\n", bst1->size);
 
	printf("\nTEST CASE 2\nAfter adding one element, size should be 1:\n");
	add(bst1, create_person("Andrew", 25), person_name_comp);
	printf("Size: %d\n", bst1->size);
 
	printf("\nTEST CASE 3\nTraversal should print the one element:\n");
	traverse(bst1, print_person);
 
	printf("\nTEST CASE 4\nThe one element should be the min:\n");
	print_person(min(bst1));
 
	printf("\nTEST CASE 5\nThe one element should be the max:\n");
	print_person(max(bst1));
 
	printf("\nTEST CASE 6\nAndrew should be contained in the bst:\n");
	person *andrew = create_person("Andrew", 25);
	printf("%s in bst\n", contains(bst1, andrew, person_name_comp) ? "is" : "isn\'t");
 
	printf("\nTEST CASE 7\nCollin should not be contained in the bst:\n");
	person *collin = create_person("Collin", 23);
	printf("%s in bst\n", contains(bst1, collin, person_name_comp) ? "is" : "isn\'t");
 
	// Free these people because we are done with them
	free_person(andrew);
	free_person(collin);
 
	printf("\nTEST CASE 8\nThere should be 7 elements in this bst:\n");
    /*      _N_
	 *     /   \
     *    H     B
	 *   / \   / \
	 *  Y   M A   L
	 */
	bstset *bst2 = create_bstset();
	int result[7];
	result[0] = add(bst2, create_person("Nick", 23), person_age_comp);
	result[1] = add(bst2, create_person("Henry", 21), person_age_comp);
	result[2] = add(bst2, create_person("Marie", 22), person_age_comp);
	result[3] = add(bst2, create_person("Yuanhan", 19), person_age_comp);
	result[4] = add(bst2, create_person("Brandon", 28), person_age_comp);
	result[5] = add(bst2, create_person("Andrew", 25), person_age_comp);
	result[6] = add(bst2, create_person("Leahy", 66), person_age_comp);
	printf("Size: %d\n", bst2->size);
 
	printf("\nTEST CASE 9\nadd should return 0 for all the added new elements:\n");
	printf("Assert will fail if add returned a nonzero value...\n");
	for(int i = 0; i < 7; ++i) {
		assert(!result[i]);
	}
	printf("Passed test!\n");
 
	printf("\nTEST CASE 10\nThe minimum element should be Yuanhan:\n");
	print_person(min(bst2));
 
	printf("\nTEST CASE 11\nThe maximum element should be Leahy:\n");
	print_person(max(bst2));
 
	//I didn't count for the comparisons in my other tests; chances are if you pass this, you pass it all; but don't hold me to it. -Nate
	printf("\nTEST CASE 12\nBrandon should be in the bst (2 comparisons):\n");
	person *brandon = create_person("Brandon", 28);
	comparisons = 0;
	printf("%s in bst\n", contains(bst2, brandon, person_age_comp) ? "is" : "isn\'t");
	printf("Comparisons: %d\n", comparisons);
 
	printf("\nTEST CASE 13\nBao should not be in the bst (3 comparisons):\n");
	person *bao = create_person("Bao", 20);
	comparisons = 0;
	printf("%s in bst\n", contains(bst2, bao, person_age_comp) ? "is" : "isn\'t");
	printf("Comparisons: %d\n", comparisons);
 
	printf("\nTEST CASE 14\nThe names should be printed in ascending age:\n");
	traverse(bst2, print_person);
 
	printf("\nTEST CASE 15\nAdding an existing element should return 1:\n");
	printf("Return value: %d\n", add(bst2, brandon, person_age_comp));
 
	printf("\nTEST CASE 16\nThe bst should still be size 7:\n");
	printf("Size: %d\n", bst2->size);
 
	// Done with these 2 people now
	free_person(brandon);
	free_person(bao);
 
	printf("\nTEST CASE 17\nThe same 7 people now sorted by name:\n");
    /*        N
	 *       / \
     *      H   Y
	 *     / \
	 *    B   M
	 *   /   /
	 *  A   L
	 */
	bstset *bst3 = create_bstset();
	add(bst3, create_person("Brandon", 28), person_name_comp);
	add(bst3, create_person("Nick", 23), person_name_comp);
	add(bst3, create_person("Henry", 21), person_name_comp);
	add(bst3, create_person("Marie", 22), person_name_comp);
	add(bst3, create_person("Yuanhan", 19), person_name_comp);
	add(bst3, create_person("Andrew", 25), person_name_comp);
	add(bst3, create_person("Leahy", 66), person_name_comp);
	traverse(bst3, print_person);
	printf("\n");
 
	//DESTROY ALL HUMANS
	destroy(bst1, free_person);
	destroy(bst2, free_person);
	destroy(bst3, free_person);
}
 
 
 
 
// Create a new person
person *create_person(const char *name, int age) {
	person *p = (person*) malloc(sizeof(person));
	p->name = (char*) malloc(strlen(name) + 1);
	strcpy(p->name, name);
	p->age = age;
	return p;
}
 
// Print a person
void print_person(void *data) {
	person *p = (person*) data;
	printf("%s, %d\n", p->name, p->age);
}
 
// Free a person
void free_person(void *data) {
	// This is safe because we should only be passing in person struct pointers
	person *p = (person*) data;
	// free any malloc'd pointers contained in the person struct (just name)
	free(p->name);
	// Now free the struct itself; this takes care of non-malloc'd data, like age.
	free(p);
}
 
// Compare people by age
int person_age_comp(const void *data1, const void *data2) {
	person *p1 = (person*) data1;
	person *p2 = (person*) data2;
	++comparisons;
	return p1->age - p2->age;
}
 
// Compare people by name
int person_name_comp(const void *data1, const void *data2) {
	person *p1 = (person*) data1;
	person *p2 = (person*) data2;
	++comparisons;
	return strcmp(p1->name, p2->name);
}
 
 
//create an integer using our struct
number *create_int(const int num) {
	number *integer = (number*) malloc(sizeof(number));
	integer -> value = num;
	return integer;
}
 
//compares the values of the ints
int compare_numbers(const void *data1, const void *data2) {
	number *n1 = (number*) data1;
	number *n2 = (number*) data2;
	return ((n1 -> value) - (n2 -> value));
}
 
//free the integer
void free_int(void *data) {
	number *integer = (number*) data;
	free(integer);
}
 
//print the number
void print_int(void *data) {
	number *n = (number*) data;
	printf("%i\n", n -> value);
}
