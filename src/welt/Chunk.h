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

#ifndef CHUNK_H_
#define CHUNK_H_

#include <map>
#include <list>
#include <vector>
#if defined _WIN32 || defined __CYGWIN__
#include <pthread.h>
#else
#include "../util/pthread.h"
#endif
#include "../util/Datentypen.h"

namespace std {

class KomprimierteChunkDaten;
class BlockAenderung;

class Chunk {
public:
	Chunk(int _x, int _z);
	~Chunk();

	bool istGeladen();
	void ergaenzeKomprimierteDaten(KomprimierteChunkDaten *_komprimierteDaten);
	void ergaenzeBlockAenderung(BlockAenderung *_blockAenderung);
	void ladeChunk();
	void speichereChunk();
	int gebeX();
	int gebeZ();
	void zeichne();
	void aktualisiereZeichnenIndex();
	unsigned long gebeVersionsNummer();
	void kopiereDaten(short *_bloeckeTyp, byte *_bloeckeMeta,
			byte *_bloeckeLicht, byte *_bloeckeHimmelLicht);
private:
	bool geladen;
	bool initialisiert;
	int x;
	int z;
	unsigned long version;
	short *bloeckeTyp;
	byte *bloeckeMeta;
	byte *bloeckeLicht;
	byte *bloeckeHimmelLicht;
	vector<KomprimierteChunkDaten *> komprimierteDaten;
	list<BlockAenderung *> blockAenderungen;
	pthread_mutex_t mutexKomprimierteDaten;
	pthread_mutex_t mutexBlockAenderungen;
	pthread_mutex_t mutexDaten;
	pthread_mutex_t mutexIndex;
	pthread_mutex_t mutexGeladen;

	void initialisiere();
};

}
#endif /* CHUNK_H_ */
