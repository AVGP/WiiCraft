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
 * CREEPER = 50
 * SKELETON = 51
 * SPIDER = 52
 * GIANT_ZOMBIE = 53
 * ZOMBIE = 54
 * SLIME = 55
 * GHAST = 56
 * ZOMBIE_PIGMAN = 57
 * ENDERMAN = 58
 * CAVE_SPIDER = 59
 * SILVERFISH = 60
 * BLAZE = 61
 * MAGMA_CUBE = 62
 * ENDER_DRAGON = 63
 * PIG = 90
 * SHEEP = 91
 * COW = 92
 * CHICKEN = 93
 * SQUID = 94
 * WOLF = 95
 * MOOSHROOM = 96
 * SNOWMAN = 97
 * OCELOT = 98
 * VILLAGER = 120
 */

#include "Paket18MobSpawn.h"

#include <cstdio>
#include <cstdlib>
#include "../../net/DataInputStream.h"
#include "../../entity/Metadata.h"
#include "../../exception/ExcSocketStringLaengeUeberschritten.h"
#include "../../exception/ExcMetadata.h"
#include "../../entity/Entity.h"
#include "../PaketManager.h"
#include "../../util/Debug.h"

using namespace std;

Paket18MobSpawn::Paket18MobSpawn() {
	PaketServer::id = 0x18;
	PaketServer::prio = 50;
}

Paket18MobSpawn::~Paket18MobSpawn() {
	delete this->metaData;
}

PaketServer *Paket18MobSpawn::gebeInstanz() {
	return new Paket18MobSpawn();
}

bool Paket18MobSpawn::registierePaket() {
	PaketManager::registrierePaket(new Paket18MobSpawn());

	return true;
}

void Paket18MobSpawn::lesePaketInhalt(DataInputStream *in) {
	this->entityId = in->leseInt();
	this->type = (in->leseByte() & 0xff);
	this->x = in->leseInt();
	this->y = in->leseInt();
	this->z = in->leseInt();
	this->yaw = in->leseByte();
	this->pitch = in->leseByte();
	this->headYaw = in->leseByte();
	try {
		this->metaData = Metadata::leseDaten(in);
	} catch (ExcSocketStringLaengeUeberschritten &exception) {
		throw ExcSocketStringLaengeUeberschritten(PaketServer::id);
	} catch (ExcMetadata &exception) {
		throw ExcMetadata(PaketServer::id);
	}
}

void Paket18MobSpawn::verarbeitePaket() {
#ifdef DEBUG_ON
	char *buffer = new char[1000];

	string mobTyp;

	switch (this->type) {
	case 50:
		mobTyp = "CREEPER";
		break;
	case 51:
		mobTyp = "SKELETON";
		break;
	case 52:
		mobTyp = "SPIDER";
		break;
	case 53:
		mobTyp = "GIANT_ZOMBIE";
		break;
	case 54:
		mobTyp = "ZOMBIE";
		break;
	case 55:
		mobTyp = "SLIME";
		break;
	case 56:
		mobTyp = "GHAST";
		break;
	case 57:
		mobTyp = "ZOMBIE_PIGMAN";
		break;
	case 58:
		mobTyp = "ENDERMAN";
		break;
	case 59:
		mobTyp = "CAVE_SPIDER";
		break;
	case 60:
		mobTyp = "SILVERFISH";
		break;
	case 61:
		mobTyp = "BLAZE";
		break;
	case 62:
		mobTyp = "MAGMA_CUBE";
		break;
	case 63:
		mobTyp = "ENDER_DRAGON";
		break;
	case 90:
		mobTyp = "PIG";
		break;
	case 91:
		mobTyp = "SHEEP";
		break;
	case 92:
		mobTyp = "COW";
		break;
	case 93:
		mobTyp = "CHICKEN";
		break;
	case 94:
		mobTyp = "SQUID";
		break;
	case 95:
		mobTyp = "WOLF";
		break;
	case 96:
		mobTyp = "MOOSHROOM";
		break;
	case 97:
		mobTyp = "SNOWMAN";
		break;
	case 98:
		mobTyp = "OCELOT";
		break;
	case 120:
		mobTyp = "VILLAGER";
		break;
	default:
		char *tmp = new char[1000];
		sprintf(tmp, "unbekannt %i", this->type);
		mobTyp = tmp;
		break;
	}

	sprintf(
			buffer,
			"entityId: %i, type: %s, x: %i, y: %i, z: %i, yaw: %i, pitch: %i, headYaw: %i",
			this->entityId, mobTyp.data(), this->x, this->y, this->z, this->yaw,
			this->pitch, this->headYaw);

	Debug::schreibePaketLog("Paket18MobSpawn", buffer);
	delete[] buffer;
#endif

	Entity::gebeEntity(this->entityId);
	// TODO Paketverarbeitung implementieren
}
