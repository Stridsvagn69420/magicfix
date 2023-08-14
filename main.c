#ifdef _WIN32
#include <windows.h> // MSVC
#endif
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8); // Windows UTF-8
	#endif

	printf("Hello Wörld\n");
	
	return EXIT_SUCCESS;
}