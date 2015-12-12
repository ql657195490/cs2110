// Make a simple GBA state machine
// Name: HONGRUI ZHENG

// Useful defines
#define REG_DISPCNT *(unsigned short*) 0x4000000
#define MODE_3 3
#define BG2_EN (1 << 10)

#define COLOR(R,G,B) (((R) & 0x1F) | (((G) & 0x1F) << 5) | (((B) & 0x1F) << 10))
#define BLACK   COLOR(0 , 0 , 0 )
#define WHITE   COLOR(31, 31, 31)
#define RED     COLOR(31, 0 , 0 )
#define GREEN   COLOR(0 , 31, 0 )
#define BLUE    COLOR(0 , 0 , 31)
#define YELLOW  COLOR(31, 31, 0 )
#define MAGENTA COLOR(31, 0 , 31)
#define CYAN    COLOR(0 , 31, 31)
#define ORANGE  COLOR(31, 15, 0 )
#define BROWN   COLOR(18, 9 , 0 )
#define PURPLE  COLOR(15, 0 , 15)
#define TEAL    COLOR(0 , 15, 15)
#define MAROON  COLOR(15, 0 , 0 )
#define GREY    COLOR(15, 15, 15)
#define PINK    COLOR(31, 18, 19)

#define BUTTONS       *(volatile unsigned short*) 0x4000130
#define BUTTON_A      (1 << 0)
#define BUTTON_B      (1 << 1)
#define BUTTON_START  (1 << 2)
#define BUTTON_SELECT (1 << 3)
#define BUTTON_RIGHT  (1 << 4)
#define BUTTON_LEFT   (1 << 5)
#define BUTTON_UP     (1 << 6)
#define BUTTON_DOWN   (1 << 7)
#define BUTTON_R      (1 << 8)
#define BUTTON_L      (1 << 9)
#define KEY_DOWN_NOW(key) (~(BUTTONS) & key)

// Function prototypes
void fillScreen3(unsigned short color);
void waitForVBlank();
void drawString3(int x, int y, const char *str, unsigned short color);

// State enum definition
enum GBAState {
	START,
	START_NODRAW,
	STATE_1,
	STATE_2,
	STATE_3
};

int main() {

	REG_DISPCNT = MODE_3 | BG2_EN;

	enum GBAState state = START;

	// TODO add any additional variables here that you need
	// Hint: You probably need one to do accurate detection of pressing A without
	// rapidly cycling through all your states!

	while(1) {
		waitForVBlank();
		switch(state) {
		case START:
			fillScreen3(WHITE);
			drawString3(4, 4, "This is the first state.", BLACK);
			drawString3(10, 20, "Press A for the next one", BLUE);
			drawString3(10, 30, "In vbam, A is probably\nmapped to the Z key", GREY);
			state = START_NODRAW;
			break;
		case START_NODRAW:

			// TODO make it change to another state by pressing A

			fillScreen3(WHITE);
			drawString3(4, 4, "This is the first state.", BLACK);
			drawString3(10, 20, "Press A for the next one", BLUE);
			drawString3(10, 30, "In vbam, A is probably\nmapped to the Z key", GREY);
			while (!KEY_DOWN_NOW(BUTTON_A));
			state = STATE_1;
			while (KEY_DOWN_NOW(BUTTON_A));
			break;
			

		case STATE_1:
			fillScreen3(RED);
			drawString3(4, 4, "This is the second state.", BLACK);
			drawString3(10, 20, "Press A for the next one", BLUE);
			drawString3(10, 30, "In vbam, A is probably\nmapped to the Z key", GREY);
			while (!KEY_DOWN_NOW(BUTTON_A));
			state = STATE_2;
			while (KEY_DOWN_NOW(BUTTON_A));
			break;
			

		case STATE_2:
			fillScreen3(YELLOW);
			drawString3(4, 4, "This is the third state.", BLACK);
			drawString3(10, 20, "Press A for the next one", BLUE);
			drawString3(10, 30, "In vbam, A is probably\nmapped to the Z key", GREY);
			while (!KEY_DOWN_NOW(BUTTON_A));
			state = STATE_3;
			while (KEY_DOWN_NOW(BUTTON_A));
			break;
			

		case STATE_3:
			fillScreen3(GREEN);
			drawString3(4, 4, "This is the forth state.", BLACK);
			drawString3(10, 20, "Press A for the next one", BLUE);
			drawString3(10, 30, "In vbam, A is probably\nmapped to the Z key", GREY);
			while (!KEY_DOWN_NOW(BUTTON_A));
			state = START_NODRAW;
			while (KEY_DOWN_NOW(BUTTON_A));
			break;
			
			
		}

		// TODO you should probably do something here with one of your variables
	}

	return 0;
}

