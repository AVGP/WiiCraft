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

#include "Paket0DPlayerPositionLook.h"

#include <cstdio>
#include "../../net/DataOutputStream.h"
#include "../../net/DataInputStream.h"
#include "../../entity/Spieler.h"
#include "../PaketManager.h"
#include "../../util/Debug.h"

using namespace std;

Paket0DPlayerPositionLook::Paket0DPlayerPositionLook() {
	PaketServer::id = 0x0d;
	PaketServer::prio = 50;
}

Paket0DPlayerPositionLook::Paket0DPlayerPositionLook(double _x, double _y,
		double _stance, double _z, float _yaw, float _pitch, bool _onGround) {
	PaketClient::id = 0x0d;
	PaketClient::prio = 50;

	this->x = _x;
	this->y = _y;
	this->z = _z;
	this->stance = _stance;
	this->yaw = _yaw;
	this->pitch = _pitch;
	this->onGround = _onGround;
}

PaketServer *Paket0DPlayerPositionLook::gebeInstanz() {
	return new Paket0DPlayerPositionLook();
}

bool Paket0DPlayerPositionLook::registierePaket() {
	PaketManager::registrierePaket(new Paket0DPlayerPositionLook());

	return true;
}

void Paket0DPlayerPositionLook::schreibePaketInhalt(DataOutputStream *out) {
	out->schreibeDouble(this->x);
	out->schreibeDouble(this->y);
	out->schreibeDouble(this->stance);
	out->schreibeDouble(this->z);
	out->schreibeFloat(this->yaw);
	out->schreibeFloat(this->pitch);
	out->schreibeBoolean(this->onGround);
}

void Paket0DPlayerPositionLook::lesePaketInhalt(DataInputStream *in) {
	this->x = in->leseDouble();
	this->stance = in->leseDouble();
	this->y = in->leseDouble();
	this->z = in->leseDouble();
	this->yaw = in->leseFloat();
	this->pitch = in->leseFloat();
	this->onGround = in->leseBoolean();
}

void Paket0DPlayerPositionLook::verarbeitePaket() {
#ifdef DEBUG_ON
	char *buffer = new char[200];
	sprintf(buffer,
			"x: %f, y: %f, z: %f, stance: %f, yaw: %f, pitch: %f, onGround: %i",
			this->x, this->y, this->z, this->stance, this->yaw, this->pitch,
			this->onGround);
	Debug::schreibePaketLog("Paket0DPlayerPositionLook", buffer);
	delete[] buffer;
#endif

	Spieler::getSpieler()->setzeHaltung(this->stance);
	Spieler::getSpieler()->setzeBlickfeld(this->yaw, this->pitch);
	Spieler::getSpieler()->setzeAufBoden(this->onGround);
	Spieler::getSpieler()->setzeKoordinaten(this->x, this->y, this->z);
}
