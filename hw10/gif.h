/*
 * Exported with nin10kit v1.1
 * Invocation command was nin10kit -mode=4 gif adv.gif 
 * Time-stamp: Wednesday 11/04/2015, 14:31:32
 * 
 * Image Information
 * -----------------
 * adv.gif (frame 0) 208@200
 * adv.gif (frame 1) 208@200
 * adv.gif (frame 2) 208@200
 * adv.gif (frame 3) 208@200
 * adv.gif (frame 4) 208@200
 * 
 * Quote/Fortune of the Day!
 * -------------------------
 * 
 * All bug reports / feature requests are to be sent to Brandon (bwhitehead0308@gmail.com)
 */

#ifndef GIF_H
#define GIF_H

extern const unsigned short gif_palette[256];
#define GIF_PALETTE_SIZE 256

extern const unsigned short adv0[20800];

extern const unsigned short adv1[20800];

extern const unsigned short adv2[20800];

extern const unsigned short adv3[20800];

extern const unsigned short adv4[20800];

extern const unsigned short* adv_frames[5];
#define ADV_FRAMES 5
#define ADV_SIZE 20800
#define ADV_WIDTH 208
#define ADV_HEIGHT 200

#endif

