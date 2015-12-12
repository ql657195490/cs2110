#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef struct
{
    int x;
    char* y;
} something;


//Examine this function that copies this structure into the dest parameter


void copy_struct(const something* src, something* dest)
{
    dest->x = src->x;
    dest->y = strdup(src->y);

    // dest->y = malloc(sizeof(src->y));
    // int i = 0;
    // while ((src->y)[i] != NULL) {
    //     dest->y[i] = src->y[i];
    // }

    //char *d = malloc (strlen (s) + 1);   // Space for length plus nul
    // if (d == NULL) return NULL;          // No memory
    // strcpy (d,s);                        // Copy the characters
    // return d;
}

void main(void)
{
    something a, b;
    a.x = 32;
    a.y = malloc(sizeof(char) * 6);
    a.y[0] = 'H';
    a.y[1] = 'E';
    a.y[2] = 'L';
    a.y[3] = 'L';
    a.y[4] = 'O';
    a.y[5] = '\0';

    copy_struct(&a, &b);
    printf("%d \n", (int)sizeof(a));
    printf("a.x = %d, a.y = %s, b.x = %d, b.y = %s\n", a.x, a.y, b.x, b.y);
    a.x = 27;
    a.y[0] = 'J';
    printf("a.x = %d, a.y = %s, b.x = %d, b.y = %s\n", a.x, a.y, b.x, b.y);

    free(a.y);
}
