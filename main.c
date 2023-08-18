#include <stdio.h>
#include <stdlib.h>
#include "magicfix.h"

int main(int argc, char** argv) {
	// Check for arguments
	if (argc < 2) {
		printf("Please append a file!\n");
		return EXIT_FAILURE;
	}

	// Open file
	FILE *fp = fopen(argv[1], "rb");
	if (fp == NULL) {
		printf("Failed to open %s\n", argv[1]);
		return EXIT_FAILURE;
	}

	// Read file contents
	uint8_t filedata[MAXREQBUFSIZE];
	fread(&filedata, sizeof(uint8_t), MAXREQBUFSIZE, fp);
	if (ferror(fp)) {
		printf("Error reading data from file stream!\n");
		return EXIT_FAILURE;
	}

	// Find entry in database
	bool found = false;
	size_t foundpos;
	for (size_t i = 0; i < FILEDBLEN; i++) {
		if (fileTypeDb[i].match(filedata)) {
			found = true;
			foundpos = i;
		}
	}

	// Print result to user
	if (found) {
		printf("Recommended extension: %s\n", fileTypeDb[foundpos].ext);
		return EXIT_SUCCESS;
	} else {
		printf("Could not determine recommended extension!\n");
		return EXIT_FAILURE;
	}
}