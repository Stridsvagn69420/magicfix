#ifndef MAGICFIX_RESULT_H
#define MAGICFIX_RESULT_H

// C Standard Library
#include <stdint.h>
#include <stdbool.h>

/// @brief char-Array Length Macro
#define BUFLEN(x) (sizeof(x) / sizeof(char))

/// @brief Magicfix Result Status Enum. Negate output if used in if-statements directly.
enum MagicResult {
	MagicTrue,   // Buffer is Type
	MagicFalse,  // Buffer is not Type
	MagicBuffErr // Buffer too small
};

#endif