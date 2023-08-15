#ifndef MAGICFIX_IMAGE_H
#define MAGICFIX_IMAGE_H

#include "magicfix.h"

/// @brief EXR Image Matcher
/// @return MagicResult
enum MagicResult magicfix_exr(uint8_t *buf);

/// @brief PNG Image Matcher
/// @return MagicResult
enum MagicResult magicfix_png(uint8_t *buf);

/// @brief WebP Image Matcher
/// @return MagicResult
enum MagicResult magicfix_webp(uint8_t *buf);

/// @brief TIFF Image Matcher
/// @return MagicResult
enum MagicResult magicfix_tiff(uint8_t *buf);

#endif