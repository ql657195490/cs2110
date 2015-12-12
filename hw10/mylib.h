#include "stdbool.h"


typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u16 *videoBuffer;

#define REG_DISPCNT *(u16*) 0x4000000
#define RGB(r, g, b) ((r) | (g << 5) | (b << 10))
#define MODE_3 3
#define MODE_4 4
#define BG2_EN (1 << 10)
#define BUFFER0 (unsigned short *) 0x6000000
#define BUFFER1 (unsigned short *) 0x600A000
#define PALLETE ((unsigned short *) 0x5000000) //without dereferencing
#define BUFFER1FLAG (1<<4)


#define BUTTON_A		(1<<0)
#define BUTTON_B		(1<<1)
#define BUTTON_SELECT	(1<<2)
#define BUTTON_START	(1<<3)
#define BUTTON_RIGHT	(1<<4)
#define BUTTON_LEFT		(1<<5)
#define BUTTON_UP		(1<<6)
#define BUTTON_DOWN		(1<<7)
#define BUTTON_R		(1<<8)
#define BUTTON_L		(1<<9)

#define BUTTONS (*(u16*)0x4000130)

#define KEY_DOWN_NOW(key)  (~(BUTTONS) & key)

#define SCANLINECOUNTER *(volatile unsigned short *) 0x4000006

#define BLACK RGB(0, 0, 0)
#define CYAN RGB(0, 31, 31)
#define GREEN RGB(0, 31, 0)
#define RED RGB(31, 0, 0)
#define MAGENTA RGB(31, 0, 31)
#define WHITE RGB(31, 31, 31)

typedef struct {
	const volatile void *src;
	volatile void *dst;
	volatile u32 cnt;
} DMAREC;
#define DMA_CHANNEL_3 3
#define DMA ((volatile DMAREC *)0x040000B0)
#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)
#define DMA_DESTINATION_RESET (3 << 21)

#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)
#define DMA_ON (1 << 31)

#define OFFSET(r,c,rowlen) ((r)*(rowlen)+(c))

void setPixel(int x, int y, u16 color);
void drawRect(int x, int y, int width, int height, u16 color);
void drawHollowRect(int x, int y, int width, int height, u16 color);
void drawImage3(int x, int y, int width, int height, const u16* image);
void waitForVblank();
bool checkCollision(int sr, int sc, int tr, int tc, int w, int h);
void drawImage4(int r, int c, int w, int h, const u16* image);
void drawImage4Flip(int r, int c, int w, int h, const u16* image);
void drawRect4(int r, int , int w, int h, u8 index);
void fillScreen4(u8 index);
void setPixel4(int row, int col, u8 index);
void flipPage();


