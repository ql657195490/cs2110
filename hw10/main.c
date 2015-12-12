// in mode 4:
// while (1) {
// 	read button
// 	change state
// 	erase whole screen
// 	draw state
// 	waitForVblank
// 	flipPage()
// }
#include "mylib.h"
#include "stdbool.h"
#include "images.h"
#include "finn3.h"
#include "text.h"


int main() {
	REG_DISPCNT = MODE_4 | BG2_EN;
	videoBuffer = BUFFER0;
	

	
	//game loop
	while(1) {

		//filling the palllete
		int startlength = sizeof(finn3_palette)/sizeof(finn3_palette[0]);
		for (int i = 0; i < startlength; i++) {
			PALLETE[i] = finn3_palette[i];
		}
		//flipPage();
		int titleFrame = 0;
		int titleCount = 0;


		while (!KEY_DOWN_NOW(BUTTON_START)) {
			titleFrame = (titleCount >> 3) % TITLE_FRAMES;
			drawImage4(0,0,TITLE_WIDTH,TITLE_HEIGHT, title_frames[titleFrame]);
			titleCount++;
			drawString(140, 90, "PRESS START!", WHITE);
			waitForVblank();
			flipPage();
		}

		//waitForVblank();
		//flipPage();


		
		int reset = 0;
		int gameover = 0;

		//variables for main character
		int frame = 0;
		int count = 0;
		int row = 160 - FINN3SMALLTRIM_HEIGHT;
		int col = 0;
		int right = 1;
		int animate = 0;
		int jumped = 0;
		int down = 0;
		int jumping = 0;
		int temprow = row;
		int jumpmax = 60;
		int lives = 3;

		//variables for goal
		int goalframe = 0;
		int goalcount = 0;
		int goalrow = 70;
		int goalcol = 210;



		//variables for enemies
		struct  enemy
		{
			int eframe;
			int ecount;
			int erow;
			int ecol;
			int ecoldel;
			int eliminated;
		};

		//enemy1
		struct enemy enemy1;
		enemy1.eframe = 0;
		enemy1.ecount = 0;
		enemy1.erow = 140 - GUNTERSMALL_HEIGHT;
		enemy1.ecol = 90;
		enemy1.ecoldel = 1;
		enemy1.eliminated = 0;

		//enemy2
		struct enemy enemy2;
		enemy2.eframe = 0;
		enemy2.ecount = 0;
		enemy2.erow = 100 - GUNTERSMALL_HEIGHT;
		enemy2.ecol = 160;
		enemy2.ecoldel = -1;
		enemy2.eliminated = 0;


		while (1) {
			if (KEY_DOWN_NOW(BUTTON_SELECT)) {
				reset = 1;
				break;
			}
			//moving horizontally
			if (KEY_DOWN_NOW(BUTTON_RIGHT)) {
				animate = 1;
				right = 1;
				col+=2;
			}
			if (KEY_DOWN_NOW(BUTTON_LEFT)) {
				animate = 1;
				right = 0;
				col-=2;
			}

			//jumping
			if (KEY_DOWN_NOW(BUTTON_UP) && !jumping) {
				jumped = 1;
				jumping = 1;
				temprow = row;
			}
			if (jumped) {
				row-=4;
				if (row<=(temprow - jumpmax)) {
					down = 1;
					jumped = 0;
				}
			}
			if (down) {
				row+=4;
				if (row >= temprow) {
					down = 0;
					jumping = 0;
				}
			}


			//boundary conditions
			if (col < -2) {
				col = -2;
			}
			if (col > (240 - FINN3SMALLTRIM_WIDTH)) {
				col = 240 - FINN3SMALLTRIM_WIDTH;
			}
			if (col > 60 - FINN3SMALLTRIM_WIDTH && col < 61 && row > 160 - GROUNDWGRASS_HEIGHT - FINN3SMALLTRIM_HEIGHT) {
				col = 60 - FINN3SMALLTRIM_WIDTH;
			}
			if (col > 60 - FINN3SMALLTRIM_WIDTH && row > 140) {
				row = 160 - GROUNDWGRASS_HEIGHT - FINN3SMALLTRIM_HEIGHT;
			}
			if (col < 60 - FINN3SMALLTRIM_WIDTH && row > 120 && !jumping) {
				row = 160 - FINN3SMALLTRIM_HEIGHT;
			}
			if (col > 140 - FINN3SMALLTRIM_WIDTH && col < 240 && row > 115 && row < 120) {
				row = 120;
				jumped = 0;
				down = 1;
			}
			if (col > 140 - FINN3SMALLTRIM_WIDTH && col < 141 && row < 120 && row > 100 - FINN3SMALLTRIM_HEIGHT) {
				col = 140 - FINN3SMALLTRIM_WIDTH;
			}
			if (col > 140 - FINN3SMALLTRIM_WIDTH && col < 240 && row < 100) {
				row = 100 - FINN3SMALLTRIM_HEIGHT;
			}
			// if (col > 140 - FINN3SMALLTRIM_WIDTH && col < 240 && row > 120) {
			// 	row = 100 - FINN3SMALLTRIM_HEIGHT;
			// }
			// if (col < 140 - FINN3SMALLTRIM_WIDTH && col > 60 - FINN3SMALLTRIM_WIDTH && row > 120 && !jumping) {
			// 	row = 140 - FINN3SMALLTRIM_HEIGHT;
			// }
			// if (col > 60 - FINN3SMALLTRIM_WIDTH && col < 140 - FINN3SMALLTRIM_WIDTH && row > 120) {
			// 	row = 140 - FINN3SMALLTRIM_HEIGHT;
			// }



			//enemy borders
			if (enemy1.ecol == 80) {
				enemy1.ecoldel = -enemy1.ecoldel;
			}
			if (enemy1.ecol == 220) {
				enemy1.ecoldel = -enemy1.ecoldel;
			}
			if (enemy2.ecol == 150) {
				enemy2.ecoldel = -enemy2.ecoldel;
			}
			if (enemy2.ecol == 220) {
				enemy2.ecoldel = -enemy2.ecoldel;
			}

			enemy1.ecol += enemy1.ecoldel;
			enemy2.ecol += enemy2.ecoldel;

			// if ((col > (60 - FINN3SMALLTRIM_WIDTH)) && row < (140 + FINN3SMALLTRIM_HEIGHT)) {
			// 	row = 140 + FINN3SMALLTRIM_HEIGHT;
			// }


			//object collisions
			if (checkCollision(row, col, enemy1.erow, enemy1.ecol, FINN3SMALLTRIM_WIDTH, FINN3SMALLTRIM_HEIGHT)) {
				lives--;
				row = 160 - FINN3SMALLTRIM_HEIGHT;
				col = 0;
				if (lives == 0) {
					drawImage4(0,0,LOSE_WIDTH,LOSE_HEIGHT,lose);
					waitForVblank();
					flipPage();
					while (!KEY_DOWN_NOW(BUTTON_SELECT));
					gameover = 1;
					lives = 3;
					break;
				}
			}

			if (checkCollision(row, col, goalrow, goalcol, FINN3SMALLTRIM_WIDTH, FINN3SMALLTRIM_HEIGHT)) {
				drawImage4(0,0,WIN_WIDTH,WIN_HEIGHT,win);
				drawString(140, 100, "YOU WON!", WHITE);
				waitForVblank();
				flipPage();
				while (!KEY_DOWN_NOW(BUTTON_SELECT));
				gameover = 1;
				break;
			}

			// if (col > enemy1.ecol - FINN3SMALLTRIM_WIDTH && row > enemy1.erow + FINN3SMALLTRIM_HEIGHT) {
			// 	enemy1.eliminated = 1;
			// }
			// if (enemy1.eliminated) {
			// 	if (enemy1.erow > 0) {
			// 		enemy1.erow+=5;
			// 	}
			// }


			//drawing environment
			fillScreen4(255);
			for (int i = 60; i <= 220; i += 20) {
				drawImage4(140, i, GROUNDWGRASS_WIDTH, GROUNDWGRASS_HEIGHT, groundwgrass);
			}
			for (int j = 140; j <= 220; j += 20) {
				drawImage4(100, j, GROUNDWGRASS_WIDTH, GROUNDWGRASS_HEIGHT, groundwgrass);
			}
			for (int k = 0; k <= 60; k += 20) {
				drawImage4(30, k, GROUNDWGRASS_WIDTH, GROUNDWGRASS_HEIGHT, groundwgrass);
			}
			

			//animation for main character
			frame = (count>>2) % FINN3SMALLTRIM_FRAMES;
			
			if (animate) {
				if (right) {
					drawImage4(row,col,FINN3SMALLTRIM_WIDTH,FINN3SMALLTRIM_HEIGHT, finn3smalltrim_frames[frame]);
				} else {
					drawImage4(row,col,FINN3SMALLTRIMFLIP_WIDTH,FINN3SMALLTRIMFLIP_HEIGHT, finn3smalltrimflip_frames[frame]);
				}
				animate = 0;
			} else {
				if (right) {
					drawImage4(row,col,FINN3SMALLTRIM_WIDTH,FINN3SMALLTRIM_HEIGHT, finn3smalltrim_frames[4]);
				} else {
					drawImage4(row,col,FINN3SMALLTRIMFLIP_WIDTH,FINN3SMALLTRIMFLIP_HEIGHT, finn3smalltrimflip_frames[4]);
				}
			}

			//animation for goal
			goalframe = (goalcount >> 3) % JAKESMALL_FRAMES;
			drawImage4(goalrow, goalcol, JAKESMALL_WIDTH, JAKESMALL_HEIGHT, jakesmall_frames[goalframe]);
			drawString(10, 150, "LIVES:", RED);

			//animation for enemy 1
			enemy1.eframe = (enemy1.ecount >> 2) % GUNTERSMALL_FRAMES;
			drawImage4(enemy1.erow, enemy1.ecol, GUNTERSMALL_WIDTH, GUNTERSMALL_HEIGHT, guntersmall_frames[enemy1.eframe]);
			//animation for enemy 2
			enemy2.eframe = (enemy2.ecount >> 2) % GUNTERSMALL_FRAMES;
			//drawImage4(enemy2.erow, enemy2.ecol, GUNTERSMALL_WIDTH, GUNTERSMALL_HEIGHT, guntersmall_frames[enemy2.eframe]);
			
			// if (KEY_DOWN_NOW(BUTTON_SELECT)) {
			// 	break;
			// }
			for (int i = 0; i < lives; i++) {
				drawImage4(0, 180+(20*i), HEART_WIDTH, HEART_HEIGHT, heart);
			}


			waitForVblank();
			count++;
			enemy1.ecount++;
			enemy2.ecount++;
			goalcount++;
			flipPage();

		}
		if (reset || gameover) {
			
			continue;
		}
		
	}
}
