/* Copyright (c) 2012, Kose Alexander
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by Kose Alexander.
 * 4. Neither the name of Kose Alexander nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY KOSE ALEXANDER ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL KOSE ALEXANDER BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "Endian.h"

#if defined _WIN32 || defined __CYGWIN__
#include "WiiFunction.h"
#endif
#include "../exception/ExcEndianUnbekanntesZeichen.h"

using namespace std;

void Endian::swap(short& s) {
#if defined _WIN32 || defined __CYGWIN__
	union {
		short s;
		unsigned char b[2];
	} dat1, dat2;

	dat1.s = s;
	dat2.b[0] = dat1.b[1];
	dat2.b[1] = dat1.b[0];
	s = dat2.s;
#endif
}

void Endian::swap(unsigned short& s) {
#if defined _WIN32 || defined __CYGWIN__
	union {
		u16 s;
		unsigned char b[2];
	} dat1, dat2;

	dat1.s = s;
	dat2.b[0] = dat1.b[1];
	dat2.b[1] = dat1.b[0];
	s = dat2.s;
#endif
}

void Endian::swap(wchar_t& c) {
#if defined _WIN32 || defined __CYGWIN__
	union {
		wchar_t c;
		unsigned char b[2];
	} dat1, dat2;

	dat1.c = c;
	dat2.b[0] = dat1.b[1];
	dat2.b[1] = dat1.b[0];
	c = dat2.c;
#endif
}

void Endian::swap(int& i) {
#if defined _WIN32 || defined __CYGWIN__
	union {
		int i;
		unsigned char b[4];
	} dat1, dat2;

	dat1.i = i;
	dat2.b[0] = dat1.b[3];
	dat2.b[1] = dat1.b[2];
	dat2.b[2] = dat1.b[1];
	dat2.b[3] = dat1.b[0];
	i = dat2.i;
#endif
}

void Endian::swap(float& f) {
#if defined _WIN32 || defined __CYGWIN__
	union {
		float f;
		unsigned char b[4];
	} dat1, dat2;

	dat1.f = f;
	dat2.b[0] = dat1.b[3];
	dat2.b[1] = dat1.b[2];
	dat2.b[2] = dat1.b[1];
	dat2.b[3] = dat1.b[0];
	f = dat2.f;
#endif
}

void Endian::swap(double& d) {
#if defined _WIN32 || defined __CYGWIN__
	union {
		double d;
		unsigned char b[8];
	} dat1, dat2;

	dat1.d = d;
	dat2.b[0] = dat1.b[7];
	dat2.b[1] = dat1.b[6];
	dat2.b[2] = dat1.b[5];
	dat2.b[3] = dat1.b[4];
	dat2.b[4] = dat1.b[3];
	dat2.b[5] = dat1.b[2];
	dat2.b[6] = dat1.b[1];
	dat2.b[7] = dat1.b[0];
	d = dat2.d;
#endif
}

void Endian::swap(long & l) {
#if defined _WIN32 || defined __CYGWIN__
	union {
		long l;
		unsigned char b[4];
	} dat1, dat2;

	dat1.l = l;
	dat2.b[0] = dat1.b[3];
	dat2.b[1] = dat1.b[2];
	dat2.b[2] = dat1.b[1];
	dat2.b[3] = dat1.b[0];
	l = dat2.l;
#endif
}

void Endian::swap(long long& l) {
#if defined _WIN32 || defined __CYGWIN__
	union {
		long long l;
		unsigned char b[8];
	} dat1, dat2;

	dat1.l = l;
	dat2.b[0] = dat1.b[7];
	dat2.b[1] = dat1.b[6];
	dat2.b[2] = dat1.b[5];
	dat2.b[3] = dat1.b[4];
	dat2.b[4] = dat1.b[3];
	dat2.b[5] = dat1.b[2];
	dat2.b[6] = dat1.b[1];
	dat2.b[7] = dat1.b[0];
	l = dat2.l;
#endif
}

wchar_t Endian::getSpezialChar(char c) {
	if ((unsigned) c == 0xffffff80) {
		return 0x20ac;
	} else if ((unsigned) c == 0xffffff82) {
		return 0x201a;
	} else if ((unsigned) c == 0xffffff83) {
		return 0x0192;
	} else if ((unsigned) c == 0xffffff84) {
		return 0x201e;
	} else if ((unsigned) c == 0xffffff85) {
		return 0x2026;
	} else if ((unsigned) c == 0xffffff86) {
		return 0x2020;
	} else if ((unsigned) c == 0xffffff87) {
		return 0x2021;
	} else if ((unsigned) c == 0xffffff88) {
		return 0x02c6;
	} else if ((unsigned) c == 0xffffff89) {
		return 0x2030;
	} else if ((unsigned) c == 0xffffff8a) {
		return 0x0160;
	} else if ((unsigned) c == 0xffffff8b) {
		return 0x2039;
	} else if ((unsigned) c == 0xffffff8c) {
		return 0x0152;
	} else if ((unsigned) c == 0xffffff8e) {
		return 0x017d;
	} else if ((unsigned) c == 0xffffff91) {
		return 0x2018;
	} else if ((unsigned) c == 0xffffff92) {
		return 0x2019;
	} else if ((unsigned) c == 0xffffff93) {
		return 0x201c;
	} else if ((unsigned) c == 0xffffff94) {
		return 0x201d;
	} else if ((unsigned) c == 0xffffff95) {
		return 0x2022;
	} else if ((unsigned) c == 0xffffff96) {
		return 0x2013;
	} else if ((unsigned) c == 0xffffff97) {
		return 0x2014;
	} else if ((unsigned) c == 0xffffff98) {
		return 0x02dc;
	} else if ((unsigned) c == 0xffffff99) {
		return 0x2122;
	} else if ((unsigned) c == 0xffffff9a) {
		return 0x0161;
	} else if ((unsigned) c == 0xffffff9b) {
		return 0x203a;
	} else if ((unsigned) c == 0xffffff9c) {
		return 0x0153;
	} else if ((unsigned) c == 0xffffff9e) {
		return 0x017e;
	} else if ((unsigned) c == 0xffffff9f) {
		return 0x0178;
	}

	return 0x0000;
}

char Endian::getSpezialChar(unsigned short c) {
	if (c == 0x20ac) {
		return 0x80;
	} else if (c == 0x201a) {
		return 0x82;
	} else if (c == 0x0192) {
		return 0x83;
	} else if (c == 0x201e) {
		return 0x84;
	} else if (c == 0x2026) {
		return 0x85;
	} else if (c == 0x2020) {
		return 0x86;
	} else if (c == 0x2021) {
		return 0x87;
	} else if (c == 0x02c6) {
		return 0x88;
	} else if (c == 0x2030) {
		return 0x89;
	} else if (c == 0x0160) {
		return 0x8a;
	} else if (c == 0x2039) {
		return 0x8b;
	} else if (c == 0x0152) {
		return 0x8c;
	} else if (c == 0x017d) {
		return 0x8e;
	} else if (c == 0x2018) {
		return 0x91;
	} else if (c == 0x2019) {
		return 0x92;
	} else if (c == 0x201c) {
		return 0x93;
	} else if (c == 0x201d) {
		return 0x94;
	} else if (c == 0x2022) {
		return 0x95;
	} else if (c == 0x2013) {
		return 0x96;
	} else if (c == 0x2014) {
		return 0x97;
	} else if (c == 0x02dc) {
		return 0x98;
	} else if (c == 0x2122) {
		return 0x99;
	} else if (c == 0x0161) {
		return 0x9a;
	} else if (c == 0x203a) {
		return 0x9b;
	} else if (c == 0x0153) {
		return 0x9c;
	} else if (c == 0x017e) {
		return 0x9e;
	} else if (c == 0x0178) {
		return 0x9f;
	} else {
		union {
			unsigned short c;
			char b[2];
		} dat;

		dat.c = c;
		throw ExcEndianUnbekanntesZeichen(dat.b[0], dat.b[1]);
	}
}
