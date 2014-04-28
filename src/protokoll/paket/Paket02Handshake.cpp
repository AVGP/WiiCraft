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

#include "Paket02Handshake.h"

#include <cstdio>
#include "../Verbindung.h"
#include "../../net/DataOutputStream.h"
#include "../../net/DataInputStream.h"
#include "Paket01LoginRequest.h"
#include "../../exception/ExcSocketStringLaengeUeberschritten.h"
#include "../../exception/ExcSocketHTTPServerJoinFehlgeschlagen.h"
#include "../Session.h"
#include "../../util/ClientInfo.h"
#include "../PaketManager.h"
#include "../../util/Debug.h"

using namespace std;

Paket02Handshake::Paket02Handshake() {
	PaketServer::id = 0x02;
	PaketServer::prio = 50;
}

Paket02Handshake::Paket02Handshake(string _usernameAndHost) {
	PaketClient::id = 0x02;
	PaketClient::prio = 50;

	this->usernameAndHost = _usernameAndHost;
}

PaketServer *Paket02Handshake::gebeInstanz() {
	return new Paket02Handshake();
}

bool Paket02Handshake::registierePaket() {
	PaketManager::registrierePaket(new Paket02Handshake());

	return true;
}

void Paket02Handshake::schreibePaketInhalt(DataOutputStream *out) {
	out->schreibeString(this->usernameAndHost);
}

void Paket02Handshake::lesePaketInhalt(DataInputStream *in) {
	try {
		this->connectionHash = in->leseString(32);
	} catch (ExcSocketStringLaengeUeberschritten &exception) {
		throw ExcSocketStringLaengeUeberschritten(PaketServer::id);
	}
}

void Paket02Handshake::verarbeitePaket() {
#ifdef DEBUG_ON
	Debug::schreibePaketLog("Paket02Handshake", this->connectionHash);
#endif

	if (this->connectionHash != "+") {
		Session::tretteServerBei(this->connectionHash);
	}

	PaketClient *p = new Paket01LoginRequest(ClientInfo::clientProtokollVersion,
			Session::gebeBenutzer());
	Verbindung::zuVerschickendenPaketenHinzufuegen(p);
}
