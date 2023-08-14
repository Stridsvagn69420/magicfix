#include "audio.h"

enum MagicResult magicfix_aiff(char *buf) {
	if (BUFLEN(buf) > 11) {
		return 
			!(buf[0] == 0x46     // F
			&& buf[1] == 0x4F    // O
			&& buf[2] == 0x52    // R
			&& buf[3] == 0x4D    // M
			&& buf[8] == 0x41    // A
			&& buf[9] == 0x49    // I
			&& buf[10] == 0x46   // F
			&& buf[11] == 0x46); // F
	} else {
		return MagicBuffErr;
	}	
}

enum MagicResult magicfix_wav(char *buf) {
	if (BUFLEN(buf) > 11) {
		return
			!(buf[0] == 0x52     // R
			&& buf[1] == 0x49    // I
			&& buf[2] == 0x46    // F
			&& buf[3] == 0x46    // F
			&& buf[8] == 0x57    // W
			&& buf[9] == 0x41    // A
			&& buf[10] == 0x56   // v
			&& buf[11] == 0x45); // E
	} else {
		return MagicBuffErr;
	}
}

enum MagicResult magicfix_flac(char *buf) {
	if (BUFLEN(buf) > 3) {
		return
			!(buf[0] == 0x66    // f
			&& buf[1] == 0x4C   // L
			&& buf[2] == 0x61   // a
			&& buf[3] == 0x43); // C
	} else {
		return MagicBuffErr;
	}
}

enum MagicResult magicfix_ogg(char *buf) {
	if (BUFLEN(buf) > 3) {
		return
			!(buf[0] == 0x4F    // O
			&& buf[1] == 0x67   // g
			&& buf[2] == 0x67   // g
			&& buf[3] == 0x53); // S
	} else {
		return MagicBuffErr;
	}
}

enum MagicResult magicfix_oggopus(char *buf) {
	if (BUFLEN(buf) > 35) {
		return
			!(buf[0] == 0x4F     // O
			&& buf[1] == 0x67    // g
			&& buf[2] == 0x67    // g
			&& buf[3] == 0x53    // S
			&& buf[28] == 0x4F   // O
			&& buf[29] == 0x70   // p
			&& buf[30] == 0x75   // u
			&& buf[31] == 0x73   // s
			&& buf[32] == 0x48   // H
			&& buf[33] == 0x65   // e
			&& buf[34] == 0x61   // a
			&& buf[35] == 0x64); // d
	} else {
		return MagicBuffErr;
	}
}

enum MagicResult magicfix_midi(char *buf) {
	if (BUFLEN(buf) > 3) {
		return
			!(buf[0] == 0x4F    // O
			&& buf[1] == 0x67   // g
			&& buf[2] == 0x67   // g
			&& buf[3] == 0x53); // S
	} else {
		return MagicBuffErr;
	}
}

enum MagicResult magicfix_mp3(char *buf) {
	if (BUFLEN(buf) > 2) {
		bool id3 = buf[0] == 0x49 && buf[1] == 0x44 && buf[2] == 0x33; // ID3v2
		bool mp3 = buf[0] == 0xFF && (buf[1] == 0xFB || buf[1] == 0xF3 || buf[1] == 0xF2); // No ID3 or ID3v1
		return !(id3 || mp3);
	} else {
		return MagicBuffErr;
	}
}