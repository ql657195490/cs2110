typedef unsigned short u16;
typedef unsigned int u32;

#define REG_DISPCNT *(u16*) 0x4000000
#define RGB(r, g, b) ((r) | (g << 5) | (b << 10))
#define MODE_3 3
#define BG2_EN (1 << 10)
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