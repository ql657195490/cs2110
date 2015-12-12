/* hex2ascii.c
 * CS 2110 Fall 2015 Lab 24
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// Do not call this function in the code! Stack smash to run it
void smash() {
	printf("Stack smashed!\n");
	exit(0);
}

// Helper function that converts the hex chars into an ASCII character
char convert_char(char c1, char c2) {
	c1 = toupper(c1);
	c2 = toupper(c2);
	if(c1 < '0' || c1 > 'F' || (c1 > '9' && c1 < 'A')) c1 = '0';
	if(c2 < '0' || c2 > 'F' || (c2 > '9' && c2 < 'A')) c2 = '0';
	c1 -= (c1 > '9') ? 'A' - 10 : '0';
	c2 -= (c2 > '9') ? 'A' - 10 : '0';
	return (c1 << 4) | c2;
}

// Read characters and print them
void read_chars() {

	// Local vars
	char buffer[16];
	static int index = 0;
	static char c1, c2, end = 0;

	// Fill the buffer with characters
	while((c1 = getchar()) != '\n') {
		if((c2 = getchar()) == '\n') end = 1;
		buffer[index++] = convert_char(c1, c2);
		if(end) break;
	}

	// Null-terminate the string
	buffer[index] = '\0';

	// Print the buffer
	printf("\n%s\n", buffer);
}

// Turn a series of two-digit hex values into ASCII
int main(void) {

	// Message to the user
	printf("Input a hex string to convert to ASCII: ");

	// Read characters and print the buffer
	read_chars();
	return 0;
}

