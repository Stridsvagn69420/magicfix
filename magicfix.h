#ifndef MAGICFIX_GLOBAL_H
#define MAGICFIX_GLOBAL_H

// C Standard Library
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

//CJson Library
#include "cJSON.h"

/// @brief char-Array Length Macro
#define BUFLEN(x) (sizeof(x) / sizeof(char))

/// @brief Magicfix Result Status Enum. Negate output if used in if-statements directly.
enum MagicResult {
	MagicTrue,   // Buffer is Type
	MagicFalse,  // Buffer is not Type
	MagicBuffErr // Buffer too small
};

// Submodules
#include "audio.h"
#include "video.h"
#include "image.h"
#include "interface.h"

#endif