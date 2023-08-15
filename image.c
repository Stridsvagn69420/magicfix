#include "image.h"

enum MagicResult magicfix_exr(uint8_t *buf) {
	if (BUFLEN(buf) > 3) {
		return
			!(buf[0] == 0x76    // v
			&& buf[1] == 0x2F   // /
			&& buf[2] == 0x31   // 1
			&& buf[3] == 0x01); // .
	} else {
		return MagicBuffErr;
	}
}

enum MagicResult magicfix_png(uint8_t *buf) {
	if (BUFLEN(buf) > 7) {
		return
			!(buf[0] == 0x89    // .
			&& buf[1] == 0x50   // P
			&& buf[2] == 0x4E   // N
			&& buf[3] == 0x47   // G
			&& buf[4] == 0x0D   // .
			&& buf[5] == 0x0A   // .
			&& buf[6] == 0x1A   // .
			&& buf[7] == 0x0A); // .
	} else {
		return MagicBuffErr;
	}
}

enum MagicResult magicfix_webp(uint8_t *buf) {
	if (BUFLEN(buf) > 7) {
		return
			!(buf[0] == 0x52    // R
			&& buf[1] == 0x49   // I
			&& buf[2] == 0x46   // F
			&& buf[3] == 0x46   // F
			&& buf[4] == 0x57   // W
			&& buf[5] == 0x45   // E
			&& buf[6] == 0x42   // B
			&& buf[7] == 0x50); // P
	} else {
		return MagicBuffErr;
	}
}

enum MagicResult magicfix_bmp(uint8_t *buf) {
	if (BUFLEN(buf) > 1) {
		return !(buf[0] == 0x42 // B
			&& buf[1] == 0x4D); // M
	} else {
		return MagicBuffErr;
	}
}

enum MagicResult magicfix_tiff(uint8_t *buf) {
	if (BUFLEN(buf) > 3) {
		bool le = buf[0] == 0x49 && buf[1] == 0x49 && buf[2] == 0x2A && buf[3] == 0x00; // Little-Edian
		bool be = buf[0] == 0x4D && buf[1] == 0x4D && buf[2] == 0x00 && buf[3] == 0x2A; // Big-Endian
		return !(le || be);
	} else {
		return MagicBuffErr;
	}
}