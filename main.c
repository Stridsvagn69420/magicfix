#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "magicfix.h"

int main(int argc, char** argv) {
	// Check for arguments
	if (argc < 2) {
		printf("Please append a file!\n");
		return EXIT_FAILURE;
	}

	// Open file
	FILE *fp = fopen(argv[1], "rb");
	/*if (fp == NULL) {
		printf("Failed to open %s\n", argv[1]);
		return EXIT_FAILURE;
	}*/

	// Read file contents
	uint8_t filedata[MAXREQBUFSIZE] = {0};
	//memset(filedata, 0x00, MAXREQBUFSIZE);
	fread(&filedata, sizeof(uint8_t), MAXREQBUFSIZE, fp);
	if (ferror(fp)) {
		printf("Error reading data from file stream!\n");
		return EXIT_FAILURE;
	}
	fclose(fp);

	for (size_t i = 0; i < MAXREQBUFSIZE; i++) {
		if ((i & 3) == 0) {
			printf("\n");
		}
		printf("%02X ", filedata[i]);
	}
	printf("\n");



	// Match file
	int found = magicfix_match(filedata);

	// Print result to user
	if (found == -1) {
		printf("Could not determine extension!\n");
		return EXIT_FAILURE;
	}
	printf("Extension: %s\n", magicfix_database[found].ext);
	return EXIT_SUCCESS;
}