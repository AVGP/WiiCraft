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

#include "Paket09Respawn.h"

#include <cstdio>
#include "../../net/DataOutputStream.h"
#include "../../net/DataInputStream.h"
#include "../../exception/ExcSocketStringLaengeUeberschritten.h"
#include "../../welt/Welt.h"
#include "../PaketManager.h"
#include "../../util/Debug.h"

using namespace std;

Paket09Respawn::Paket09Respawn() {
	PaketServer::id = 0x09;
	PaketServer::prio = 50;
}

Paket09Respawn::Paket09Respawn(int _dimension, byte _difficulty,
		byte _creativeMode, short _worldHeight, string _levelType) {
	PaketClient::id = 0x09;
	PaketClient::prio = 50;

	this->dimension = _dimension;
	this->difficulty = _difficulty;
	this->creativeMode = _creativeMode;
	this->worldHeight = _worldHeight;
	this->levelType = _levelType;
}

PaketServer *Paket09Respawn::gebeInstanz() {
	return new Paket09Respawn();
}

bool Paket09Respawn::registierePaket() {
	PaketManager::registrierePaket(new Paket09Respawn());

	return true;
}

void Paket09Respawn::schreibePaketInhalt(DataOutputStream *out) {
	out->schreibeInt(this->dimension);
	out->schreibeByte(this->difficulty);
	out->schreibeByte(this->creativeMode);
	out->schreibeShort(this->worldHeight);
	out->schreibeString(this->levelType);
}

void Paket09Respawn::lesePaketInhalt(DataInputStream *in) {
	this->dimension = in->leseInt();
	this->difficulty = in->leseByte();
	this->creativeMode = in->leseByte();
	this->worldHeight = in->leseShort();

	try {
		this->levelType = in->leseString(16);
	} catch (ExcSocketStringLaengeUeberschritten &exception) {
		throw ExcSocketStringLaengeUeberschritten(PaketServer::id);
	}
}

void Paket09Respawn::verarbeitePaket() {
	Welt::initialisiereWelt(this->dimension, this->levelType, this->difficulty,
			this->creativeMode, this->worldHeight);

#ifdef DEBUG_ON
	char *buffer = new char[200];
	sprintf(
			buffer,
			"dimension: %i, difficulty: %i, creativeMode: %i, worldHeight: %i, levelType: %s",
			this->dimension, this->difficulty, this->creativeMode,
			this->worldHeight, this->levelType.data());
	Debug::schreibePaketLog("Paket09Respawn", buffer);
	delete[] buffer;
#endif
}
