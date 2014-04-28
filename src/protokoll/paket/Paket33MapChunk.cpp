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

#include "Paket33MapChunk.h"

#include <cstdio>
#include <cstdlib>
#include "../../net/DataInputStream.h"
#include "../../welt/Welt.h"
#include "../../welt/KomprimierteChunkDaten.h"
#include "../PaketManager.h"
#include "../../util/Debug.h"

using namespace std;

Paket33MapChunk::Paket33MapChunk() {
	PaketServer::id = 0x33;
	PaketServer::prio = 50;
}

PaketServer *Paket33MapChunk::gebeInstanz() {
	return new Paket33MapChunk();
}

bool Paket33MapChunk::registierePaket() {
	PaketManager::registrierePaket(new Paket33MapChunk());

	return true;
}

void Paket33MapChunk::lesePaketInhalt(DataInputStream *in) {
	this->chunkX = in->leseInt();
	this->chunkZ = in->leseInt();
	this->groundUpContiguous = in->leseBoolean();
	this->primaryBitMap = in->leseShort();
	this->addBitMap = in->leseShort();
	this->compressedSize = in->leseInt();
	in->leseInt();
	this->compressedData = in->leseKomplett(this->compressedSize);
}

void Paket33MapChunk::verarbeitePaket() {
	int chunkTeile = 0;
	for (int j = 0; j < 16; j++) {
		chunkTeile += this->primaryBitMap >> j & 1;
	}

#ifdef DEBUG_ON
	char *buffer = new char[1000];
	sprintf(
			buffer,
			"chunk: %ix%i, groundUpContiguous: %i, primaryBitMap: %i, addBitMap: %i, compressedSize: %i, chunkTeile: %i",
			this->chunkX, this->chunkZ, this->groundUpContiguous,
			this->primaryBitMap, this->addBitMap, this->compressedSize,
			chunkTeile);
	Debug::schreibePaketLog("Paket33MapChunk", buffer);
	delete[] buffer;
#endif

	KomprimierteChunkDaten * k = new KomprimierteChunkDaten(
			this->compressedData, this->compressedSize, this->primaryBitMap,
			this->groundUpContiguous);
	Welt::gebeWelt()->ergaenzeKomprimierteDaten(chunkX, chunkZ, k);
}
