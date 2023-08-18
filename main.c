#ifdef _WIN32
#include <windows.h> // Windows-API
#endif
#include <stdio.h>
#include <stdlib.h>
#include "magicfix.h"

int main(int argc, char** argv) {
	#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8); // Windows UTF-8
	#endif

	if (argc < 2) {
		printf("Please append a file!\n");
		return EXIT_FAILURE;
	}

	FILE *fp = fopen(argv[1], "rb");
	if (fp == NULL) {
		printf("Failed to open %s\n", argv[1]);
		return EXIT_FAILURE;
	}

	uint8_t filedata[MAXREQBUFSIZE];
	fread(&filedata, sizeof(uint8_t), MAXREQBUFSIZE, fp);
	if (ferror(fp)) {
		printf("Error reading data from file stream!\n");
		return EXIT_FAILURE;
	}

	bool found = false;
	size_t foundpos;
	for (size_t i = 0; i < FILEDBLEN; i++) {
		if (fileTypeDb[i].match(filedata)) {
			found = true;
			foundpos = i;
		}
	}

	if (found) {
		printf("Recommended extension: %s\n", fileTypeDb[foundpos].ext);
		return EXIT_SUCCESS;
	} else {
		printf("Could not determine type of provided file!\n");
		return EXIT_FAILURE;
	}
}