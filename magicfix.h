#ifndef MAGICFIX_H
#define MAGICFIX_H

// C Standard Library
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// uint8_t-Array Length Macro
#define BUFLEN(x) (sizeof(x) / sizeof(uint8_t))

// Matcher function
typedef bool (*Matcher)(uint8_t *buf);

// File Database Entry
struct FileTypeData {
	Matcher match; // Buffer Matcher
	const uint8_t minbuf;  // Minimum Buffer Size
	const uint8_t *ext;    // File Extension
};

// File Database
#define FILEDBLEN 34     // File Database Length
#define MAXREQBUFSIZE 32 // Maximum required buffer size
extern const struct FileTypeData magicfix_database[FILEDBLEN];

#endif