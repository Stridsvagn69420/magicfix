#include "font.h"

enum MagicResult magicfix_woff(char *buf) {
	if (BUFLEN(buf) > 7) {
		return
			!(buf[0] == 0x77    // w
			&& buf[1] == 0x4F   // O
			&& buf[2] == 0x46   // F
			&& buf[3] == 0x46   // F
			&& buf[4] == 0x00   // NULL
			&& buf[5] == 0x01   // .
			&& buf[6] == 0x00   // NULL
			&& buf[7] == 0x00); // NULL
	} else {
		return MagicBuffErr;
	}
}

enum MagicResult magicfix_woff2(char *buf) {
	if (BUFLEN(buf) > 7) {
		return
			!(buf[0] == 0x77    // w
			&& buf[1] == 0x4F   // O
			&& buf[2] == 0x46   // F
			&& buf[3] == 0x32   // 2
			&& buf[4] == 0x00   // NULL
			&& buf[5] == 0x01   // .
			&& buf[6] == 0x00   // NULL
			&& buf[7] == 0x00); // NULL
	} else {
		return MagicBuffErr;
	}
}

enum MagicResult magicfix_ttf(char *buf) {
	if (BUFLEN(buf) > 4) {
		return
			!(buf[0] == 0x00    // NULL
			&& buf[1] == 0x01   // .
			&& buf[2] == 0x00   // NULL
			&& buf[3] == 0x00   // NULL
			&& buf[4] == 0x00); // NULL
	} else {
		return MagicBuffErr;
	}
}

enum MagicResult magicfix_otf(char *buf) {
	if (BUFLEN(buf) > 4) {
		return
			!(buf[0] == 0x4F    // O
			&& buf[1] == 0x54   // T
			&& buf[2] == 0x54   // T
			&& buf[3] == 0x4F   // O
			&& buf[4] == 0x00); // NULL
	} else {
		return MagicBuffErr;
	}
}