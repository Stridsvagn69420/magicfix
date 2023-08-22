#ifndef MAGICFIX_H
#define MAGICFIX_H

// Magicfix Metadata
#define MAGICFIX_VERSION "v1.0.0"
#define MAGICFIX_GITHUB "https://github.com/Stridsvagn69420/magicfix"
#define MAGICFIX_AUTHOR "Stridsvagn69420"
#define MAGICFIX_LICENSE "EUPL-1.2"

// C Standard Library
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// Matcher function
typedef bool (*Matcher)(const uint8_t* buf);

// File Database Entry
struct FileTypeData {
	Matcher match; // Buffer Matcher
	const uint8_t minbuf;  // Minimum Buffer Size
	const uint8_t *ext;    // File Extension
};

// File Database
#define FILEDBLEN 34     // File Database Length
#define MAXREQBUFSIZE 36 // Maximum required buffer size
extern const struct FileTypeData magicfix_database[FILEDBLEN];

/// @brief File Header Matcher
/// @param filedata File Data (Must be at least MAXREQBUFSIZE large)
/// @return Position in magicfix_database, -1 if not found.
int magicfix_match(const uint8_t* filedata);

/// @brief File Matcher Wrapper
/// @param path String
/// @return Position in magicfix_database, -1 if not found, -2 if stream error, -3 if file could not be opened.
int magicfix_matchfile(const char* path);

/// @brief Extension Replacer
/// @param fpath File Path to be modified
/// @param ext New File Extension (Must start with a dot)
/// @return 
void magicfix_extrep(char* fpath, const char* ext);

/// @brief File Extension Rename Wrapper
/// @param oldpath Path to File
/// @param ext New File Extension (Must start with a dot)
/// @return Result of rename()
int magicfix_rename(const char* oldpath, const char* ext);

#endif
