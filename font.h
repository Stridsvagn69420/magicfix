#ifndef MAGICFIX_FONT_H
#define MAGICFIX_FONT_H

#include "result.h"

/// @brief WOFF Font Matcher
/// @return MagicResult
enum MagicResult magicfix_woff(uint8_t *buf);

/// @brief WOFF2 Font Matcher
/// @return MagicResult
enum MagicResult magicfix_woff2(uint8_t *buf);

/// @brief TTF Font Matcher
/// @return MagicResult
enum MagicResult magicfix_ttf(uint8_t *buf);

/// @brief OTF Font Matcher
/// @return MagicResult
enum MagicResult magicfix_otf(uint8_t *buf);

#endif