
#include "start.h"
#include "gameover.h"
#include "win.h"
#include "lvl1.h"
#include "lvl2.h"
#include "stdbool.h"
#include "mylib.h"



//u16 *videoBuffer=(u16 *) 0x6000000;
void setPixel(int x, int y, u16 color);
void drawRect(int x, int y, int width, int height, u16 color);
void drawHollowRect(int x, int y, int width, int height, u16 color);
void drawImage3(int x, int y, int width, int height, const u16* image);
void waitForVblank();
bool checkCollision(int selfrow, int selfcol, int otherrow, int othercol, int size);

void waitForVblank() {
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}

bool checkCollision(int selfrow, int selfcol, int otherrow, int othercol, int size) {
	return ((selfcol >= (othercol - size) && selfcol <= (othercol + size))
 			&& (selfrow >= (otherrow - size) && selfrow <= (otherrow + size)));
}

int main(void) {
	REG_DISPCNT = MODE_3 | BG2_EN;
	while (1) {
		drawImage3(0, 0, START_WIDTH, START_HEIGHT, start);
		while (!KEY_DOWN_NOW(BUTTON_START));
		//while (KEY_DOWN_NOW(BUTTON_START));

	//level 1
		struct square
		{
			int row;
			int col;
			int size;
		};
		struct square self;
		self.row = 160; self.col = 120; self.size = 5;
		int row1 = 50; int col1 = 75;
		int row2 = 110; int col2 = 155;
		int oldrow = self.row; int oldcol = self.col;
		int oldrow1 = row1; int oldcol1 = col2;
		int oldrow2 = row2; int oldcol2 = col2;
		//int rdel1 = 1;
		int cdel1 = 3;
		int cdel2 = 3;
		//int rdel2 = 1;
		//int cdel2 = 1;
		int size = 5;
		int oldsize = size;
		bool gameend = 0;
		bool reset = 0;
		
		//drawImage3(0, 0, LVL1_WIDTH, LVL1_HEIGHT, lvl1);
		drawRect(0, 0, 240, 160, BLACK);
		drawRect(0, 120, 5, 5, RED);
		drawImage3(0, 0, LVL1_WIDTH, LVL1_HEIGHT, lvl1);
		//drawRect(0, 0, 80, 160, MAGENTA);
		drawRect(0, 160, 80, 160, MAGENTA);
		while (1) {
			if (KEY_DOWN_NOW(BUTTON_SELECT)) {
				reset = 1;
				break;
			}
			//int clr = CYAN;
			if (KEY_DOWN_NOW(BUTTON_UP)) {
				self.row--;
			}
			if (KEY_DOWN_NOW(BUTTON_DOWN)) {
				self.row++;
			}
			if (KEY_DOWN_NOW(BUTTON_LEFT)) {
				self.col--;
			}
			if (KEY_DOWN_NOW(BUTTON_RIGHT)) {
				self.col++;
			}
			if (self.row < 0) {
				self.row = 0;
			}
			if (self.row > 159 - size + 1) {
				self.row = 159 - size + 1;
			}
			if (self.col < 80) {
				self.col = 80;
			}
			if (self.col > 159 - size + 1) {
				self.col = 159 - size + 1;
			}

			if (checkCollision(self.row, self.col, 0, 120, self.size)) {
				break;
			}
			if (checkCollision(self.row, self.col, row1, col1, size)) {
				drawImage3(0, 0, GAMEOVER_WIDTH, GAMEOVER_HEIGHT, gameover);
				while(!KEY_DOWN_NOW(BUTTON_SELECT));
				//while(KEY_DOWN_NOW(BUTTON_START) & KEY_DOWN_NOW(BUTTON_SELECT));
				gameend = 1;
				break;
				
			}
			if (checkCollision(self.row, self.col, row2, col2, size)) {
				drawImage3(0, 0, GAMEOVER_WIDTH, GAMEOVER_HEIGHT, gameover);
				while(!KEY_DOWN_NOW(BUTTON_SELECT));
				//while(KEY_DOWN_NOW(BUTTON_START) & KEY_DOWN_NOW(BUTTON_SELECT));
				gameend = 1;
				break;
			}
			// if (checkCollision(row, col, row13, col34, size)) {
			// 	drawImage3(0, 0, GAMEOVER_WIDTH, GAMEOVER_HEIGHT, gameover);
			// 	while(1) {
			// 	}
			// }
			// if (checkCollision(row, col, row24, col34, size)) {
			// 	drawImage3(0, 0, GAMEOVER_WIDTH, GAMEOVER_HEIGHT, gameover);
			// 	while(1) {
			// 	}
			// }


			//row13 += rdel1;
			col1 += cdel1;
			col2 += cdel2;
			//row24 += rdel2;
			//col34 += cdel2;
			// if(row13<0)
			// {
			// 	row13 = 0;
			// 	rdel1 = -rdel1;
			// }
			// if(row13>159-size+1)
			// {
			// 	row13 = 159-size+1;
			// 	rdel1 = -rdel1;
			// }
			if(col1 < 80)
			{
				col1 = 80;
				cdel1 = -cdel1;
			}
			if(col1 > 159-size+1)
			{
				col1 = 159-size+1;
				cdel1 = -cdel1;
			}
			if(col2 < 80)
			{
				col2 = 80;
				cdel2 = -cdel2;
			}
			if(col2 > 159-size+1)
			{
				col2 = 159-size+1;
				cdel2 = -cdel2;
			}

			waitForVblank();
			drawRect(oldrow, oldcol, oldsize, oldsize, BLACK);
			drawRect(self.row, self.col, self.size, self.size, CYAN);
			drawRect(oldrow1, oldcol1, oldsize, oldsize, BLACK);
			drawRect(row1, col1, size, size, GREEN);
			drawRect(oldrow2, oldcol2, oldsize, oldsize, BLACK);
			drawRect(row2, col2, size, size, GREEN);


			oldrow = self.row;
			oldcol = self.col;
			oldrow1 = row1;
			oldcol1 = col1;
			oldrow2 = row2;
			oldcol2 = col2;
			oldsize = size;


		}
	//go back to start of game if gameover and key pressed
		if (gameend || reset) {
			continue;
		}

	//level 2

		int rowlvl2 = 160; int collvl2 = 120;
		int row1lvl2 = 50; int col1lvl2 = 0;
		int row2lvl2 = 110; int col2lvl2 = 240;
		int food1row = 110; int food1col = 50;
		int food2row = 50; int food2col = 180;
		int food3row = 50; int food3col = 50;
		int food4row = 110; int food4col = 180;

		int oldrowlvl2 = rowlvl2; int oldcollvl2 = collvl2;
		int oldrow1lvl2 = row1lvl2; int oldcol1lvl2 = col2lvl2;
		int oldrow2lvl2 = row2lvl2; int oldcol2lvl2 = col2lvl2;
		//int rdel1 = 1;
		int cdel1lvl2 = 3;
		int cdel2lvl2 = 3;
		//int rdel2 = 1;
		//int cdel2 = 1;

		int collected = 0;

		drawRect(0, 0, 240, 160, BLACK);
		
		drawRect(120, 0, 80, 40, MAGENTA);
		drawRect(120, 160, 80, 40, MAGENTA);
		drawRect(60, 0, 80, 45, MAGENTA);
		drawRect(60, 160, 80, 45, MAGENTA);
		drawImage3(0, 0, LVL2_WIDTH, LVL2_HEIGHT, lvl2);
		//drawRect(0, 0, 80, 45, MAGENTA);
		drawRect(0, 160, 80, 45, MAGENTA);

		while (1) {
			if (KEY_DOWN_NOW(BUTTON_SELECT)) {
				reset = 1;
				break;
			}
			int clr = CYAN;
			if (KEY_DOWN_NOW(BUTTON_UP)) {
				rowlvl2--;
			}
			if (KEY_DOWN_NOW(BUTTON_DOWN)) {
				rowlvl2++;
			}
			if (KEY_DOWN_NOW(BUTTON_LEFT)) {
				collvl2--;
			}
			if (KEY_DOWN_NOW(BUTTON_RIGHT)) {
				collvl2++;
			}
			//outer perimeter
			if (collvl2 < 0) {
				collvl2 = 0;
			}
			if (rowlvl2 < 0) {
				rowlvl2 = 0;
			}
			if (rowlvl2 > 159 - size + 1) {
				rowlvl2 = 159 - size + 1;
			}
			if (collvl2 > 239 - size + 1) {
				collvl2 = 239 - size + 1;
			}

			//map restrictions (lower)
			if (collvl2 < 80 && rowlvl2 > 116) {
				collvl2 = 80;
			}
			if (collvl2 > 155 && rowlvl2 > 116) {
				collvl2 = 155;
			}
			if ((collvl2 < 80 || collvl2 > 155) && rowlvl2 > 115) {
				rowlvl2 = 115;
			}
			if ((collvl2 < 80 || collvl2 > 160) && rowlvl2 > 100 && rowlvl2 < 105) {
				rowlvl2 = 105;
			}
			if (collvl2 < 80 && rowlvl2 < 105 && rowlvl2 > 100) {
				collvl2 = 80;
			}
			if (collvl2 > 155 && rowlvl2 < 105 && rowlvl2 > 100) {
				collvl2 = 155;
			}

			//map restrictions (upper)
			if (collvl2 < 80 && rowlvl2 < 100 && rowlvl2 > 60) {
				collvl2 = 80;
			}
			if (collvl2 > 155 && rowlvl2 < 100 && rowlvl2 > 60) {
				collvl2 = 155;
			}
			if ((collvl2 < 80 || collvl2 > 155) && rowlvl2 < 100 && rowlvl2 > 55) {
				rowlvl2 = 55;
			}
			if ((collvl2 < 80 || collvl2 > 160) && rowlvl2 > 40 && rowlvl2 < 45) {
				rowlvl2 = 45;
			}
			if (collvl2 < 80 && rowlvl2 < 45) {
				collvl2 = 80;
			}
			if (collvl2 > 155 && rowlvl2 < 45) {
				collvl2 = 155;
			}

			

			if (checkCollision(rowlvl2, collvl2, 0, 120, size) && collected >= 2) {
				break;
			}
			if (checkCollision(rowlvl2, collvl2, row1lvl2, col1lvl2, size)) {
				drawImage3(0, 0, GAMEOVER_WIDTH, GAMEOVER_HEIGHT, gameover);
				while(!KEY_DOWN_NOW(BUTTON_SELECT));
				//while(KEY_DOWN_NOW(BUTTON_START) & KEY_DOWN_NOW(BUTTON_SELECT));
				gameend = 1;
				break;
			}
			if (checkCollision(rowlvl2, collvl2, row2lvl2, col2lvl2, size)) {
				drawImage3(0, 0, GAMEOVER_WIDTH, GAMEOVER_HEIGHT, gameover);
				while(!KEY_DOWN_NOW(BUTTON_SELECT));
				//while(KEY_DOWN_NOW(BUTTON_START) & KEY_DOWN_NOW(BUTTON_SELECT));
				gameend = 1;
				break;
			}
			if (checkCollision(rowlvl2, collvl2, food1row, food1col, size)) {
				drawRect(food1row, food1col, size, size, BLACK);
				collected++;
				food1row = 0;
				food1col = 0;
			}
			if (checkCollision(rowlvl2, collvl2, food2row, food2col, size)) {
				drawRect(food2row, food2col, size, size, BLACK);
				collected++;
				food2row = 0;
				food2col = 10;
			}
			if (checkCollision(rowlvl2, collvl2, food3row, food3col, size)) {
				drawRect(food3row, food3col, size, size, BLACK);
				collected++;
				food3row = 0;
				food3col = 20;
			}
			if (checkCollision(rowlvl2, collvl2, food4row, food4col, size)) {
				drawRect(food4row, food4col, size, size, BLACK);
				collected++;
				food4row = 0;
				food4col = 30;
			}
			// if (checkCollision(row, col, row13, col34, size)) {
			// 	drawImage3(0, 0, GAMEOVER_WIDTH, GAMEOVER_HEIGHT, gameover);
			// 	while(1) {
			// 	}
			// }
			// if (checkCollision(row, col, row24, col34, size)) {
			// 	drawImage3(0, 0, GAMEOVER_WIDTH, GAMEOVER_HEIGHT, gameover);
			// 	while(1) {
			// 	}
			// }


			//row13 += rdel1;
			col1lvl2 += cdel1lvl2;
			col2lvl2 += cdel2lvl2;
			//row24 += rdel2;
			//col34 += cdel2;
			// if(row13<0)
			// {
			// 	row13 = 0;
			// 	rdel1 = -rdel1;
			// }
			// if(row13>159-size+1)
			// {
			// 	row13 = 159-size+1;
			// 	rdel1 = -rdel1;
			// }
			if(col1lvl2 < 0)
			{
				col1lvl2 = 0;
				cdel1lvl2 = -cdel1lvl2;
			}
			if(col1lvl2 > 239-size+1)
			{
				col1lvl2 = 239-size+1;
				cdel1lvl2 = -cdel1lvl2;
			}
			if(col2lvl2 < 0)
			{
				col2lvl2 = 0;
				cdel2lvl2 = -cdel2lvl2;
			}
			if(col2lvl2 > 239-size+1)
			{
				col2lvl2 = 239-size+1;
				cdel2lvl2 = -cdel2lvl2;
			}

			waitForVblank();
			drawRect(oldrowlvl2, oldcollvl2, size, size, BLACK);
			drawRect(rowlvl2, collvl2, size, size, clr);
			drawRect(oldrow1lvl2, oldcol1lvl2, size, size, BLACK);
			drawRect(row1lvl2, col1lvl2, size, size, GREEN);
			drawRect(oldrow2lvl2, oldcol2lvl2, size, size, BLACK);
			drawRect(row2lvl2, col2lvl2, size, size, GREEN);
			drawRect(food1row, food1col, size, size, WHITE);
			drawRect(food2row, food2col, size, size, WHITE);
			drawRect(food3row, food3col, size, size, WHITE);
			drawRect(food4row, food4col, size, size, WHITE);
			drawRect(0, 120, 5, 5, RED);


			oldrowlvl2 = rowlvl2;
			oldcollvl2 = collvl2;
			oldrow1lvl2 = row1lvl2;
			oldcol1lvl2 = col1lvl2;
			oldrow2lvl2 = row2lvl2;
			oldcol2lvl2 = col2lvl2;
		}
		if (gameend || reset) {
			continue;
		}

		if (!reset) {
			drawImage3(0, 0, WIN_WIDTH, WIN_HEIGHT, win);
			while (!KEY_DOWN_NOW(BUTTON_START));
			while (KEY_DOWN_NOW(BUTTON_START));
		}

	}
} 