#ifndef MAGICFIX_VIDEO_H
#define MAGICFIX_VIDEO_H

#include "result.h"

/// @brief WebM Video Matcher
/// @return MagicResult
enum MagicResult magicfix_webm(uint8_t *buf);

/// @brief MKV Video Matcher
/// @return MagicResult
enum MagicResult magicfix_mkv(uint8_t *buf);

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
enum MagicResult magicfix_mp4(uint8_t *buf);

/// @brief M4V Video Matcher
/// @return MagicResult
enum MagicResult magicfix_m4v(uint8_t *buf);

/// @brief MOV Video Matcher
/// @return MagicResult
enum MagicResult magicfix_mov(uint8_t *buf);

#endif