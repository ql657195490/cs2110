/* sort.c
 * CS 2110 Fall 2015 Lab 23
 * Name: HONGRUI ZHENG
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	const char *name;
	int age;
} Person;

int compage(const void *a, const void *b);
int compstr(const void *a, const void *b);

#define NUMPEOPLE 10
Person people[NUMPEOPLE] = {
	{"Jonathan", 32},
	{"Amelia"  , 51},
	{"Marcus"  , 22},
	{"Ashley"  , 25},
	{"Xavier"  , 37},
	{"Ellen"   , 73},
	{"Ricardo" , 26},
	{"Tanaka"  , 40},
	{"Mitchell", 68},
	{"Roy"     , 19}
};

// TODO write any additional functions you may need here
int compage(const void *a, const void *b) {
	const Person *p1 = (const Person*) a;
	const Person *p2 = (const Person*) b;
	return p1->age - p2->age;
}
int compstr(const void *a, const void *b) {
	const Person *p1 = (const Person*) a;
	const Person *p2 = (const Person*) b;
	return strcmp(p1->name, p2->name);
}



int main(void) {

	// TODO Use qsort to sort people by age
	qsort(people, NUMPEOPLE, sizeof(Person), compage);


	// Print people sorted by age
	printf("---[Age sort]------------\n");
	for(int i = 0; i < NUMPEOPLE; ++i) {
		printf("\t%-10s %-2d\n", people[i].name, people[i].age);
	}

	qsort(people, NUMPEOPLE, sizeof(Person), compstr);
	// TODO Use qsort to sort people by name



	// Print people sorted by name
	printf("---[Name sort]-----------\n");

	for(int i = 0; i < NUMPEOPLE; ++i) {
		printf("\t%-10s %-2d\n", people[i].name, people[i].age);
	}

	return 0;
}

