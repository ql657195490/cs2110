// CS 2110, Fall 2015
// Lab 19
// clearscreen.c

typedef unsigned short u16;
typedef unsigned int u32;
typedef struct {
	const volatile void *src;
	volatile void *dst;
	volatile u32 cnt;
} DMA_CONTROLLER;

#define DMA ((volatile DMA_CONTROLLER*) 0x40000B0)
#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1
#define DMA_CHANNEL_2 2
#define DMA_CHANNEL_3 3

#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)
#define DMA_DESTINATION_RESET (3 << 21)

#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

#define DMA_REPEAT (1 << 25)

#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)

#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)

#define DMA_IRQ (1 << 30)
#define DMA_ON (1 << 31)

#define COLOR(R, G, B) ((R) | (G) << 5 | (B) << 10)
#define RED COLOR(31, 0, 0)

extern unsigned short *videoBuffer;

// Clear the screen with DMA
void clearscreen() {
	volatile u16 color = RED;
	DMA[3].src = &color;
	DMA[3].dst = &videoBuffer[0];
	DMA[3].cnt = 38400 | DMA_SOURCE_FIXED | DMA_ON;
}

