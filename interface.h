#ifndef INTERFACE_H
#define INTERFACE_H

#include "magicfix.h"

#define ERR_JSON 2

unsigned char* read_file(char* filename);
enum MagicResult process(char* filename, char* resutl);

#endif