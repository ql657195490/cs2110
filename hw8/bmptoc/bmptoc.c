// bmptoc.c
// Name: HONGRUI ZHENG

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

// This is the array into which you will load the raw data from the file
// You don't have to use this array if you don't want to, but you will be responsible
// for any errors caused by erroneously using the stack or malloc if you do it a
// different way, incorrectly!
char data_arr[0x36 + 240 * 160 * 4];
int main(int argc, char *argv[]) {

	// 1. Make sure the user passed in the correct number of arguments
	int read_size = 0x36 + 240 * 160 * 4;
	if (argc != 2) {
		printf("Number of arguments incorrect. \n");
		return 0;
	}

	// 2. Open the file; if it doesn't exist, tell the user and then exit
	FILE *fp;
	int name_length = strlen(argv[1]) - 4;
	char name_woext[name_length];
	strncpy(name_woext, argv[1], name_length);
	name_woext[name_length] = 0;
	char upper[strlen(name_woext)];
	for(unsigned int i = 0; i < strlen(name_woext); i++) {
		if (name_woext[i] > 96 && name_woext[i] < 123) {
			upper[i] = name_woext[i] - 32;
		} else {
			upper[i] = name_woext[i];
		}
	}
	upper[strlen(name_woext)] = 0;
	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("File doesn't exist. \n");
		return 0;
	}

	// 3. Read the file into the buffer then close it when you are done
	int bytes_read = fread(data_arr, 4, read_size, fp);
	fclose(fp);
	bytes_read = bytes_read;

	// 4. Get the width and height of the image
	int width;
	width = *(int*)&data_arr[0x12];
	int height;
	height = *(int*)&data_arr[0x16];

	// 5. Create header file, and write header contents; close it
	char header[strlen(name_woext) + 2];
	sprintf(header, "%s.h", name_woext);
	FILE *fpo1 = fopen(header, "w");
	fprintf(fpo1, "#define %s_WIDTH %d\n", upper, width);
	fprintf(fpo1, "#define %s_HEIGHT %d\n", upper, height);
	fprintf(fpo1, "const unsigned short %s_data[%d];", name_woext, width * height);
	fclose(fpo1);

	// 6. Create C file, and write pixel data; close it
	char cfile[strlen(name_woext) + 2];
	sprintf(cfile, "%s.c", name_woext);
	FILE *fpo2 = fopen(cfile, "w");
	fprintf(fpo2, "const unsigned short %s_data[%d] = {", name_woext, height * width);
	unsigned char bmppixel;
	unsigned short gbapixel;
	for (int k = (0x36 + width * (height - 1) * 4); k >= 0x36; k -= (width * 4)) {
		for (int j = k; j < (k + width * 4); j += 4) {
			gbapixel = 0;
			bmppixel = (unsigned char)data_arr[j] / 8;
			gbapixel += (bmppixel << 10);
			bmppixel = (unsigned char)data_arr[j + 1] / 8;
			gbapixel += (bmppixel << 5);
			bmppixel = (unsigned char)data_arr[j + 2] / 8;
			gbapixel += (bmppixel);
			fprintf(fpo2, "0x%x, ", gbapixel);
		}
	}
	fprintf(fpo2, "};");
	fclose(fpo2);
	return 0;
}

