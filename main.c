#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "magicfix.h"

// Colors
#define RED "\x1B[31m"
#define YEL "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define RESET "\x1B[0m"

int main(int argc, char **argv) {
	// Print Metadata
	if (argc < 2) {
		printf("%smagicfix - Command-line tool to repair your file extensions%s\n", MAG, RESET);
		printf("%sVersion:%s %s\n", CYN, RESET, MAGICFIX_VERSION);
		printf("%sGitHub:%s %s\n", CYN, RESET, MAGICFIX_GITHUB);
		printf("%sAuthor:%s %s\n", CYN, RESET, MAGICFIX_AUTHOR);
		printf("%sLicense:%s %s\n", CYN, RESET, MAGICFIX_LICENSE);
		return EXIT_SUCCESS;
	}

	// Iterate over Command-Line Args
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
				printf("%sSuccessfully changed to %s%s%s\n", BLU, MAG, ext, RESET);
			} else {
				fprintf("%sCould not change to %s%s%s\n", RED, YEL, ext, RESET);
			}
		}
	}
	return EXIT_SUCCESS;
}