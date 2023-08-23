#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "magicfix.h"

// Colors
#define RED "\x1B[31m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
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

	// Audio-Flag
	bool audio = (strcmp(argv[1], "--audio")) ? false : true;
	if (argc < 3 && audio) {
		fprintf(stderr, "%sPlease provide files to fix!%s\n", RED, RESET);
		return EXIT_FAILURE;
	}

	// Iterate over Command-Line Args
	int status = 1;
	for (size_t i = (audio ? 2 : 1); i < argc; i++) {
		int res = magicfix_matchfile(argv[i]);
		switch (res) {
		case -3:
		case -2:
			fprintf(stderr, "%sFailed to open %s%s%s\n", RED, YEL, argv[i], RESET);
			break;

		case -1:
			fprintf(stderr, "%sFile is of %sUnknown Type%s\n", CYN, RED, RESET);
			break;

		default:;
			uint8_t* ext = (audio && magicfix_database[res].exta != NULL) ? magicfix_database[res].exta : magicfix_database[res].extv;
			if (magicfix_rename(argv[i], ext) == 0) {
				printf("%sSuccessfully changed to %s%s%s\n", BLU, MAG, ext, RESET);
				status = EXIT_SUCCESS;
			} else {
				fprintf(stderr, "%sCould not change to %s%s%s\n", RED, YEL, ext, RESET);
			}
		}
	}
	return status;
}
