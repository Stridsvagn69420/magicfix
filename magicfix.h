#ifndef MAGICFIX_GLOBAL_H
#define MAGICFIX_GLOBAL_H

/// @brief C Standard Library
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/// @brief char-Array Length Macro
#define BUFLEN(x) (sizeof(x) / sizeof(char))

/// @brief Magicfix Result Status Enum. Negate output if used in if-statements directly.
enum MagicResult {
    MagicTrue,   // Buffer is Type
    MagicFalse,  // Buffer is not Type
    MagicBuffErr // Buffer too small
};

/// @brief Submodules
#include "audio.h"
#include "video.h"
#include "image.h"

#endif