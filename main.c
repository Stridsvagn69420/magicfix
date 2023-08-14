#ifdef _WIN32
#include <windows.h> // MSVC
#endif
#include "magicfix.h"

int main(int argc, char** argv) {
	#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8); // Windows UTF-8
	#endif

	printf("Héllä Wörld\n");

	unsigned char buff[3] = "ID3"; 
	enum MagicResult result = magicfix_mp3(buff);
	printf("MP3: %d\n", result);
	
	return EXIT_SUCCESS;
}