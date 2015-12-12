/*
 * Exported with nin10kit v1.1
 * Invocation command was nin10kit -mode=4 gif2 adv3.gif 
 * Time-stamp: Thursday 11/05/2015, 14:01:28
 * 
 * Image Information
 * -----------------
 * adv3.gif (frame 0) 92@121
 * adv3.gif (frame 1) 90@124
 * adv3.gif (frame 2) 90@124
 * 
 * Quote/Fortune of the Day!
 * -------------------------
 * 
 * All bug reports / feature requests are to be sent to Brandon (bwhitehead0308@gmail.com)
 */

#ifndef GIF2_H
#define GIF2_H

extern const unsigned short gif2_palette[255];
#define GIF2_PALETTE_SIZE 255

extern const unsigned short adv30[5566];

extern const unsigned short adv31[5580];

extern const unsigned short adv32[5580];

extern const unsigned short* adv3_frames[3];
#define ADV3_FRAMES 3
#define ADV3_SIZE 5566
#define ADV3_WIDTH 92
#define ADV3_HEIGHT 121

#endif

