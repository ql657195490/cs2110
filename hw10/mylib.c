#include "mylib.h"
#include "stdbool.h"

u16 *videoBuffer = (u16 *) 0x6000000;

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
void waitForVblank() {
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}

bool checkCollision(int selfrow, int selfcol, int otherrow, int othercol, int selfw, int selfh) {
	return ((selfcol >= (othercol - selfw) && selfcol <= (othercol + selfcol))
 			&& (selfrow >= (otherrow - selfh) && selfrow <= (otherrow + selfh)));
}

void setPixel4(int row, int col, u8 index) {
	int whichPixel = OFFSET(row, col, 240);
	int whichShort = whichPixel / 2;
	unsigned short theShort = videoBuffer[whichShort];
	if (col & 1) {
		//col is odd so insert index into the left byte
		theShort = (theShort & 0x00FF) | (index << 8);
	} else {
		theShort = (theShort & 0xFF00) | (index);
	}
	videoBuffer[whichShort] = theShort;
}

void flipPage() {
	if (REG_DISPCNT & BUFFER1FLAG) {
		//were display BUFFER1 and videoBuffer was BUFFER0
		REG_DISPCNT = (REG_DISPCNT & (~BUFFER1FLAG));
		videoBuffer = BUFFER1;
	} else {
		REG_DISPCNT = REG_DISPCNT | BUFFER1FLAG;
		videoBuffer = BUFFER0;
	}
}

void fillScreen4(u8 index) {
	volatile u16 color = (index << 8) | index;
	DMA[3].src = &color;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = 19200 | DMA_ON | DMA_SOURCE_FIXED;
}

void drawImage4(int r, int c, int width, int height, const u16* image) {
	for (int i = 0; i < height; i++) {
		DMA[3].src = &image[OFFSET(i, 0, width / 2)];
		DMA[3].dst = videoBuffer + OFFSET(r + i, c, 240)/2;
		DMA[3].cnt = (width / 2) | DMA_ON;
	}
}

void drawImage4Flip(int r, int c, int width, int height, const u16* image) {
	for (int i = 0; i < height; i++) {
		DMA[3].src = &image[OFFSET(i, width/2, width / 2)];
		DMA[3].dst = videoBuffer + OFFSET(r+i, c, 240)/2;
		DMA[3].cnt = (width / 2) | DMA_ON | DMA_SOURCE_DECREMENT;
	}
}

void drawRect4(int r, int c, int width, int height, u8 index) {
	volatile u16 color = index | (index << 8);
	for (int i = 0; i < height; i++) {
		DMA[3].src = &color;
		DMA[3].dst = videoBuffer + OFFSET(r + i, c, 240) / 2;
		DMA[3].cnt = width / 2 | DMA_ON | DMA_SOURCE_FIXED;
	}
}
