#ifdef _WIN32
#include <windows.h> // MSVC
#endif
#include <stdio.h>
#include <stdlib.h>
#include "magicfix.h"

int main(int argc, char** argv) {
	#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8); // Windows UTF-8
	#endif

	printf("Hallöchen, Welt! 🤯\n"); // UTF-8 Test

	printf("Listing File Type Database...\n");
	for (uint8_t i = 0; i < FILEDBLEN; i++) {
		printf("Ext: %s, Size: %i\n", fileTypeDb[i].ext, fileTypeDb[i].minbuf);
	}

	return EXIT_SUCCESS;
}