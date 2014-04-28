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

#include "Paket36BlockAction.h"

#include <cstdio>
#include "../../net/DataInputStream.h"
#include "../../welt/Welt.h"
#include "../PaketManager.h"
#include "../../util/Debug.h"

using namespace std;

Paket36BlockAction::Paket36BlockAction() {
	PaketServer::id = 0x36;
	PaketServer::prio = 50;
}

PaketServer *Paket36BlockAction::gebeInstanz() {
	return new Paket36BlockAction();
}

bool Paket36BlockAction::registierePaket() {
	PaketManager::registrierePaket(new Paket36BlockAction());

	return true;
}

void Paket36BlockAction::lesePaketInhalt(DataInputStream *in) {
	this->x = in->leseInt();
	this->y = in->leseShort();
	this->z = in->leseInt();
	this->byte1 = in->leseByte();
	this->byte2 = in->leseByte();
}

void Paket36BlockAction::verarbeitePaket() {
	int chunkX;
	int chunkZ;
	Welt::berechneChunkPosition(this->x, this->z, chunkX, chunkZ);

	byte startX;
	byte startY;
	byte startZ;
	Welt::gebeWelt()->gebeChunkPos(this->x, this->y, this->z, startX, startY,
			startZ);

#ifdef DEBUG_ON
	short index = Welt::gebeWelt()->berechneIndex(startX, startY, startZ);

	char *buffer = new char[100];
	sprintf(buffer, "chunk: %ix%i, index: %i, b1: %x, b2: %x", chunkX, chunkZ,
			index, this->byte1, this->byte2);
	Debug::schreibePaketLog("Paket36BlockAction", buffer);
	delete[] buffer;
#endif

	// TODO Paketverarbeitung implementieren
}
