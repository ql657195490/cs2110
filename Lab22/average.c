// CS 2110 Lab 22
// Name: HONGRUI ZHENG

#define _POSIX_C_SOURCE 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Gets a number from stdin (delimited by spaces)
int getNum(void) {
	int num = 0, val;
	static int eof = 0;
	if(eof) {
		return -1;
	}
	do { // because do-while doesn't get enough love
		val = getchar();
		if(val >= '0' && val <= '9') {
			num *= 10;
			num += val - '0';
		}
	} while(val != ' ' && val != '\n');
	if(val == '\n') {
		eof = 1;
	}
	return num;
}

// Calculate the average of several numbers
int main(void) {
	
	// Dynamically sized array to hold numbers
	// Since we should have at least 1 number, malloc space for 1 int to start
	int *arr = malloc(sizeof(int) * 1);

	// How many numbers are in our array
	int count = 1;

	// Get the first number
	arr[0] = getNum();

	// Continue to get numbers from the user until they press enter
	int num;
	while((num = getNum()) >= 0) {
		
		count++;										// TODO update count
		int *temparr = malloc(sizeof(int)*count);		// TODO create a new array large enough to hold all the existing numbers
														//      as well as the new one that was just entered
		memcpy(temparr, arr, sizeof(int)*(count-1));					// TODO copy the elements from the old array into the new one (memcpy)
		temparr[count-1] = num;							// TODO store the new number in the last index of our new array
		free(arr);
		arr = temparr;									// TODO free the old array's data then assign the new array pointer to arr
	}

	// Check to see if you were following directions
	FILE *p = popen("grep average.c -e realloc -c", "r");
	char buf[10];
	fgets(buf, 10, p);
	fclose(p);
	if(atoi(buf) > _POSIX_C_SOURCE) {
		printf("You implemented it with realloc, which the instructions specifically said not to do\n");
		return 0;
	}

	// Print the average
	int sum = 0;
	for(int i = 0; i < count; ++i) {
		sum += arr[i];
	}
	printf("Average: %d\n", sum / count); // yes I know it's floored average. too bad

	free(arr);// TODO what should we do here?



	return 0;
}

