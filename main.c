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

	// Invoke Wrapper
	int res = magicfix_matchfile(argv[1]);
	switch (res) {
		case -3:
			fprintf(stderr, "Failed to open %s\n", argv[1]);
			break;

		case -2:
			fprintf(stderr, "Failed to read from File Stream\n");
			break;

		case -1:
			fprintf(stderr, "File is of unknown type\n");
			break;

		default:
			printf("Extension: %s\n", magicfix_database[res].ext);
			return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}