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

#include "Metadata.h"

#include <string>
#include <stdio.h>
#include "../net/DataInputStream.h"
#include "../exception/ExcMetadata.h"
#include "MetadataZeile.h"
#include "../util/Debug.h"

using namespace std;

Metadata *Metadata::leseDaten(DataInputStream *in) {
	map<byte, MetadataZeile *> _inhalt;

	byte x = in->leseByte();
	while (x != 127) {
		byte typ = (x & 0xe0) >> 5;
		byte index = x & 0x1f;

		switch (typ) {
		case 0:
			_inhalt[index] = new MetadataZeile(in->leseByte());
			break;
		case 1:
			_inhalt[index] = new MetadataZeile(in->leseShort());
			break;
		case 2:
			_inhalt[index] = new MetadataZeile(in->leseInt());
			break;
		case 3:
			_inhalt[index] = new MetadataZeile(in->leseFloat());
			break;
		case 4:
			_inhalt[index] = new MetadataZeile(in->leseString(64));
			break;
		case 5:
			_inhalt[index] = new MetadataZeile(in->leseShort(), in->leseByte(),
					in->leseShort());
			break;
		case 6:
			_inhalt[index] = new MetadataZeile(in->leseInt(), in->leseInt(),
					in->leseInt());
			break;
		default:
			throw ExcMetadata(typ);
		}

		x = in->leseByte();
	}

	return new Metadata(_inhalt);
}

Metadata::Metadata(map<byte, MetadataZeile *> _inhalt) {
	this->inhalt = _inhalt;
}

Metadata::~Metadata() {
	for (map<byte, MetadataZeile *>::iterator zeile = this->inhalt.begin();
			zeile != this->inhalt.end(); ++zeile) {
		delete zeile->second;
	}

	this->inhalt.clear();
}
