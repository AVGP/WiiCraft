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
 * 0 No animation
 * 1 Swing arm
 * 2 Damage animation
 * 3 Leave bed
 * 5 Eat food
 * 102 (unknown)
 * 104 Crouch
 * 105 Uncrouch
 *
 * Only 1 (swing arm) and 3 (leave bed) is sent by notchian clients.
 * Crouching is sent via 0x13. Damage is server-side, and so is not sent by notchian clients.
 * See also 0x26.
 */

#include "Paket12Animation.h"

#include <cstdio>
#include "../../net/DataOutputStream.h"
#include "../../net/DataInputStream.h"
#include "../../entity/Entity.h"
#include "../PaketManager.h"
#include "../../util/Debug.h"

using namespace std;

Paket12Animation::Paket12Animation() {
	PaketServer::id = 0x12;
	PaketServer::prio = 50;
}

Paket12Animation::Paket12Animation(int _entityId, byte _animation) {
	PaketClient::id = 0x12;
	PaketClient::prio = 50;

	this->entityId = _entityId;
	this->animation = _animation;
}

PaketServer *Paket12Animation::gebeInstanz() {
	return new Paket12Animation();
}

bool Paket12Animation::registierePaket() {
	PaketManager::registrierePaket(new Paket12Animation());

	return true;
}

void Paket12Animation::schreibePaketInhalt(DataOutputStream *out) {
	out->schreibeInt(this->entityId);
	out->schreibeByte(this->animation);
}

void Paket12Animation::lesePaketInhalt(DataInputStream *in) {
	this->entityId = in->leseInt();
	this->animation = in->leseByte();
}

void Paket12Animation::verarbeitePaket() {
#ifdef DEBUG_ON
	char *buffer = new char[100];
	sprintf(buffer, "entityId: %i, animation: %i", this->entityId,
			this->animation);
	Debug::schreibePaketLog("Paket12Animation", buffer);
	delete[] buffer;
#endif

	Entity::gebeEntity(this->entityId);
	// TODO Paketverarbeitung implementieren
}
