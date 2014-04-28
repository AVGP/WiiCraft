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

#include "Paket6BCreativeInventoryAction.h"

#include <cstdio>
#include <cstdlib>
#include "../../net/DataOutputStream.h"
#include "../../net/DataInputStream.h"
#include "../../entity/Slot.h"
#include "../PaketManager.h"
#include "../../util/Debug.h"

using namespace std;

Paket6BCreativeInventoryAction::Paket6BCreativeInventoryAction() {
	PaketServer::id = 0x6b;
	PaketServer::prio = 50;
}

Paket6BCreativeInventoryAction::~Paket6BCreativeInventoryAction() {
	free(this->clickedItem);
}

PaketServer *Paket6BCreativeInventoryAction::gebeInstanz() {
	return new Paket6BCreativeInventoryAction();
}

bool Paket6BCreativeInventoryAction::registierePaket() {
	PaketManager::registrierePaket(new Paket6BCreativeInventoryAction());

	return true;
}

void Paket6BCreativeInventoryAction::schreibePaketInhalt(
		DataOutputStream *out) {
}

void Paket6BCreativeInventoryAction::lesePaketInhalt(DataInputStream *in) {
	this->slot = in->leseShort();
	this->clickedItem = Slot::leseSlot(in);
}

void Paket6BCreativeInventoryAction::verarbeitePaket() {
#ifdef DEBUG_ON
	char *buffer = new char[100];
	sprintf(buffer, "slot: %i", this->slot);
	Debug::schreibePaketLog("Paket6BCreativeInventoryAction", buffer);
	delete[] buffer;
#endif

	// TODO Paketverarbeitung implementieren
}
