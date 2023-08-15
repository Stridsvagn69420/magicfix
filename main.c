#include "interface.h"
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

	printf("Héllô Wörld\n");

	unsigned char buff[9] = ""; 
	if(process(argv[1], buff) == MagicFalse)
		printf("OPPS, we can't fix your file :(\n");
	else
	 	printf("%s", buff);
	return EXIT_SUCCESS;
}