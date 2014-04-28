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

/*
 * effectId:
 * 1000	CLICK2
 * 1001	CLICK1
 * 1002	BOW_FIRE
 * 1003	DOOR_TOGGLE
 * 1004	EXTINGUISH
 * 1005	RECORD_PLAY	Record ID [1]
 * 1007	CHARGE	Sound of ghast firing.
 * 1008	FIREBALL	Sound of blaze firing
 * 1009	FIREBALL	Same as above
 * 2000	SMOKE	Direction, check below
 * 2001	BLOCK_BREAK	Block ID broken
 * 2002	SPLASH_POTION	Potion ID [2]	Particle animation and sound
 * 2003	PORTAL	Particle animation
 * 2004	BLAZE (?)	Particle animation (fire + smoke)
 *
 * data:
 * 0	South - East
 * 1	South
 * 2	South - West
 * 3	East
 * 4	(Up or middle ?)
 * 5	West
 * 6	North - East
 * 7	North
 * 8	North - West
 */

#include "Paket3DSoundParticleEffect.h"

#include <cstdio>
#include "../../net/DataInputStream.h"
#include "../PaketManager.h"
#include "../../util/Debug.h"

using namespace std;

Paket3DSoundParticleEffect::Paket3DSoundParticleEffect() {
	PaketServer::id = 0x3d;
	PaketServer::prio = 50;
}

PaketServer *Paket3DSoundParticleEffect::gebeInstanz() {
	return new Paket3DSoundParticleEffect();
}

bool Paket3DSoundParticleEffect::registierePaket() {
	PaketManager::registrierePaket(new Paket3DSoundParticleEffect());

	return true;
}

void Paket3DSoundParticleEffect::lesePaketInhalt(DataInputStream *in) {
	this->effectId = in->leseInt();
	this->x = in->leseInt();
	this->y = in->leseByte();
	this->z = in->leseInt();
	this->data = in->leseInt();
}

void Paket3DSoundParticleEffect::verarbeitePaket() {
#ifdef DEBUG_ON
	char *buffer = new char[100];
	sprintf(buffer, "effectId: %i, x: %i, y: %i, z: %i, data: %i",
			this->effectId, this->x, this->y, this->z, this->data);
	Debug::schreibePaketLog("Paket3DSoundParticleEffect", buffer);
	delete[] buffer;
#endif

	// TODO Paketverarbeitung implementieren
}
