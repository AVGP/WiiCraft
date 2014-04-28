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

#include "Paket28EntityMetadata.h"

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

Paket28EntityMetadata::Paket28EntityMetadata() {
	PaketServer::id = 0x28;
	PaketServer::prio = 50;
}

Paket28EntityMetadata::~Paket28EntityMetadata() {
	delete this->entityMetadata;
}

PaketServer *Paket28EntityMetadata::gebeInstanz() {
	return new Paket28EntityMetadata();
}

bool Paket28EntityMetadata::registierePaket() {
	PaketManager::registrierePaket(new Paket28EntityMetadata());

	return true;
}

void Paket28EntityMetadata::lesePaketInhalt(DataInputStream *in) {
	this->entityId = in->leseInt();
	try {
		this->entityMetadata = Metadata::leseDaten(in);
	} catch (ExcSocketStringLaengeUeberschritten &exception) {
		throw ExcSocketStringLaengeUeberschritten(PaketServer::id);
	} catch (ExcMetadata &exception) {
		throw ExcMetadata(PaketServer::id);
	}
}

void Paket28EntityMetadata::verarbeitePaket() {
#ifdef DEBUG_ON
	char *buffer = new char[100];
	sprintf(buffer, "entityId: %i", this->entityId);
	Debug::schreibePaketLog("Paket28EntityMetadata", buffer);
	delete[] buffer;
#endif

	Entity::gebeEntity(this->entityId);
	// TODO Paketverarbeitung implementieren
}
