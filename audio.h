#ifndef MAGICFIX_AUDIO_H
#define MAGICFIX_AUDIO_H

#include "result.h"

/// @brief AIFF Audio Matcher
/// @return MagicResult
enum MagicResult magicfix_aiff(uint8_t *buf);

/// @brief WAV Audio Matcher
/// @return MagicResult
enum MagicResult magicfix_wav(uint8_t *buf);

/// @brief WAV Audio Matcher
/// @return MagicResult
enum MagicResult magicfix_flac(uint8_t *buf);

/// @brief OGG Audio Matcher
/// @return MagicResult
enum MagicResult magicfix_ogg(uint8_t *buf);

/// @brief OGG-Opus Audio Matcher
/// @return MagicResult
enum MagicResult magicfix_oggopus(uint8_t *buf);

/// @brief MIDI Audio Matcher
/// @return MagicResult
enum MagicResult magicfix_midi(uint8_t *buf);

/// @brief MP3 Audio Matcher
/// @return MagicResult
enum MagicResult magicfix_mp3(uint8_t *buf);

/// @brief AAC Audio Matcher
/// @return MagicResult
enum MagicResult magicfix_aac(uint8_t *buf);

/// @brief M4A Audio Matcher
/// @return MagicResult
enum MagicResult magicfix_m4a(uint8_t *buf);

#endif