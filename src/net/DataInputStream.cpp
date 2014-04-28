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

#include "DataInputStream.h"

#include <cstdlib>
#include "Socket.h"
#include "../util/Endian.h"
#include "../exception/ExcSocketStringLaengeUeberschritten.h"

using namespace std;

DataInputStream::DataInputStream(Socket * _socket) {
	this->socket = _socket;
}

DataInputStream::~DataInputStream() {
}

bool DataInputStream::leseBoolean() {
	bool read;

	this->socket->read(&read, sizeof(bool));

	return read;
}

byte DataInputStream::leseByte() {
	byte read;

	this->socket->read(&read, sizeof(byte));

	return read;
}

byte * DataInputStream::leseBytes(int anzahl) {
	byte *read = new byte[anzahl];

	for (int i = 0; i < anzahl; i++) {
		this->socket->read(&read[i], sizeof(byte));
	}

	return read;
}

char DataInputStream::leseChar() {
	unsigned short schar;

	this->socket->read(&schar, sizeof(unsigned short));

	union {
		unsigned short s;
		char b[2];
	} dat;

	dat.s = schar;

	if (dat.b[0] > 0) {
		return Endian::getSpezialChar(schar);
	} else {
#if defined _WIN32 || defined __CYGWIN__
		dat.b[0] = dat.b[1];
		dat.b[1] = 0x00;
#endif
		return dat.s;
	}
}

double DataInputStream::leseDouble() {
	double read;

	this->socket->read(&read, sizeof(double));

	Endian::swap(read);
	return read;
}

float DataInputStream::leseFloat() {
	float read;

	this->socket->read(&read, sizeof(float));

	Endian::swap(read);
	return read;
}

byte *DataInputStream::leseKomplett(int laenge) {
	byte *read = new byte[laenge];

	read = this->leseBytes(laenge);

	return read;
}

int DataInputStream::leseInt() {
	int read;

	this->socket->read(&read, sizeof(int));

	Endian::swap(read);
	return read;
}

long long DataInputStream::leseLong() {
	long long read;

	this->socket->read(&read, sizeof(long long));

	Endian::swap(read);
	return read;
}

short DataInputStream::leseShort() {
	short read;

	this->socket->read(&read, sizeof(short));

	Endian::swap(read);
	return (long) read;
}

string DataInputStream::leseString(int maxLaenge) {
	string ret;
	short laenge = this->leseShort();

	if (laenge > maxLaenge) {
		throw ExcSocketStringLaengeUeberschritten(laenge, maxLaenge);
	}

	for (short i = 0; i < laenge; i++) {
		string s(1, this->leseChar());
		ret.append(s);
	}
	return ret;
}
