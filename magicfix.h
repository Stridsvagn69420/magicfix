#ifndef MAGICFIX_GLOBAL_H
#define MAGICFIX_GLOBAL_H

/// @author Stridsvagn69420 

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

// Submodules
#include "audio.h"
#include "video.h"
#include "image.h"
#include "interface.h"
#include "result.h"

#endif