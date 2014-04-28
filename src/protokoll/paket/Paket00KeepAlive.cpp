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

#include "Paket00KeepAlive.h"

#include <cstdio>
#include "../../net/DataOutputStream.h"
#include "../../net/DataInputStream.h"
#include "../Verbindung.h"
#include "../PaketManager.h"
#include "../../util/Debug.h"

using namespace std;

Paket00KeepAlive::Paket00KeepAlive() {
	PaketServer::id = 0x00;
	PaketServer::prio = 0;
}

Paket00KeepAlive::Paket00KeepAlive(int _keepAliventityId) {
	PaketClient::id = 0x00;
	PaketClient::prio = 0;

	this->keepAliventityId = _keepAliventityId;
}

PaketServer *Paket00KeepAlive::gebeInstanz() {
	return new Paket00KeepAlive();
}

bool Paket00KeepAlive::registierePaket() {
	PaketManager::registrierePaket(new Paket00KeepAlive());

	return true;
}

void Paket00KeepAlive::schreibePaketInhalt(DataOutputStream *out) {
	out->schreibeInt(this->keepAliventityId);
}

void Paket00KeepAlive::lesePaketInhalt(DataInputStream *in) {
	this->keepAliventityId = in->leseInt();
}

void Paket00KeepAlive::verarbeitePaket() {
	PaketClient *p = new Paket00KeepAlive(0);
	Verbindung::zuVerschickendenPaketenHinzufuegen(p);

#ifdef DEBUG_ON
	char *buffer = new char[100];
	sprintf(buffer, "id: %i", this->keepAliventityId);
	Debug::schreibePaketLog("Paket00KeepAlive", buffer);
	delete[] buffer;
#endif
}
