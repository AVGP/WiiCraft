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

#include "KomprimierteChunkDaten.h"

#include <cmath>
#include "Welt.h"
#include "../exception/ExcZip.h"
#include "../util/Zip.h"

using namespace std;

KomprimierteChunkDaten::KomprimierteChunkDaten(byte *_komprimierteDaten,
		int _komprimierteDatenMenge, short _bitMap, bool _groundUpContiguous) {

	this->komprimierteDaten = _komprimierteDaten;
	this->komprimierteDatenMenge = _komprimierteDatenMenge;
	this->bitMap = _bitMap;
	this->groundUpContiguous = _groundUpContiguous;
}

KomprimierteChunkDaten::~KomprimierteChunkDaten() {
	delete[] this->komprimierteDaten;
}

byte *KomprimierteChunkDaten::gebeDekomprimierteDaten() {
	int dekomprimierteDatenlaenge = this->gebeDatenMenge();
	int errechneteDatenlaenge = dekomprimierteDatenlaenge;

	byte *dekomprimierteDaten = Zip::entpacken(this->komprimierteDaten,
			this->komprimierteDatenMenge, dekomprimierteDatenlaenge);

	if (dekomprimierteDatenlaenge != errechneteDatenlaenge) {
		throw ExcZip(dekomprimierteDatenlaenge, errechneteDatenlaenge);
	}

	return dekomprimierteDaten;
}

int KomprimierteChunkDaten::gebeDatenMenge() {
	int chunkTeile = 0;
	for (int j = 0; j < 16; j++) {
		chunkTeile += this->bitMap >> j & 1;
	}

	// TODO ueberpruefen welche groesse korrekt ist
//	int entpackteDatenMenge = 12288 * chunkTeile;
	int entpackteDatenMenge = 10240 * chunkTeile;

	if (this->groundUpContiguous) {
		entpackteDatenMenge += 256;
	}

	return entpackteDatenMenge;
}

void KomprimierteChunkDaten::ladeDaten(short *bloeckeTyp, byte *bloeckeMeta,
		byte *bloeckeLicht, byte *bloeckeHimmelLicht) {

	byte *dekomprimierteDaten = this->gebeDekomprimierteDaten();

	int chunkTeile = 0;
	for (int j = 0; j < 16; j++) {
		chunkTeile += this->bitMap >> j & 1;
	}

	// TODO Biome-Daten verwerten
	// TODO auf erweiterten BlockTyp umbauen

	int abschnittBlockTyp = 0;
	float abschnittBlockMeta = (16 * 16 * (16 * chunkTeile) * 1);
	float abschnittBlockLicht = (16 * 16 * (16 * chunkTeile) * 1.5);
	float abschnittBlockHimmelLicht = (16 * 16 * (16 * chunkTeile) * 2);
	//float abschnittBlockZusatz = (16 * 16 * (16 * chunkTeile) * 2.5);
	//float abschnittBlockBiome = (16 * 16 * (16 * chunkTeile) * 3);

	for (int i = 0; i < 16; i++) {
		if (!(this->bitMap & 1 << i)) {
			continue;
		}

		for (int iY = 0; iY < 16; iY++) {
			for (int iZ = 0; iZ < 16; iZ++) {
				for (int iX = 0; iX < 16; iX++) {
					unsigned short index = Welt::gebeWelt()->berechneIndex(iX,
							iY + (i * 16), iZ);

					short ganzesA =
							dekomprimierteDaten[((int) abschnittBlockTyp)];

					// Nur laden wenn kein Luft Block
					if (ganzesA > 0) {
						// Abschnitt A: Blocktyp
						bloeckeTyp[index] = ganzesA;

						// Abschnitt B: Metadaten
						byte ganzesB =
								dekomprimierteDaten[((int) abschnittBlockMeta)];
						if (fmod(abschnittBlockMeta, 1) == 0.5) {
							bloeckeMeta[index] = (ganzesB & 0xf0) >> 4;
						} else {
							bloeckeMeta[index] = ganzesB & 0x0f;
						}

						// Abschnitt C: Licht
						byte ganzesC =
								dekomprimierteDaten[((int) abschnittBlockLicht)];
						if (fmod(abschnittBlockLicht, 1) == 0.5) {
							bloeckeLicht[index] = (ganzesC & 0xf0) >> 4;
						} else {
							bloeckeLicht[index] = ganzesC & 0x0f;
						}

						// Abschnitt D: Himmel Licht
						byte ganzesD =
								dekomprimierteDaten[((int) abschnittBlockHimmelLicht)];
						if (fmod(abschnittBlockHimmelLicht, 1) == 0.5) {
							bloeckeHimmelLicht[index] = (ganzesD & 0xf0) >> 4;
						} else {
							bloeckeHimmelLicht[index] = ganzesD & 0x0f;
						}
					} else {
						// Luftblock
						bloeckeTyp[index] = 0;
						bloeckeMeta[index] = 0;
						bloeckeLicht[index] = 0;
						bloeckeHimmelLicht[index] = 0;
					}

					abschnittBlockTyp += 1;
					abschnittBlockMeta += 0.5;
					abschnittBlockLicht += 0.5;
					abschnittBlockHimmelLicht += 0.5;
				}
			}
		}
	}

	delete[] dekomprimierteDaten;
}
