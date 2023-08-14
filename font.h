#ifndef MAGICFIX_FONT_H
#define MAGICFIX_FONT_H

#include "magicfix.h"

/// @brief WOFF Font Matcher
/// @return MagicResult
enum MagicResult magicfix_woff(char *buf);

/// @brief WOFF2 Font Matcher
/// @return MagicResult
enum MagicResult magicfix_woff2(char *buf);

/// @brief TTF Font Matcher
/// @return MagicResult
enum MagicResult magicfix_ttf(char *buf);

/// @brief OTF Font Matcher
/// @return MagicResult
enum MagicResult magicfix_otf(char *buf);

#endif