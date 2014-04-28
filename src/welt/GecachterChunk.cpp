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

#include "GecachterChunk.h"

#include <stddef.h>
#if defined _WIN32 || defined __CYGWIN__
#include "../util/WiiFunction.h"
#else /* __wii__ */
#include <grrlib.h>
#endif /* __wii__ */
#include "Chunk.h"
#include "Welt.h"
#include "../item/ItemManager.h"

using namespace std;

GecachterChunk::GecachterChunk(Chunk *_chunk) {
	this->version = 0;
	this->anzahlZeichenbarerBloecke = 0;
	this->chunk = _chunk;

	this->bloeckeTyp = new short[1];
	this->bloeckeMeta = new byte[1];
	this->bloeckeLicht = new byte[1];
	this->bloeckeHimmelLicht = new byte[1];

	this->aktualisiereCacheWennNoetig();
}

bool GecachterChunk::istAktuell() {
	if (this->version < this->chunk->gebeVersionsNummer()) {
		return false;
	}

	return true;
}

void GecachterChunk::aktualisiereCacheWennNoetig() {
	if (this->istAktuell()) {
		return;
	}

	this->version = this->chunk->gebeVersionsNummer();

	if (this->anzahlZeichenbarerBloecke > 0) {
		this->anzahlZeichenbarerBloecke = 0;
		delete[] this->nrZeichenbarerBloecke;
	}

	list<unsigned int> tmpList;

	Welt *welt = Welt::gebeWelt();

	if (welt == NULL) {
		return;
	}

	unsigned int datenmenge = welt->gebeWeltHoehe() * 16 * 16;

	short *gecachtBloeckeTyp = new short[datenmenge];
	byte *gecachtBloeckeMeta = new byte[datenmenge];
	byte *gecachtBloeckeLicht = new byte[datenmenge];
	byte *gecachtBloeckeHimmelLicht = new byte[datenmenge];

	this->chunk->kopiereDaten(gecachtBloeckeTyp, gecachtBloeckeMeta,
			gecachtBloeckeLicht, gecachtBloeckeHimmelLicht);

	for (unsigned int index = 0; index < datenmenge; index++) {
		short typ = gecachtBloeckeTyp[index];

		if (typ == 0x000) {
			continue;
		}

		Welt *welt = Welt::gebeWelt();
		int blockX;
		int blockY;
		int blockZ;
		welt->berechnePosAusIndex(index, blockX, blockY, blockZ);
		short hoehe = welt->gebeWeltHoehe();

		unsigned short indexWest = index - (16 * hoehe);
		unsigned short indexOst = index + (16 * hoehe);
		unsigned short indexOben = index + 1;
		unsigned short indexUnten = index - 1;
		unsigned short indexNord = index + hoehe;
		unsigned short indexSued = index - hoehe;

		// TODO nachbar Chunk pruefen
		if (
		//(blockX == 0 && welt->istChunkGeladen(this->x - 1, this->z) /* && nachbar Chunk abfragen*/) ||
		(blockX > 0
				&& (gecachtBloeckeTyp[indexWest] == 0
						|| ItemManager::istDurchsichtig(
								gecachtBloeckeTyp[indexWest])))) {
			tmpList.push_back(index);
			continue;
		}

		if (
		//(blockX == 15 && welt->istChunkGeladen(this->x + 1, this->z) /* && nachbar Chunk abfragen*/) ||
		(blockX < 15
				&& (gecachtBloeckeTyp[indexOst] == 0
						|| ItemManager::istDurchsichtig(
								gecachtBloeckeTyp[indexOst])))) {
			tmpList.push_back(index);
			continue;
		}

		if (
		//(blockZ == 0 && welt->istChunkGeladen(this->x, this->z - 1) /* && nachbar Chunk abfragen*/) ||
		(blockZ > 0
				&& (gecachtBloeckeTyp[indexSued] == 0
						|| ItemManager::istDurchsichtig(
								gecachtBloeckeTyp[indexSued])))) {
			tmpList.push_back(index);
			continue;
		}

		if (
		//(blockZ == 15 && welt->istChunkGeladen(this->x, this->z + 1) /* && nachbar Chunk abfragen*/) ||
		(blockZ < 15
				&& (gecachtBloeckeTyp[indexNord] == 0
						|| ItemManager::istDurchsichtig(
								gecachtBloeckeTyp[indexNord])))) {
			tmpList.push_back(index);
			continue;
		}

		if (blockY > 0
				&& (gecachtBloeckeTyp[indexUnten] == 0
						|| ItemManager::istDurchsichtig(
								gecachtBloeckeTyp[indexUnten]))) {
			tmpList.push_back(index);
			continue;
		}

		if (blockY < hoehe - 1
				&& (gecachtBloeckeTyp[indexOben] == 0
						|| ItemManager::istDurchsichtig(
								gecachtBloeckeTyp[indexOben]))) {
			tmpList.push_back(index);
			continue;
		}
	}

	this->anzahlZeichenbarerBloecke = tmpList.size();
	this->nrZeichenbarerBloecke =
			new unsigned int[this->anzahlZeichenbarerBloecke];

	list<unsigned int>::iterator it;

	delete[] this->bloeckeTyp;
	delete[] this->bloeckeMeta;
	delete[] this->bloeckeLicht;
	delete[] this->bloeckeHimmelLicht;
	this->bloeckeTyp = new short[tmpList.size()];
	this->bloeckeMeta = new byte[tmpList.size()];
	this->bloeckeLicht = new byte[tmpList.size()];
	this->bloeckeHimmelLicht = new byte[tmpList.size()];

	unsigned int nr = 0;
	for (it = tmpList.begin(); it != tmpList.end(); it++) {
		this->nrZeichenbarerBloecke[nr] = (*it);
		this->bloeckeTyp[nr] = gecachtBloeckeTyp[(*it)];
		this->bloeckeMeta[nr] = gecachtBloeckeMeta[(*it)];
		this->bloeckeLicht[nr] = gecachtBloeckeLicht[(*it)];
		this->bloeckeHimmelLicht[nr] = gecachtBloeckeHimmelLicht[(*it)];

		nr++;
	}

	delete[] gecachtBloeckeTyp;
	delete[] gecachtBloeckeMeta;
	delete[] gecachtBloeckeLicht;
	delete[] gecachtBloeckeHimmelLicht;
}

void GecachterChunk::zeichne() {
	GRRLIB_ObjectView((this->chunk->gebeX() * 16), 0,
			(this->chunk->gebeZ() * 16), 0, 0, 0, 1, 1, 1);

	Welt *welt = Welt::gebeWelt();

	for (unsigned int durchlauf = 0;
			durchlauf < this->anzahlZeichenbarerBloecke; durchlauf++) {
		unsigned int index = this->nrZeichenbarerBloecke[durchlauf];

		int blockX;
		int blockY;
		int blockZ;
		welt->berechnePosAusIndex(index, blockX, blockY, blockZ);

		ItemManager::zeichne(this->bloeckeTyp[durchlauf], blockX, blockY,
				blockZ, this->bloeckeMeta[durchlauf]);

	}
}
