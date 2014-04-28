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
 * 1	moveSpeed		Increases player speed and FOV.
 * 2	moveSlowdown	Decreases player speed and FOV.
 * 3	digSpeed		Increases player dig speed
 * 4	digSlowDown		Decreases player dig speed
 * 5	damageBoost
 * 6	heal
 * 7	harm
 * 8	jump
 * 9	confusion		Portal-like effect
 * 10	regeneration	Hearts pulse one-by-one				Caused by golden apple. Health regenerates over 600-tick (30s) period.
 * 11	resistance
 * 12	fireResistance
 * 13	waterBreathing	Bubbles do not decrease underwater
 * 14	invisibility
 * 15	blindness
 * 16	nightVision
 * 17	hunger			Food bar turns green				Caused by poisoning from Rotten Flesh or Raw Chicken
 * 18	weakness
 * 19	poison			Hearts turn yellow					Caused by poisoning from cave (blue) spider
 */

#include "Paket29EntityEffect.h"

#include <cstdio>
#include "../../net/DataInputStream.h"
#include "../../entity/Entity.h"
#include "../PaketManager.h"
#include "../../util/Debug.h"

using namespace std;

Paket29EntityEffect::Paket29EntityEffect() {
	PaketServer::id = 0x29;
	PaketServer::prio = 50;
}

PaketServer *Paket29EntityEffect::gebeInstanz() {
	return new Paket29EntityEffect();
}

bool Paket29EntityEffect::registierePaket() {
	PaketManager::registrierePaket(new Paket29EntityEffect());

	return true;
}

void Paket29EntityEffect::lesePaketInhalt(DataInputStream *in) {
	this->entityId = in->leseInt();
	this->effectId = in->leseByte();
	this->amplifier = in->leseByte();
	this->duration = in->leseShort();
}

void Paket29EntityEffect::verarbeitePaket() {
#ifdef DEBUG_ON
	char *buffer = new char[100];
	sprintf(buffer, "entityId: %i, effectId: %i, amplifier: %i, duration: %i",
			this->entityId, this->effectId, this->amplifier, this->duration);
	Debug::schreibePaketLog("Paket29EntityEffect", buffer);
	delete[] buffer;
#endif

	Entity::gebeEntity(this->entityId);
	// TODO Paketverarbeitung implementieren
}
