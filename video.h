#ifndef MAGICFIX_VIDEO_H
#define MAGICFIX_VIDEO_H

#include "magicfix.h"

/// @brief WebM Video Matcher
/// @return MagicResult
enum MagicResult magicfix_webm(uint8_t *buf);

/// @brief AVI Video Matcher
/// @return MagicResult
enum MagicResult magicfix_avi(uint8_t *buf);

/// @brief FLV Video Matcher
/// @return MagicResult
enum MagicResult magicfix_flv(uint8_t *buf);

/// @brief MPEG Video Matcher
/// @return MagicResult
enum MagicResult magicfix_mpeg(uint8_t *buf);

/// @brief MP4 Video Matcher
/// @return MagicResult
enum MagicResult magicfix_mpeg(uint8_t *buf);

#endif