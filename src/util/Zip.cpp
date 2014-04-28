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

// Beispiel von http://stackoverflow.com/questions/7540259/deflate-and-inflate-zlib-h-in-c
#include "Zip.h"

#include <zlib.h>
#include <cstdlib>
#include <cstring>

using namespace std;

byte *Zip::entpacken(byte *quelle, int quellelaenge, int &ziellaenge) {
	byte *ziel = new byte[ziellaenge];

	z_stream infstream;
	infstream.zalloc = Z_NULL;
	infstream.zfree = Z_NULL;
	infstream.opaque = Z_NULL;
	infstream.avail_in = (uInt) quellelaenge;
	infstream.next_in = (Bytef *) quelle;
	infstream.avail_out = ziellaenge;
	infstream.next_out = (Bytef *) ziel;

	inflateInit(&infstream);
	inflate(&infstream, Z_NO_FLUSH);
	inflateEnd(&infstream);

	ziellaenge = ((byte *) infstream.next_out) - ziel;

	return ziel;
}

byte *Zip::packen(byte *quelle, int quellelaenge, int &ziellaenge) {
	byte *tmpziel = new byte[quellelaenge];

	z_stream defstream;
	defstream.zalloc = Z_NULL;
	defstream.zfree = Z_NULL;
	defstream.opaque = Z_NULL;
	defstream.avail_in = (uInt) quellelaenge + 1;
	defstream.next_in = (Bytef *) quelle;
	defstream.avail_out = (uInt) quellelaenge;
	defstream.next_out = (Bytef *) tmpziel;

	deflateInit(&defstream, Z_DEFAULT_COMPRESSION);
	deflate(&defstream, Z_FINISH);
	deflateEnd(&defstream);

	ziellaenge = ((byte *) defstream.next_out) - tmpziel;

	byte *ziel = new byte[ziellaenge];

	memcpy(ziel, tmpziel, ziellaenge);
	delete[] tmpziel;

	return ziel;
}
