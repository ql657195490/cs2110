/*
 * Exported with nin10kit v1.1
 * Invocation command was nin10kit -mode=4 images gamestart.png gameover.png win.png 
 * Time-stamp: Wednesday 11/04/2015, 14:21:31
 * 
 * Image Information
 * -----------------
 * gamestart.png 240@160
 * gameover.png 240@160
 * win.png 240@160
 * 
 * Quote/Fortune of the Day!
 * -------------------------
 * 
 * All bug reports / feature requests are to be sent to Brandon (bwhitehead0308@gmail.com)
 */

#ifndef IMAGES_H
#define IMAGES_H

extern const unsigned short images_palette[28];
#define IMAGES_PALETTE_SIZE 28

extern const unsigned short gamestart[19200];
#define GAMESTART_SIZE 19200
#define GAMESTART_WIDTH 240
#define GAMESTART_HEIGHT 160

extern const unsigned short gameover[19200];
#define GAMEOVER_SIZE 19200
#define GAMEOVER_WIDTH 240
#define GAMEOVER_HEIGHT 160

extern const unsigned short win[19200];
#define WIN_SIZE 19200
#define WIN_WIDTH 240
#define WIN_HEIGHT 160

#endif

