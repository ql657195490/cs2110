#include "stdlib.h"
#include "stdio.h"
typedef struct
{
	char a;
	char b;
} struct1;

typedef struct
{
	short p;
	char a;
	int b;
} struct2;


void main(void) {
	struct1 s1;
	struct2 s2;

	printf("size of char: %d\nsize of short: %d\nsize of int: %d\nsize of long: %d\nsize of char*: %d\nsize of int*: %d\nsize of void*: %d\nsize of int**: %d\nsize of struct1: %d\nsize of struct2: %d\n"
			, (int)sizeof(char), (int)sizeof(short), (int)sizeof(int), (int)sizeof(long), (int)sizeof(char*)
			, (int)sizeof(int*), (int)sizeof(void*), (int)(sizeof(int**)), (int)(sizeof(s1)), (int)(sizeof(s2)));
}