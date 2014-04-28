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

#include "Chunk.h"

#include <cstring>
#include <string.h>
#include "KomprimierteChunkDaten.h"
#include "BlockAenderung.h"
#include "ChunkLaden.h"
#include "Welt.h"

using namespace std;

Chunk::Chunk(int _x, int _z) {
	this->x = _x;
	this->z = _z;
	this->geladen = false;
	this->initialisiert = false;
	this->version = 0;

	pthread_mutex_init(&this->mutexKomprimierteDaten, NULL);
	pthread_mutex_init(&this->mutexBlockAenderungen, NULL);
	pthread_mutex_init(&this->mutexGeladen, NULL);
	pthread_mutex_init(&this->mutexDaten, NULL);
	pthread_mutex_init(&this->mutexIndex, NULL);

	ChunkLaden::gebeChunkLaden()->fuegeChunkHinzu(this);
}

Chunk::~Chunk() {
	ChunkLaden::gebeChunkLaden()->loescheChunk(this);

	pthread_mutex_destroy(&this->mutexKomprimierteDaten);
	pthread_mutex_destroy(&this->mutexBlockAenderungen);
	pthread_mutex_destroy(&this->mutexGeladen);
	pthread_mutex_destroy(&this->mutexDaten);
	pthread_mutex_destroy(&this->mutexIndex);

	for (unsigned int i = 0; i < this->komprimierteDaten.size(); i++) {
		delete this->komprimierteDaten.at(i);
	}

	while (this->blockAenderungen.size() > 0) {
		delete this->blockAenderungen.front();
		this->blockAenderungen.pop_front();
	}

	if (this->initialisiert) {
		delete[] this->bloeckeTyp;
		delete[] this->bloeckeMeta;
		delete[] this->bloeckeLicht;
		delete[] this->bloeckeHimmelLicht;
	}
}

bool Chunk::istGeladen() {
	pthread_mutex_lock(&this->mutexGeladen);
	bool _geladen = this->geladen;
	pthread_mutex_unlock(&this->mutexGeladen);

	return _geladen;
}

void Chunk::ergaenzeKomprimierteDaten(
		KomprimierteChunkDaten *_komprimierteDaten) {
	pthread_mutex_lock(&this->mutexKomprimierteDaten);
	this->komprimierteDaten.push_back(_komprimierteDaten);
	pthread_mutex_unlock(&this->mutexKomprimierteDaten);
}

void Chunk::ergaenzeBlockAenderung(BlockAenderung *_blockAenderung) {
	pthread_mutex_lock(&this->mutexBlockAenderungen);
	this->blockAenderungen.push_front(_blockAenderung);
	this->blockAenderungen.unique(BlockAenderung::Vergleicher);
	pthread_mutex_unlock(&this->mutexBlockAenderungen);
}

void Chunk::ladeChunk() {
	bool datenGefunden = false;

	pthread_mutex_lock(&this->mutexGeladen);
	if (!this->initialisiert) {
		int datenmenge = Welt::gebeWelt()->gebeWeltHoehe() * 16 * 16;

		this->bloeckeTyp = new short[datenmenge];
		this->bloeckeMeta = new byte[datenmenge];
		this->bloeckeLicht = new byte[datenmenge];
		this->bloeckeHimmelLicht = new byte[datenmenge];

		memset(this->bloeckeTyp, 0, datenmenge * sizeof(short));
		memset(this->bloeckeMeta, 0, datenmenge * sizeof(byte));
		memset(this->bloeckeLicht, 0, datenmenge * sizeof(byte));
		memset(this->bloeckeHimmelLicht, 0, datenmenge * sizeof(byte));

		this->initialisiert = true;
	}
	pthread_mutex_unlock(&this->mutexGeladen);

	// gezippten Chunk oeffnen
	pthread_mutex_lock(&this->mutexKomprimierteDaten);
	if (this->komprimierteDaten.size() > 0) {
		datenGefunden = true;
	}

	for (unsigned int i = 0; i < this->komprimierteDaten.size(); i++) {
		KomprimierteChunkDaten *k = this->komprimierteDaten.front();
		this->komprimierteDaten.erase(this->komprimierteDaten.begin());

		pthread_mutex_lock(&this->mutexDaten);
		k->ladeDaten(this->bloeckeTyp, this->bloeckeMeta, this->bloeckeLicht,
				this->bloeckeHimmelLicht);
		pthread_mutex_unlock(&this->mutexDaten);
		delete k;
	}
	pthread_mutex_unlock(&this->mutexKomprimierteDaten);

	// wartende Changes verarbeiten
	pthread_mutex_lock(&this->mutexBlockAenderungen);
	if (this->blockAenderungen.size() > 0) {
		datenGefunden = true;
	}

	while (this->blockAenderungen.size() > 0) {
		BlockAenderung *b = this->blockAenderungen.front();
		this->blockAenderungen.pop_front();

		pthread_mutex_lock(&this->mutexDaten);
		b->aendereDaten(this->bloeckeTyp, this->bloeckeMeta, this->bloeckeLicht,
				this->bloeckeHimmelLicht);
		pthread_mutex_unlock(&this->mutexDaten);
		delete b;
	}
	pthread_mutex_unlock(&this->mutexBlockAenderungen);

	if (datenGefunden) {
		this->version++;

		pthread_mutex_lock(&this->mutexGeladen);
		if (!this->geladen) {
			this->geladen = true;

			Welt::gebeWelt()->setzeChunkGeladen(this->gebeX(), this->gebeZ(),
					true);
		}
		pthread_mutex_unlock(&this->mutexGeladen);
	}
}

void Chunk::speichereChunk() {
	// TODO: aktuellen Chunk zippen

	pthread_mutex_lock(&this->mutexGeladen);

	this->geladen = false;
	Welt::gebeWelt()->setzeChunkGeladen(this->gebeX(), this->gebeZ(), false);

	pthread_mutex_lock(&this->mutexDaten);
	if (this->initialisiert) {
		delete[] this->bloeckeTyp;
		delete[] this->bloeckeMeta;
		delete[] this->bloeckeLicht;
		delete[] this->bloeckeHimmelLicht;
	}
	pthread_mutex_unlock(&this->mutexDaten);

	this->initialisiert = false;
	pthread_mutex_unlock(&this->mutexGeladen);
}

int Chunk::gebeX() {
	return this->x;
}

int Chunk::gebeZ() {
	return this->z;
}

unsigned long Chunk::gebeVersionsNummer() {
	return this->version;
}

void Chunk::kopiereDaten(short *_bloeckeTyp, byte *_bloeckeMeta,
		byte *_bloeckeLicht, byte *_bloeckeHimmelLicht) {

	int datenmenge = Welt::gebeWelt()->gebeWeltHoehe() * 16 * 16;

	memcpy(_bloeckeTyp, this->bloeckeTyp, datenmenge * sizeof(short));
	memcpy(_bloeckeMeta, this->bloeckeMeta, datenmenge * sizeof(byte));
	memcpy(_bloeckeLicht, this->bloeckeLicht, datenmenge * sizeof(byte));
	memcpy(_bloeckeHimmelLicht, this->bloeckeHimmelLicht,
			datenmenge * sizeof(byte));
}
