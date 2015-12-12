typedef struct
{
    int x;
    char* y;
} something;


//Examine this function that copies this structure into the dest parameter


void copy_struct(const something* src, something* dest)
{
    *dest = *src;
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
    printf("a.x = %d, a.y = %s, b.x = %d, b.y = %s\n", a.x, a.y, b.x, b.y);
    a.x = 27;
    a.y[0] = 'J';
    printf("a.x = %d, a.y = %s, b.x = %d, b.y = %s\n", a.x, a.y, b.x, b.y);

    free(a.y);
}