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

#include "DataOutputStream.h"

#include <cstring>
#include "Socket.h"
#include "../util/Endian.h"

using namespace std;

DataOutputStream::DataOutputStream(Socket * _socket) {
	this->socket = _socket;
}

DataOutputStream::~DataOutputStream() {
}

void DataOutputStream::schreibeBoolean(bool b) {
	this->socket->write(&b, sizeof(b));
}

void DataOutputStream::schreibeByte(byte b) {
	this->socket->write(&b, sizeof(b));
}

void DataOutputStream::schreibeBytes(char *b) {
	for (unsigned int i = 0; i < strlen(b); i++) {
		this->schreibeByte(b[i]);
	}
}

void DataOutputStream::schreibeChar(char c) {
	wchar_t t = Endian::getSpezialChar(c);
	if (t == 0x0000) {
#if defined _WIN32 || defined __CYGWIN__
		union {
			wchar_t t;
			unsigned char b[2];
		} dat;

		dat.b[0] = c;
		dat.b[1] = 0x00;
#else
		union {
			wchar_t t;
			unsigned char b[4];
		} dat;

		dat.b[0] = 0x00;
		dat.b[1] = 0x00;
		dat.b[2] = 0x00;
		dat.b[3] = c;
#endif
		t = dat.t;
	}
	Endian::swap(t);

	union {
		wchar_t t;
		unsigned char b[4];
	} dat;

	dat.t = t;
#if defined _WIN32 || defined __CYGWIN__
	// unter Win ist wchar_t 2 Byte lang
	this->socket->write(&dat.b[0], sizeof(dat.b[0]));
	this->socket->write(&dat.b[1], sizeof(dat.b[1]));
#else
	// bei der Wii ist wchar_t 4 Byte lang
	this->socket->write(&dat.b[2], sizeof(dat.b[2]));
	this->socket->write(&dat.b[3], sizeof(dat.b[3]));
#endif
}

void DataOutputStream::schreibeChars(string s) {
	const char * c = s.c_str();
	for (unsigned int n = 0; n < s.length(); n++) {
		this->schreibeChar(c[n]);
	}
}

void DataOutputStream::schreibeDouble(double d) {
	Endian::swap(d);
	this->socket->write(&d, sizeof(d));
}

void DataOutputStream::schreibeFloat(float f) {
	Endian::swap(f);
	this->socket->write(&f, sizeof(f));
}

void DataOutputStream::schreibeInt(int i) {
	Endian::swap(i);
	this->socket->write(&i, sizeof(i));
}

void DataOutputStream::schreibeLong(long long l) {
	Endian::swap(l);
	this->socket->write(&l, sizeof(l));
}

void DataOutputStream::schreibeShort(short s) {
	Endian::swap(s);
	this->socket->write(&s, sizeof(s));
}

void DataOutputStream::schreibeString(string s) {
	this->schreibeShort((short) s.length());
	this->schreibeChars(s);
}
