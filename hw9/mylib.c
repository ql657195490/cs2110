#include "mylib.h"

u16 *videoBuffer=(u16 *) 0x6000000;

void setPixel(int x, int y, u16 color);
void drawRect(int x, int y, int width, int height, u16 color);
void drawHollowRect(int x, int y, int width, int height, u16 color);
void drawImage3(int x, int y, int width, int height, const u16* image);



void setPixel(int x, int y, u16 color) {
	videoBuffer[OFFSET(x, y, 240)] = color;
}

void drawRect(int r, int c, int width, int height, u16 color)
{
	// int i, j;
	// for(i = 0; i < height; i++) {
	// 	for(j = 0; j < width; j++) {
	// 		setPixel(r+i, c+j, color);
	// 	}
	// }
	for (int x = 0; x < height; x++) {
		DMA[3].src = &color;
		DMA[3].dst = &videoBuffer[OFFSET(r + x, c, 240)];
		DMA[3].cnt = (width) | DMA_SOURCE_FIXED | DMA_ON;
	}
}
void drawHollowRect(int r, int c, int width, int height, u16 color) {
	int i, j;
	for (i = 0; i < height; i++) {
		setPixel(r + i, c, color);
		setPixel(r + i, c + width - 1, color);
	}
	for (j = 0; j < width; j++) {
		setPixel(r, c + j, color);
		setPixel(r + height - 1, c + j, color);
	}
}
void drawImage3(int r, int c, int width, int height, const u16* image) {
	for (int x = 0; x < height; x++) {
		DMA[3].src = &image[OFFSET(x, 0, width)];
		DMA[3].dst = &videoBuffer[OFFSET(r + x, c, 240)];
		DMA[3].cnt = (width) | DMA_ON;
	}
}