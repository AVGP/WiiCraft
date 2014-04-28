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

#include "PaketCAPlayerAbilities.h"

#include <cstdio>
#include "../../net/DataOutputStream.h"
#include "../../net/DataInputStream.h"
#include "../../entity/Spieler.h"
#include "../PaketManager.h"
#include "../../util/Debug.h"

using namespace std;

PaketCAPlayerAbilities::PaketCAPlayerAbilities() {
	PaketServer::id = 0xca;
	PaketServer::prio = 50;
}

PaketCAPlayerAbilities::PaketCAPlayerAbilities(bool _invulnerability,
		bool _isFlying, bool _canFly, bool _instantDestroy) {
	PaketClient::id = 0xca;
	PaketClient::prio = 50;

	this->invulnerability = _invulnerability;
	this->isFlying = _isFlying;
	this->canFly = _canFly;
	this->instantDestroy = _instantDestroy;
}

PaketServer *PaketCAPlayerAbilities::gebeInstanz() {
	return new PaketCAPlayerAbilities();
}

bool PaketCAPlayerAbilities::registierePaket() {
	PaketManager::registrierePaket(new PaketCAPlayerAbilities());

	return true;
}

void PaketCAPlayerAbilities::schreibePaketInhalt(DataOutputStream *out) {
	out->schreibeBoolean(this->invulnerability);
	out->schreibeBoolean(this->isFlying);
	out->schreibeBoolean(this->canFly);
	out->schreibeBoolean(this->instantDestroy);
}

void PaketCAPlayerAbilities::lesePaketInhalt(DataInputStream *in) {
	this->invulnerability = in->leseBoolean();
	this->isFlying = in->leseBoolean();
	this->canFly = in->leseBoolean();
	this->instantDestroy = in->leseBoolean();
}

void PaketCAPlayerAbilities::verarbeitePaket() {
#ifdef DEBUG_ON
	char *buffer = new char[200];
	sprintf(buffer,
			"invulnerability: %i, isFlying: %i, canFly: %i, instantDestroy: %i",
			this->invulnerability, this->isFlying, this->canFly,
			this->instantDestroy);
	Debug::schreibePaketLog("PaketCAPlayerAbilities", buffer);
	delete[] buffer;
#endif

	Spieler::getSpieler()->setzeFaehigkeit(this->isFlying, this->canFly,
			this->instantDestroy, this->invulnerability);
}
