#include <stdlib.h>
#include "kitty.h"

#define REG_DISPCTL *(unsigned short *)0x4000000
#define BG2_ENABLE (1<<10)
#define MODE3 3
#define SCANLINECOUNTER *(volatile unsigned short *)0x4000006
#define OFFSET(r, c, rowlen) ((r)*(rowlen) + (c))

typedef unsigned short u16;
u16 *videoBuffer = (u16 *)0x6000000;


/* This struct contains the width, height and the data array of an image. */
typedef struct image {
    int width;
    int height;
    const u16 *data_arr;
} image;


/* Function prototypes */
void waitForVblank();
void flipHorizontally(int row, int col, image *img);
void flipVertically(int row, int col, image *img);


void flipHorizontally(int row, int col, image *img) {
    image im = *img;
    int w = im.width;
    int h = im.height;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int temp = w - j;
            videoBuffer[OFFSET(row+i,col+temp,240)] = im.data_arr[OFFSET(i,j,w)];
        }
    }
}


 void flipVertically(int row, int col, image *img) {
    image im = *img;
    int w = im.width;
    int h = im.height;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int temp = h - i;
            videoBuffer[OFFSET(row+temp,col+j,240)] = im.data_arr[OFFSET(i,j,w)];
        }
    }
 }


int main(void)
{
    REG_DISPCTL = MODE3 | BG2_ENABLE;

    int row = 10;
    int col = 40;

    image img;
    img.width = KITTY_WIDTH;
    img.height = KITTY_HEIGHT;
    img.data_arr = kitty;
    
    waitForVblank();

   flipHorizontally(row, col, &img);
//   flipVertically(row, col, &img);

    while (1);
}


void waitForVblank()
{
    while(SCANLINECOUNTER > 160);
    while(SCANLINECOUNTER < 160);
}
