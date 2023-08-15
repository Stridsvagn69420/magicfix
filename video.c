#include "video.h"

enum MagicResult magicfix_webm(uint8_t *buf) {
	if (BUFLEN(buf) > 3) {
		return
			!(buf[0] == 0x1A    // .
			&& buf[1] == 0x45   // E
			&& buf[2] == 0xDF   // .
			&& buf[3] == 0xA3); // .
	} else {
		return MagicBuffErr;
	}
}

enum MagicResult magicfix_avi(uint8_t *buf) {
	if (BUFLEN(buf) > 10) {
		return
			!(buf[0] == 0x52     // R
			&& buf[1] == 0x49    // I
			&& buf[2] == 0x46    // F
			&& buf[3] == 0x46    // F
			&& buf[8] == 0x41    // A
			&& buf[9] == 0x56    // V
			&& buf[10] == 0x49); // I
	} else {
		return MagicBuffErr;
	}
}

enum MagicResult magicfix_flv(uint8_t *buf) {
	if (BUFLEN(buf) > 2) {
		return
			!(buf[0] == 0x46    // F
			&& buf[1] == 0x4C   // L
			&& buf[2] == 0x56); // V
	} else {
		return MagicBuffErr;
	}
}

enum MagicResult magicfix_mpeg(uint8_t *buf) {
	if (BUFLEN(buf) > 3) {
		return
			!(buf[0] == 0x00    // NULL
			&& buf[1] == 0x00   // NULL
			&& buf[2] == 0x01   // .
			&& buf[3] >= 0xB0 && buf[3] <= 0xBF); // Range from B0 to BF
	} else {
		return MagicBuffErr;
	}
}

enum MagicResult magicfix_mp4(uint8_t *buf) {
	if (BUFLEN(buf) > 11) {
		return
			!(buf[4] == 0x66    // f
			&& buf[5] == 0x74   // t
			&& buf[6] == 0x79   // y
			&& buf[7] >= 0x70   // p
			&& (
				buf[8] == 0x61 && buf[9] == 0x76 && buf[10] == 0x63 && buf[11] == 0x31    // avc1
				|| buf[8] == 0x64 && buf[9] == 0x61 && buf[10] == 0x73 && buf[11] == 0x68 // dash
				|| buf[8] == 0x69 && buf[9] == 0x73 && buf[10] == 0x6F && buf[11] == 0x6D // isom
				|| buf[8] == 0x6D && buf[9] == 0x70 && buf[10] == 0x34 && buf[11] == 0x32 // mp42
				|| buf[8] == 0x6D && buf[9] == 0x70 && buf[10] == 0x37 && buf[11] == 0x31 // mp71
				|| buf[8] == 0x6D && buf[9] == 0x6D && buf[10] == 0x70 && buf[11] == 0x34 // mmp4
				|| buf[8] == 0x69 && buf[9] == 0x73 && buf[10] == 0x6F && buf[11] == 0x32 // iso2
				|| buf[8] == 0x69 && buf[9] == 0x73 && buf[10] == 0x6F && buf[11] == 0x33 // iso3
				|| buf[8] == 0x69 && buf[9] == 0x73 && buf[10] == 0x6F && buf[11] == 0x34 // iso4
				|| buf[8] == 0x69 && buf[9] == 0x73 && buf[10] == 0x6F && buf[11] == 0x35 // iso5
				|| buf[8] == 0x69 && buf[9] == 0x73 && buf[10] == 0x6F && buf[11] == 0x36 // iso6
				|| buf[8] == 0x6D && buf[9] == 0x70 && buf[10] == 0x34 && buf[11] == 0x76 // mp4v
				|| buf[8] == 0x6D && buf[9] == 0x73 && buf[10] == 0x6E && buf[11] == 0x76 // msnv
			)); 
	} else {
		return MagicBuffErr;
	}
}