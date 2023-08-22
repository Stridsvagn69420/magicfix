#include "magicfix.h"

// Quicktime Container
static bool ftyp(const uint8_t* buf) {
	return buf[4] == 0x66 && buf[5] == 0x74 && buf[6] == 0x79 && buf[7] == 0x70; // ftyp
}

// WAV Audio
static bool wav(const uint8_t* buf) {
	return buf[0] == 0x52 && buf[1] == 0x49 && buf[2] == 0x46 && buf[3] == 0x46    // RIFF
		&& buf[8] == 0x57 && buf[9] == 0x41 && buf[10] == 0x56 && buf[11] == 0x45; // WAVE
}

// FLAC Audio
static bool flac(const uint8_t* buf) {
	return buf[0] == 0x66 && buf[1] == 0x4C && buf[2] == 0x61 && buf[3] == 0x43; // fLaC
}

// OGG Audio
static bool ogg(const uint8_t* buf) {
	return buf[0] == 0x4F && buf[1] == 0x67 && buf[2] == 0x67 && buf[3] == 0x53; // OggS
}

// OGG Opus Audio
static bool opus(const uint8_t* buf) {
	return ogg(buf) && buf[28] == 0x4F && buf[29] == 0x70 && buf[30] == 0x75 && buf[31] == 0x73 && buf[32] == 0x48 && buf[33] == 0x65 && buf[34] == 0x61 && buf[35] == 0x64; // OpusHead
}

// MP3 Audio
static bool mp3(const uint8_t* buf) {
	bool id3 = buf[0] == 0x49 && buf[1] == 0x44 && buf[2] == 0x33; // ID3
	bool mp3 = buf[0] == 0xFF && (buf[1] == 0xFB || buf[1] == 0xF3 || buf[1] == 0xF2); // No ID3 or ID3v1
	return id3 || mp3;
}

// AAC Audio
static bool aac(const uint8_t* buf) {
	return buf[0] == 0xFF && (buf[1] == 0xF1 || buf[1] == 0xF9);
}

// M4A Audio
static bool m4a(const uint8_t* buf) {
	bool m4a = buf[10] == 0x41;  // M4A 
	bool m4b = buf[10] == 0x42;  // M4B
	bool m4p = buf[10] == 0x50;  // M4P
	return ftyp(buf) && buf[8] == 0x4D && buf[9] == 0x34 && (m4a || m4b || m4p);
}

// MIDI Audio
static bool midi(const uint8_t* buf) {
	return buf[0] == 0x4D && buf[1] == 0x54 && buf[2] == 0x68 && buf[3] == 0x64;
}

// AIFF Audio
static bool aiff(const uint8_t* buf) {
	return buf[0] == 0x46 && buf[1] == 0x4F && buf[2] == 0x52 && buf[3] == 0x4D    // FORM
		&& buf[8] == 0x41 && buf[9] == 0x49 && buf[10] == 0x46 && buf[11] == 0x46; // AIFF
}

// MP4 Video
static bool mp4(const uint8_t* buf) {
	return ftyp(buf)
		&& (
			buf[8] == 0x61 && buf[9] == 0x76 && buf[10] == 0x63 && buf[11] == 0x31    // avc1
			|| buf[8] == 0x64 && buf[9] == 0x61 && buf[10] == 0x73 && buf[11] == 0x68 // dash
			|| buf[8] == 0x69 && buf[9] == 0x73 && buf[10] == 0x6F && buf[11] == 0x6D // isom
			|| buf[8] == 0x69 && buf[9] == 0x73 && buf[10] == 0x6F && buf[11] == 0x32 // iso2
			|| buf[8] == 0x6D && buf[9] == 0x70 && buf[10] == 0x34 && buf[11] == 0x32 // mp42
			|| buf[8] == 0x6D && buf[9] == 0x70 && buf[10] == 0x37 && buf[11] == 0x31 // mp71
			|| buf[8] == 0x6D && buf[9] == 0x6D && buf[10] == 0x70 && buf[11] == 0x34 // mmp4
			|| buf[8] == 0x6D && buf[9] == 0x70 && buf[10] == 0x34 && buf[11] == 0x76 // mp4v
			|| buf[8] == 0x4D && buf[9] == 0x53 && buf[10] == 0x4E && buf[11] == 0x56 // MSNV
		); 
}

// WebM Video
static bool webm(const uint8_t* buf) {
	return buf[0] == 0x1A && buf[1] == 0x45 && buf[2] == 0xDF && buf[3] == 0xA3
		&& buf[24] == 0x77 && buf[25] == 0x65 && buf[26] == 0x62 && buf[27] == 0x6D; // webm
}

// Matroska Video
static bool mkv(const uint8_t* buf) {
	return buf[0] == 0x1A && buf[1] == 0x45  && buf[2] == 0xDF && buf[3] == 0xA3
		&& buf[24] == 0x6D && buf[25] == 0x61 && buf[26] == 0x74 && buf[27] == 0x72 && buf[28] == 0x6F && buf[29] == 0x73 && buf[30] == 0x6B && buf[31] == 0x61; // matroska
}

// M4V Video
static bool m4v(const uint8_t* buf) {
	return ftyp(buf) && buf[8] == 0x4D && buf[9] == 0x34 && buf[10] == 0x56 && buf[11] == 0x20; // M4V 
}

// 3GPP Video
static bool tgp(const uint8_t* buf) {
	return ftyp(buf) && buf[8] == 0x33 && buf[9] == 0x67 && buf[10] == 0x70; // 3gp
}

// 3GPP2 Video
static bool tg2(const uint8_t* buf) {
	return ftyp(buf) && buf[8] == 0x33 && buf[9] == 0x67 && buf[10] == 0x32; // 3g2
}

// MOV Quicktime Video
static bool mov(const uint8_t* buf) {
	bool ftypqt = ftyp(buf) && buf[8] == 0x71 && buf[9] == 0x74 && buf[10] == 0x20 && buf[11] == 0x20; // ftypqt  
	bool moov = buf[4] == 0x6D && buf[5] == 0x6F && buf[6] == 0x6F && buf[7] == 0x76; // moov
	bool free = buf[4] == 0x66 && buf[5] == 0x72 && buf[6] == 0x65 && buf[7] == 0x65; // free
	return ftypqt || moov || free;
}

// FLV Video
static bool flv(const uint8_t* buf) {
	return buf[0] == 0x46 && buf[1] == 0x4C && buf[2] == 0x56; // FLV
}

// MPEG Video
static bool mpeg(const uint8_t* buf) {
	return buf[0] == 0x00 && buf[1] == 0x00 && buf[2] == 0x01 && buf[3] >= 0xB0 && buf[3] <= 0xBF;
}

// AVI Video
static bool avi(const uint8_t* buf) {
	return buf[0] == 0x52 && buf[1] == 0x49 && buf[2] == 0x46 && buf[3] == 0x46 // RIFF
		&& buf[8] == 0x41 && buf[9] == 0x56 && buf[10] == 0x49; // AVI
}

// TTF Font
static bool ttf(const uint8_t* buf) {
	return buf[0] == 0x00 && buf[1] == 0x01 && buf[2] == 0x00 && buf[3] == 0x00 && buf[4] == 0x00;	
}

// OTF Font
static bool otf(const uint8_t* buf) {
	return buf[0] == 0x4F && buf[1] == 0x54 && buf[2] == 0x54 && buf[3] == 0x4F; // OTTO
}

// WOFF2 Font
static bool woff2(const uint8_t* buf) {
	return buf[0] == 0x77 && buf[1] == 0x4F && buf[2] == 0x46 && buf[3] == 0x32 // WOF2
		&& buf[4] == 0x00 && buf[5] == 0x01 && buf[6] == 0x00 && buf[7] == 0x00;
}

// WOFF Font
static bool woff(const uint8_t* buf) {
	return buf[0] == 0x77 && buf[1] == 0x4F && buf[2] == 0x46 && buf[3] == 0x46 // WOFF
		&& buf[4] == 0x00 && buf[5] == 0x01 && buf[6] == 0x00 && buf[7] == 0x00;
}

// PNG Image
static bool png(const uint8_t* buf) {
	return buf[0] == 0x89 && buf[1] == 0x50 && buf[2] == 0x4E && buf[3] == 0x47 && buf[4] == 0x0D && buf[5] == 0x0A && buf[6] == 0x1A && buf[7] == 0x0A;
}

// WebP Image
static bool webp(const uint8_t* buf) {
	return buf[0] == 0x52 && buf[1] == 0x49 && buf[2] == 0x46 && buf[3] == 0x46  // RIFF
		&& buf[8] == 0x57 && buf[9] == 0x45 && buf[10] == 0x42 && buf[11] == 0x50; // WEBP
}

// HEIC Image
static bool heic(const uint8_t* buf) {
	return ftyp(buf) && buf[8] == 0x68 && buf[9] == 0x65 && buf[10] == 0x69 && buf[11] == 0x63; // heic
}

// AVIF Image
static bool avif(const uint8_t* buf) {
	return ftyp(buf) && buf[8] == 0x61 && buf[9] == 0x76 && buf[10] == 0x69 && buf[11] == 0x66; // avif
}

// JPEG Image
static bool jpeg(const uint8_t* buf) {
	return buf[0] == 0xFF && buf[1] == 0xD8 && buf[2] == 0xFF;
}

// JPEG 2000 Image
static bool jpeg2(const uint8_t* buf) {
	bool kp2 = buf[0] == 0xFF && buf[1] == 0x4F && buf[2] == 0xFF && buf[3] == 0x51;
	bool jp2 = buf[0] == 0x00 && buf[1] == 0x00 && buf[2] == 0x00 && buf[3] == 0x0C
		&& buf[4] == 0x6A && buf[5] == 0x50 && buf[6] == 0x20 && buf[7] == 0x20
		&& buf[8] == 0x0D && buf[9] == 0x0A && buf[10] == 0x87 && buf[11] == 0x0A;
	return jp2 || kp2;
}

// JPEG-XL Image
static bool jpgxl(const uint8_t* buf) {
	bool kxl = buf[0] == 0xFF && buf[1] == 0x0A;
	bool jxl = buf[0] == 0x00 && buf[1] == 0x00 && buf[2] == 0x00 && buf[3] == 0x0C
		&& buf[4] == 0x4A && buf[5] == 0x58 && buf[6] == 0x4C && buf[7] == 0x20
		&& buf[8] == 0x0D && buf[9] == 0x0A && buf[10] == 0x87 && buf[11] == 0x0A;
	return jxl || kxl;
}

// JPEG-XS Image
static bool jpgxs(const uint8_t* buf) {
	return buf[0] == 0xFF && buf[1] == 0x10 && buf[2] == 0xFF && buf[3] == 0x50;
}

// JPEG-XR Image
static bool jpgxr(const uint8_t* buf) {
	return buf[0] == 0x49 && buf[1] == 0x49 && buf[2] == 0xBC && buf[3] == 0x01;
}

// QOI Image
static bool qoif(const uint8_t* buf) {
	return buf[0] == 0x71 && buf[1] == 0x6F && buf[2] == 0x69 && buf[3] == 0x66; // qoif
}

// EXR Image
static bool exr(const uint8_t* buf) {
	return buf[0] == 0x76 && buf[1] == 0x2F && buf[2] == 0x31 && buf[3] == 0x01; // v/1.
}

// Bitmap Image
static bool bmp(const uint8_t* buf) {
	return buf[0] == 0x42 && buf[1] == 0x4D; // BM
}

// TIFF Image
static bool tiff(const uint8_t* buf) {
	bool le = buf[0] == 0x49 && buf[1] == 0x49 && buf[2] == 0x2A && buf[3] == 0x00; // Little-Edian
	bool be = buf[0] == 0x4D && buf[1] == 0x4D && buf[2] == 0x00 && buf[3] == 0x2A; // Big-Endian
	return le || be;
}

/// @brief File Database
const struct FileTypeData magicfix_database[FILEDBLEN] = {
	{ wav,   12, ".wav"   },
	{ flac,   4, ".flac"  },
	{ ogg,    4, ".ogg"   },
	{ opus,  36, ".opus"  },
	{ mp3,    3, ".mp3"   },
	{ aac,    2, ".aac"   },
	{ m4a,   12, ".m4a"   },
	{ aiff,  12, ".aiff"  },
	{ mp4,   12, ".mp4"   },
	{ webm,  28, ".webm"  },
	{ mkv,   32, ".mkv"   },
	{ m4v,   12, ".m4v"   },
	{ tgp,   11, ".3gp"   },
	{ tg2,   11, ".3g2"   },
	{ mov,   12, ".mov"   },
	{ flv,    3, ".flv"   },
	{ mpeg,   4, ".mpeg"  },
	{ avi,    4, ".avi"   },
	{ ttf,    5, ".ttf"   },
	{ otf,    4, ".otf"   },
	{ woff2,  8, ".woff2" },
	{ woff,   8, ".woff"  },
	{ png,    8, ".png"   },
	{ webp,  12, ".webp"  },
	{ avif,  12, ".avif"  },
	{ jpeg,   2, ".jpg"   },
	{ jpeg2, 12, ".jp2"   },
	{ jpgxl, 12, ".jxl"   },
	{ jpgxs,  4, ".jxs"   },
	{ jpgxr,  4, ".jxr"   },
	{ qoif,   4, ".qoi"   },
	{ exr,    4, ".exr"   },
	{ bmp,    2, ".bmp"   },
	{ tiff,   4, ".tiff"  }
};

/// @brief File Header Matcher
/// @param filedata File Data (Must be at least MAXREQBUFSIZE large)
/// @return Position in magicfix_database, -1 if not found.
int magicfix_match(const uint8_t* filedata) {
	for (size_t i = 0; i < FILEDBLEN; i++) {
		if (magicfix_database[i].match(filedata)) {
			return i;
		}
	}
	return -1;
}

/// @brief File Matcher Wrapper
/// @param path String
/// @return Position in magicfix_database, -1 if not found, -2 if stream error, -3 if file could not be opened.
int magicfix_matchfile(const char* path) {
	// Open File
	FILE* fp = fopen(path, "rb");
	if (fp == NULL) {
		return -3;
	}

	// Read File
	const uint8_t filedata[MAXREQBUFSIZE] = {0};
	fread(filedata, sizeof(const uint8_t), MAXREQBUFSIZE, fp);
	if (ferror(fp)) {
		fclose(fp);
		return -2;
	}
	fclose(fp);

	// Match File
	return magicfix_match(filedata);
}

/// @brief Extension Replacer
/// @param fpath File Path to be modified (256+ Bytes Recommended)
/// @param ext New File Extension (Must start with a dot)
void magicfix_extrep(char* fpath, const char* ext) {
	// Get File Segment of Path
	char* last_slash = strrchr(fpath, '/');
	char* last_backslash = strrchr(fpath, '\\');
	char* separator = (last_slash > last_backslash) ? last_slash : last_backslash;

	// Get Extension Dot of File Segment
	char* dot = strrchr((separator == NULL) ? fpath : separator, '.');
	if (dot == NULL) {
		strcat(fpath, ext); // Append
	} else {
		strcpy(dot, ext);	// Change
	}
}

/// @brief File Extension Rename Wrapper
/// @param oldpath Path to File
/// @param ext New File Extension (Must start with a dot)
/// @return Result of rename()
int magicfix_rename(const char* oldpath, const char* ext) {
	char newpath[256] = {0};         // New File Path
	strcpy(newpath, oldpath);        // Copy Old File Path
	magicfix_extrep(newpath, ext);   // Replace Extension
	return rename(oldpath, newpath); // Rename File
}