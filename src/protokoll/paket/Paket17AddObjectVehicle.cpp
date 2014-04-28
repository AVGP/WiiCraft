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
 * BOAT = 1
 * MINECART = 10
 * MINECART_STORAGE = 11
 * MINECART_POWERED =12
 * ACTIVATED_TNT =50
 * ENDERCRYSTAL = 51
 * ARROW_PROJECTILE = 60
 * SNOWBALL_PROJECTILE = 61
 * EGG_PROJECTILE = 62
 * FALLING_SAND = 70
 * FALLING_GRAVEL = 71
 * EYE_OF_ENDER = 72
 * FALLING_DRAGON EGG = 74
 * FISHING_FLOAT = 90
 */

#include "Paket17AddObjectVehicle.h"

#include <cstdio>
#include <string>
#include "../../net/DataInputStream.h"
#include "../../entity/Entity.h"
#include "../PaketManager.h"
#include "../../util/Debug.h"

using namespace std;

Paket17AddObjectVehicle::Paket17AddObjectVehicle() {
	PaketServer::id = 0x17;
	PaketServer::prio = 50;
}

PaketServer *Paket17AddObjectVehicle::gebeInstanz() {
	return new Paket17AddObjectVehicle();
}

bool Paket17AddObjectVehicle::registierePaket() {
	PaketManager::registrierePaket(new Paket17AddObjectVehicle());

	return true;
}

void Paket17AddObjectVehicle::lesePaketInhalt(DataInputStream *in) {
	this->entityId = in->leseInt();
	this->type = in->leseByte();
	this->x = in->leseInt();
	this->y = in->leseInt();
	this->z = in->leseInt();
	this->fireballThrowersEntityId = in->leseInt();
	if (this->fireballThrowersEntityId > 0) {
		this->speedX = in->leseShort();
		this->speedY = in->leseShort();
		this->speedZ = in->leseShort();
	}
}

void Paket17AddObjectVehicle::verarbeitePaket() {
#ifdef DEBUG_ON
	char *buffer = new char[100];
	string typ;
	if (this->type == 1) {
		typ = "BOAT";
	} else if (this->type == 10) {
		typ = "MINECART";
	} else if (this->type == 11) {
		typ = "MINECART_STORAGE";
	} else if (this->type == 12) {
		typ = "MINECART_POWERED";
	} else if (this->type == 50) {
		typ = "ACTIVATED_TNT";
	} else if (this->type == 51) {
		typ = "ENDERCRYSTAL";
	} else if (this->type == 60) {
		typ = "ARROW_PROJECTILE";
	} else if (this->type == 61) {
		typ = "SNOWBALL_PROJECTILE";
	} else if (this->type == 62) {
		typ = "EGG_PROJECTILE";
	} else if (this->type == 70) {
		typ = "FALLING_SAND";
	} else if (this->type == 71) {
		typ = "FALLING_GRAVEL";
	} else if (this->type == 72) {
		typ = "EYE_OF_ENDER";
	} else if (this->type == 74) {
		typ = "FALLING_DRAGON_EGG";
	} else if (this->type == 90) {
		typ = "FISHING_FLOAT";
	} else {
		typ = "unbekannt";
	}

	sprintf(buffer, "typ=%s, id=%i", typ.data(), this->entityId);
	Debug::schreibePaketLog("Paket17AddObjectVehicle", buffer);
	delete[] buffer;
#endif

	Entity::gebeEntity(this->entityId);
	// TODO Paketverarbeitung implementieren
}
