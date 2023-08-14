#ifndef MAGICFIX_AUDIO_H
#define MAGICFIX_AUDIO_H

#include "magicfix.h"

/// @brief AIFF Audio Matcher
/// @return MagicResult
enum MagicResult magicfix_aiff(char *buf);

/// @brief WAV Audio Matcher
/// @return MagicResult
enum MagicResult magicfix_wav(char *buf);

/// @brief WAV Audio Matcher
/// @return MagicResult
enum MagicResult magicfix_flac(char *buf);

/// @brief OGG Audio Matcher
/// @return MagicResult
enum MagicResult magicfix_ogg(char *buf);

/// @brief OGG-Opus Audio Matcher
/// @return MagicResult
enum MagicResult magicfix_oggopus(char *buf);

/// @brief MIDI Audio Matcher
/// @return MagicResult
enum MagicResult magicfix_midi(char *buf);

/// @brief MP3 Audio Matcher
/// @return MagicResult
enum MagicResult magicfix_mp3(char *buf);

#endif