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

#include "Paket3CExplosion.h"

#include <cstdio>
#include "../../net/DataInputStream.h"
#include "../PaketManager.h"
#include "../../util/Debug.h"

using namespace std;

Paket3CExplosion::Paket3CExplosion() {
	PaketServer::id = 0x3c;
	PaketServer::prio = 50;
}

Paket3CExplosion::~Paket3CExplosion() {
	delete[] this->records;
}

PaketServer *Paket3CExplosion::gebeInstanz() {
	return new Paket3CExplosion();
}

bool Paket3CExplosion::registierePaket() {
	PaketManager::registrierePaket(new Paket3CExplosion());

	return true;
}

void Paket3CExplosion::lesePaketInhalt(DataInputStream *in) {
	this->x = in->leseDouble();
	this->y = in->leseDouble();
	this->z = in->leseDouble();
	this->unknown = in->leseFloat();
	this->recordCount = in->leseInt();

	this->records = new byte[this->recordCount * 3];

	for (int i = 0; i < recordCount; i++) {
		int row = (i * 3);
		this->records[row] = in->leseByte();
		this->records[row + 1] = in->leseByte();
		this->records[row + 2] = in->leseByte();
	}
}

void Paket3CExplosion::verarbeitePaket() {
#ifdef DEBUG_ON
	char *buffer = new char[100];
	sprintf(buffer, "x: %f, y: %f, z: %f, unknown: %f, recordCount: %i",
			this->x, this->y, this->z, this->unknown, this->recordCount);
	Debug::schreibePaketLog("Paket3CExplosion", buffer);
	delete[] buffer;
#endif

	// TODO Paketverarbeitung implementieren
}
