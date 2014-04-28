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

#include "MetadataZeile.h"

using namespace std;

MetadataZeile::MetadataZeile(byte wert1) {
	this->typ = 0;

	this->typ0 = wert1;
}

MetadataZeile::MetadataZeile(short wert1) {
	this->typ = 1;

	this->typ1 = wert1;
}

MetadataZeile::MetadataZeile(int wert1) {
	this->typ = 2;

	this->typ2 = wert1;
}

MetadataZeile::MetadataZeile(float wert1) {
	this->typ = 3;

	this->typ3 = wert1;
}

MetadataZeile::MetadataZeile(string wert1) {
	this->typ = 4;

	this->typ4 = wert1;
}

MetadataZeile::MetadataZeile(short wert1, byte wert2, short wert3) {
	this->typ = 5;

	this->typ5a = wert1;
	this->typ5b = wert2;
	this->typ5c = wert3;
}

MetadataZeile::MetadataZeile(int wert1, int wert2, int wert3) {
	this->typ = 6;

	this->typ6a = wert1;
	this->typ6b = wert2;
	this->typ6c = wert3;
}
