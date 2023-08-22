#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "magicfix.h"

#define RED "\x1B[31m"
#define YEL "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define RESET "\x1B[0m"

int main(int argc, char **argv) {
	// Check for arguments
	if (argc < 2) {
		printf("Please append a file!\n");
		return EXIT_FAILURE;
	}

	// Invoke Wrapper
	int status = 0;
	for (size_t i = 1; i < argc; i++) {
		int res = magicfix_matchfile(argv[i]);
		switch (res) {
		case -3:
			fprintf(stderr, "%sFailed to open %s%s%s\n", RED, YEL, argv[i], RESET);
			status = EXIT_FAILURE;
			break;

		case -2:
			fprintf(stderr, "%sFailed to read from File Stream%s\n", RED, RESET);
			status = EXIT_FAILURE;
			break;

		case -1:
			fprintf(stderr, "%sFile is of %sUnknown Type%s\n", RED, YEL, RESET);
			status = EXIT_FAILURE;
			break;

		default:
			char* ext = magicfix_database[res].ext;
			if (magicfix_rename(argv[i], ext) == 0) {
				printf("%sSuccessfully changed file extension to %s%s%s\n", BLU, MAG, ext, RESET);
			} else {
				fprintf("%sCould not change file extension to %s%s%s\n", RED, YEL, ext, RESET);
			}
		}
	}
	return EXIT_SUCCESS;
}