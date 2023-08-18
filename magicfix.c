#include "magicfix.h"

// WAV Audio
static bool wav(uint8_t *buf) {
	return buf[0] == 0x52 && buf[1] == 0x49 && buf[2] == 0x46 && buf[3] == 0x46    // RIFF
		&& buf[8] == 0x57 && buf[9] == 0x41 && buf[10] == 0x56 && buf[11] == 0x45; // WAVE
}

// FLAC Audio
static bool flac(uint8_t *buf) {
	return buf[0] == 0x66 && buf[1] == 0x4C && buf[2] == 0x61 && buf[3] == 0x43; // fLaC
}

// OGG Audio
static bool ogg(uint8_t *buf) {
	return buf[0] == 0x4F && buf[1] == 0x67 && buf[2] == 0x67 && buf[3] == 0x53; // OggS
}

// OGG Opus Audio
static bool opus(uint8_t *buf) {
	return ogg(buf) && buf[28] == 0x4F && buf[29] == 0x70 && buf[30] == 0x75 && buf[31] == 0x73 && buf[32] == 0x48 && buf[33] == 0x65 && buf[34] == 0x61 && buf[35] == 0x64; // OpusHead
}

// MP3 Audio
static bool mp3(uint8_t *buf) {
	bool id3 = buf[0] == 0x49 && buf[1] == 0x44 && buf[2] == 0x33; // ID3
	bool mp3 = buf[0] == 0xFF && (buf[1] == 0xFB || buf[1] == 0xF3 || buf[1] == 0xF2); // No ID3 or ID3v1
	return id3 || mp3;
}

// AAC Audio
static bool aac(uint8_t *buf) {
	return buf[0] == 0xFF && (buf[1] == 0xF1 || buf[1] == 0xF9);
}

// M4A Audio
static bool m4a(uint8_t *buf) {
	bool m4a = buf[8] == 0x4D && buf[9] == 0x34 && buf[10] == 0x41 && buf[11] == 0x20;  // M4A 
	bool gp4 = buf[8] == 0x33 && buf[9] == 0x67 && buf[10] == 0x70 && buf[11] == 0x34; // 3gp4
	return buf[4] == 0x66 && buf[5] == 0x74 && buf[6] == 0x79 && buf[7] == 0x70 // ftyp
		&& (m4a || gp4);
}

// MIDI Audio
static bool midi(uint8_t *buf) {
	return buf[0] == 0x4D && buf[1] == 0x54 && buf[2] == 0x68 && buf[3] == 0x64;
}

// AIFF Audio
static bool aiff(uint8_t *buf) {
	return buf[0] == 0x46 && buf[1] == 0x4F && buf[2] == 0x52 && buf[3] == 0x4D    // FORM
		&& buf[8] == 0x41 && buf[9] == 0x49 && buf[10] == 0x46 && buf[11] == 0x46; // AIFF
}

// MP4 Video
static bool mp4(uint8_t *buf) {
	return buf[4] == 0x66 && buf[5] == 0x74 && buf[6] == 0x79 && buf[7] >= 0x70 // ftyp
		&& (
			buf[8] == 0x61 && buf[9] == 0x76 && buf[10] == 0x63 && buf[11] == 0x31    // avc1
			|| buf[8] == 0x64 && buf[9] == 0x61 && buf[10] == 0x73 && buf[11] == 0x68 // dash
			|| buf[8] == 0x69 && buf[9] == 0x73 && buf[10] == 0x6F && buf[11] == 0x6D // isom
			|| buf[8] == 0x6D && buf[9] == 0x70 && buf[10] == 0x34 && buf[11] == 0x32 // mp42
			|| buf[8] == 0x6D && buf[9] == 0x70 && buf[10] == 0x37 && buf[11] == 0x31 // mp71
			|| buf[8] == 0x6D && buf[9] == 0x6D && buf[10] == 0x70 && buf[11] == 0x34 // mmp4
			|| buf[8] == 0x6D && buf[9] == 0x70 && buf[10] == 0x34 && buf[11] == 0x76 // mp4v
			|| buf[8] == 0x4D && buf[9] == 0x53 && buf[10] == 0x4E && buf[11] == 0x56 // MSNV
		); 
}

// WebM Video
static bool webm(uint8_t *buf) {
	return buf[0] == 0x1A && buf[1] == 0x45 && buf[2] == 0xDF && buf[3] == 0xA3
		&& buf[24] == 0x77 && buf[25] == 0x65 && buf[26] == 0x62 && buf[27] == 0x6D; // webm
}

// Matroska Video
static bool mkv(uint8_t *buf) {
	return buf[0] == 0x1A && buf[1] == 0x45  && buf[2] == 0xDF && buf[3] == 0xA3
		&& buf[24] == 0x6D && buf[25] == 0x61 && buf[26] == 0x74 && buf[27] == 0x72 && buf[28] == 0x6F && buf[29] == 0x73 && buf[30] == 0x6B && buf[31] == 0x61; // matroska
}

// M4V Video
static bool m4v(uint8_t *buf) {
	return buf[4] == 0x66 && buf[5] == 0x74 && buf[6] == 0x79 && buf[7] == 0x70    // ftyp
		&& buf[8] == 0x4D && buf[9] == 0x34 && buf[10] == 0x56 && buf[11] == 0x20; // M4V 
}

// MOV Quicktime Video
static bool mov(uint8_t *buf) {
	bool ftypqt = buf[4] == 0x66 && buf[5] == 0x74 && buf[6] == 0x79 && buf[7] == 0x70 && buf[8] == 0x71 && buf[9] == 0x74 && buf[10] == 0x20 && buf[11] == 0x20; // ftypqt
	bool moov = buf[4] == 0x6D && buf[5] == 0x6F && buf[6] == 0x6F && buf[7] == 0x76; // moov
	bool free = buf[4] == 0x66 && buf[5] == 0x72 && buf[6] == 0x65 && buf[7] == 0x65; // free
	return ftypqt || moov || free;
}

// FLV Video
static bool flv(uint8_t *buf) {
	return buf[0] == 0x46 && buf[1] == 0x4C && buf[2] == 0x56; // FLV
}

// MPEG Video
static bool mpeg(uint8_t *buf) {
	return buf[0] == 0x00 && buf[1] == 0x00 && buf[2] == 0x01 && buf[3] >= 0xB0 && buf[3] <= 0xBF;
}

// AVI Video
static bool avi(uint8_t *buf) {
	return buf[0] == 0x52 && buf[1] == 0x49 && buf[2] == 0x46 && buf[3] == 0x46 // RIFF
		&& buf[8] == 0x41 && buf[9] == 0x56 && buf[10] == 0x49; // AVI
}

// TTF Font
static bool ttf(uint8_t *buf) {
	return buf[0] == 0x00 && buf[1] == 0x01 && buf[2] == 0x00 && buf[3] == 0x00 && buf[4] == 0x00;	
}

// OTF Font
static bool otf(uint8_t *buf) {
	return buf[0] == 0x4F && buf[1] == 0x54 && buf[2] == 0x54 && buf[3] == 0x4F; // OTTO
}

// WOFF2 Font
static bool woff2(uint8_t *buf) {
	return buf[0] == 0x77 && buf[1] == 0x4F && buf[2] == 0x46 && buf[3] == 0x32 // WOF2
		&& buf[4] == 0x00 && buf[5] == 0x01 && buf[6] == 0x00 && buf[7] == 0x00;
}

// WOFF Font
static bool woff(uint8_t *buf) {
	return buf[0] == 0x77 && buf[1] == 0x4F && buf[2] == 0x46 && buf[3] == 0x46 // WOFF
		&& buf[4] == 0x00 && buf[5] == 0x01 && buf[6] == 0x00 && buf[7] == 0x00;
}

// PNG Image
static bool png(uint8_t *buf) {
	return buf[0] == 0x89 && buf[1] == 0x50 && buf[2] == 0x4E && buf[3] == 0x47 && buf[4] == 0x0D && buf[5] == 0x0A && buf[6] == 0x1A && buf[7] == 0x0A;
}

// WebP Image
static bool webp(uint8_t *buf) {
	return buf[0] == 0x52 && buf[1] == 0x49 && buf[2] == 0x46 && buf[3] == 0x46  // RIFF
		&& buf[8] == 0x57 && buf[9] == 0x45 && buf[10] == 0x42 && buf[11] == 0x50; // WEBP
}

// HEIC Image
static bool heic(uint8_t *buf) {
	return buf[4] == 0x66 && buf[5] == 0x74 && buf[6] == 0x79 && buf[7] == 0x70    // ftyp
		&& buf[8] == 0x68 && buf[9] == 0x65 && buf[10] == 0x69 && buf[11] == 0x63; // heic
}

// AVIF Image
static bool avif(uint8_t *buf) {
	return buf[4] == 0x66 && buf[5] == 0x74 && buf[6] == 0x79 && buf[7] == 0x70    // ftyp
		&& buf[8] == 0x61 && buf[9] == 0x76 && buf[10] == 0x69 && buf[11] == 0x66; // avif
}

// JPEG Image
static bool jpeg(uint8_t *buf) {
	return buf[0] == 0xFF && buf[1] == 0xD8 && buf[2] == 0xFF;
}

// JPEG 2000 Image
static bool jpeg2(uint8_t *buf) {
	bool kp2 = buf[0] == 0xFF && buf[1] == 0x4F && buf[2] == 0xFF && buf[3] == 0x51;
	bool jp2 = buf[0] == 0x00 && buf[1] == 0x00 && buf[2] == 0x00 && buf[3] == 0x0C
		&& buf[4] == 0x6A && buf[5] == 0x50 && buf[6] == 0x20 && buf[7] == 0x20
		&& buf[8] == 0x0D && buf[9] == 0x0A && buf[10] == 0x87 && buf[11] == 0x0A;
	return jp2 || kp2;
}

// JPEG-XL Image
static bool jpgxl(uint8_t *buf) {
	bool kxl = buf[0] == 0xFF && buf[0] == 0x0A;
	bool jxl = buf[0] == 0x00 && buf[1] == 0x00 && buf[2] == 0x00 && buf[3] == 0x0C
		&& buf[4] == 0x4A && buf[5] == 0x58 && buf[6] == 0x4C && buf[7] == 0x20
		&& buf[8] == 0x0D && buf[9] == 0x0A && buf[10] == 0x87 && buf[11] == 0x0A;
	return jxl || kxl;
}

// JPEG-XS Image
static bool jpgxs(uint8_t *buf) {
	return buf[0] == 0xFF && buf[1] == 0x10 && buf[2] == 0xFF && buf[3] == 0x50;
}

// JPEG-XR Image
static bool jpgxr(uint8_t *buf) {
	return buf[0] == 0x49 && buf[1] == 0x49 && buf[2] == 0xBC && buf[3] == 0x01;
}

// QOI Image
static bool qoif(uint8_t *buf) {
	return buf[0] == 0x71 && buf[1] == 0x6F && buf[2] == 0x69 && buf[3] == 0x66; // qoif
}

// EXR Image
static bool exr(uint8_t *buf) {
	return buf[0] == 0x76 && buf[1] == 0x2F && buf[2] == 0x31 && buf[3] == 0x01; // v/1.
}

// Bitmap Image
static bool bmp(uint8_t *buf) {
	return buf[0] == 0x42 && buf[1] == 0x4D; // BM
}

// TIFF Image
static bool tiff(uint8_t *buf) {
	bool le = buf[0] == 0x49 && buf[1] == 0x49 && buf[2] == 0x2A && buf[3] == 0x00; // Little-Edian
	bool be = buf[0] == 0x4D && buf[1] == 0x4D && buf[2] == 0x00 && buf[3] == 0x2A; // Big-Endian
	return le || be;
}

/// @brief File Database
const struct FileTypeData fileTypeDb[FILEDBLEN] = {
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

// TODO: MAYBE add wrapper utils here, maybe not neccesary