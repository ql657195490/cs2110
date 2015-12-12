/*
 * Exported with nin10kit v1.1
 * Invocation command was nin10kit -mode=4 gif5 finn.gif 
 * Time-stamp: Thursday 11/05/2015, 15:47:03
 * 
 * Image Information
 * -----------------
 * finn.gif (frame 0) 480@504
 * finn.gif (frame 1) 480@504
 * finn.gif (frame 2) 480@504
 * 
 * Quote/Fortune of the Day!
 * -------------------------
 * 
 * All bug reports / feature requests are to be sent to Brandon (bwhitehead0308@gmail.com)
 */

#ifndef GIF5_H
#define GIF5_H

extern const unsigned short gif5_palette[21];
#define GIF5_PALETTE_SIZE 21

extern const unsigned short finn0[120960];

extern const unsigned short finn1[120960];

extern const unsigned short finn2[120960];

extern const unsigned short* finn_frames[3];
#define FINN_FRAMES 3
#define FINN_SIZE 120960
#define FINN_WIDTH 480
#define FINN_HEIGHT 504

#endif

