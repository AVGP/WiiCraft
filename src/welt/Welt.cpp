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

#include "Welt.h"

#include <sstream>
#include <math.h>
#include <cstddef>
#include "Chunk.h"
#include "ChunkCacheManager.h"

using namespace std;

Welt *Welt::welt = NULL;

void Welt::berechneChunkPosition(int x, int z, int &chunkX, int &chunkZ) {
	chunkX = x >> 4;
	chunkZ = z >> 4;
}

void Welt::gebeChunkPos(int x, int y, int z, byte &xP, byte &yP, byte &zP) {
	xP = x & 15;
	yP = y & (this->gebeWeltHoehe() - 1);
	zP = z & 15;
}

unsigned short Welt::berechneIndex(int x, int y, int z) {
	short _weltHoehe = this->gebeWeltHoehe();
	return y + (z * _weltHoehe) + (x * _weltHoehe * 16);
}

void Welt::berechnePosAusIndex(unsigned short index, int &x, int &y, int &z) {
	short _weltHoehe = this->gebeWeltHoehe();
	x = (index - (index % (_weltHoehe * 16))) / (_weltHoehe * 16);
	z = ((index - (index % _weltHoehe)) / _weltHoehe) - (x * 16);
	y = index - (z * _weltHoehe) - (x * _weltHoehe * 16);
}

void Welt::initialisiereWelt(int dimension, string levelTyp,
		byte schwierigkeitsGrad, int serverModus, unsigned short weltHoehe) {
	if (Welt::welt != NULL) {
		delete Welt::welt;
	}

	Welt::welt = new Welt(dimension, levelTyp, schwierigkeitsGrad, serverModus,
			weltHoehe);
}

Welt *Welt::gebeWelt() {
	return Welt::welt;
}

Welt::Welt(int _dimension, string _levelTyp, byte _schwierigkeitsGrad,
		int _serverModus, unsigned short _weltHoehe) {

	pthread_mutex_init(&this->mutexChunks, NULL);
	pthread_mutex_init(&this->mutexGeladeneChunks, NULL);
	pthread_mutex_init(&this->mutexUhrzeit, NULL);
	pthread_mutex_init(&this->mutexWelthoehe, NULL);

	this->uhrzeit = 0;
	this->dimension = _dimension;
	this->schwierigkeitsGrad = _schwierigkeitsGrad;
	this->serverModus = _serverModus;

	this->regen = false;

	this->kompassPosition.x = 0;
	this->kompassPosition.y = 0;
	this->kompassPosition.z = 0;

	this->chunkCacheManager = new ChunkCacheManager();

	// TODO wird von Mojang noch nicht ausgewertet
	pthread_mutex_lock(&this->mutexWelthoehe);
	this->weltHoehe = 256;
	if (_weltHoehe != 0) {
		this->weltHoehe = _weltHoehe;
	}
	pthread_mutex_unlock(&this->mutexWelthoehe);
}

Welt::~Welt() {
	pthread_mutex_destroy(&this->mutexChunks);
	pthread_mutex_destroy(&this->mutexGeladeneChunks);
	pthread_mutex_destroy(&this->mutexUhrzeit);
	pthread_mutex_destroy(&this->mutexWelthoehe);

	for (map<int, map<int, Chunk *> >::iterator x = this->chunks.begin();
			x != this->chunks.end(); ++x) {
		map<int, Chunk *> currentValue = x->second;

		for (map<int, Chunk *>::iterator z = currentValue.begin();
				z != currentValue.end(); ++z) {
			delete z->second;
		}
	}

	this->chunks.clear();
	this->geladeneChunks.clear();
}

void Welt::initialisiereChunk(int x, int z) {
	pthread_mutex_lock(&this->mutexChunks);
	this->chunks[x][z] = new Chunk(x, z);
	pthread_mutex_unlock(&this->mutexChunks);
}

void Welt::loescheChunk(int x, int z) {
	pthread_mutex_lock(&this->mutexGeladeneChunks);
	if (this->geladeneChunks.count(x) > 0
			&& this->geladeneChunks[x].count(z) > 0) {
		this->geladeneChunks[x].erase(z);
	}
	pthread_mutex_unlock(&this->mutexGeladeneChunks);

	pthread_mutex_lock(&this->mutexChunks);
	if (this->chunks.count(x) > 0 && this->chunks[x].count(z) > 0) {
		Chunk * c = this->chunks[x][z];
		this->chunks[x].erase(z);
		delete c;
	}
	pthread_mutex_unlock(&this->mutexChunks);
}

void Welt::setzeChunkGeladen(int x, int z, bool laden) {
	if (laden) {
		pthread_mutex_lock(&this->mutexChunks);
		if (this->chunks.count(x) > 0 && this->chunks[x].count(z) > 0) {
			pthread_mutex_lock(&this->mutexGeladeneChunks);
			this->geladeneChunks[x][z] = this->chunks[x][z];
			pthread_mutex_unlock(&this->mutexGeladeneChunks);

			this->chunkCacheManager->fuegeChunkHinzu(this->chunks[x][z]);
		}
		pthread_mutex_unlock(&this->mutexChunks);
	} else {
		pthread_mutex_lock(&this->mutexGeladeneChunks);
		if (this->geladeneChunks.count(x) > 0
				&& this->geladeneChunks[x].count(z) > 0) {
			this->chunkCacheManager->loescheChunk(this->geladeneChunks[x][z]);

			this->geladeneChunks[x].erase(z);
		}
		pthread_mutex_unlock(&this->mutexGeladeneChunks);
	}
}

bool Welt::istChunkGeladen(int x, int z) {
	bool geladen = false;
	pthread_mutex_lock(&this->mutexGeladeneChunks);
	if (this->geladeneChunks.count(x) > 0
			&& this->geladeneChunks[x].count(z) > 0) {
		geladen = true;
	}
	pthread_mutex_unlock(&this->mutexGeladeneChunks);

	return geladen;
}

void Welt::ergaenzeKomprimierteDaten(int chunkX, int chunkZ,
		KomprimierteChunkDaten *komprimierteDaten) {
	pthread_mutex_lock(&this->mutexChunks);
	this->chunks[chunkX][chunkZ]->ergaenzeKomprimierteDaten(komprimierteDaten);
	pthread_mutex_unlock(&this->mutexChunks);
}

void Welt::ergaenzeBlockAenderung(int chunkX, int chunkZ,
		BlockAenderung *blockAenderung) {
	pthread_mutex_lock(&this->mutexChunks);
	this->chunks[chunkX][chunkZ]->ergaenzeBlockAenderung(blockAenderung);
	pthread_mutex_unlock(&this->mutexChunks);
}

void Welt::setzeKompassPosition(int _x, int _y, int _z) {
	this->kompassPosition.x = _x;
	this->kompassPosition.y = _y;
	this->kompassPosition.z = _z;
}

void Welt::setzeServerModus(byte _serverModus) {
	this->serverModus = _serverModus;
}

void Welt::setzeRegen(bool _regen) {
	this->regen = _regen;
}

int Welt::gebeAnzahlGeladeneChunks() {
	int anzahl = 0;
	map<int, map<int, Chunk *> >::iterator it1;

	pthread_mutex_lock(&this->mutexGeladeneChunks);
	for (it1 = this->geladeneChunks.begin(); it1 != this->geladeneChunks.end();
			it1++) {
		anzahl += (*it1).second.size();
	}
	pthread_mutex_unlock(&this->mutexGeladeneChunks);
	return anzahl;
}

int Welt::gebeAnzahlChunks() {
	int anzahl = 0;
	map<int, map<int, Chunk *> >::iterator it1;

	pthread_mutex_lock(&this->mutexChunks);
	for (it1 = this->chunks.begin(); it1 != this->chunks.end(); it1++) {
		anzahl += (*it1).second.size();
	}
	pthread_mutex_unlock(&this->mutexChunks);
	return anzahl;
}

void Welt::zeichne() {
	this->chunkCacheManager->zeichne();
}

unsigned short Welt::gebeWeltHoehe() {
	pthread_mutex_lock(&this->mutexWelthoehe);
	short _weltHoehe = this->weltHoehe;
	pthread_mutex_unlock(&this->mutexWelthoehe);

	return _weltHoehe;
}

void Welt::setzeUhrzeit(short _uhrzeit) {
	pthread_mutex_lock(&this->mutexUhrzeit);
	this->uhrzeit = _uhrzeit;
	pthread_mutex_unlock(&this->mutexUhrzeit);
}

short Welt::gebeUhrzeit() {
	pthread_mutex_lock(&this->mutexUhrzeit);
	short _uhrzeit = this->uhrzeit;
	pthread_mutex_unlock(&this->mutexUhrzeit);

	return _uhrzeit;
}

string Welt::gebeUhrzeitString() {
	pthread_mutex_lock(&this->mutexUhrzeit);
	short _uhrzeit = this->uhrzeit;
	pthread_mutex_unlock(&this->mutexUhrzeit);

	short stunden = _uhrzeit / 1000;
	short minuten = (short) (((float) (_uhrzeit % 1000)) * 0.06f);
	short sekunden = (short) fmod(_uhrzeit, 1.0f / 0.06f);

	ostringstream stream;

	if (stunden < 10) {
		stream << "0";
	}
	if (stream << stunden) {
	} else {
		stream << "0";
	}
	stream << ":";
	if (minuten < 10) {
		stream << "0";
	}
	if (stream << minuten) {
	} else {
		stream << "0";
	}
	stream << ":";
	if (sekunden < 10) {
		stream << "0";
	}
	if (stream << sekunden) {
	} else {
		stream << "0";
	}

	return stream.str();
}
