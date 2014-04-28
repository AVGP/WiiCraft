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

#include "Paket03ChatMessage.h"

#include <cstdio>
#include "../../net/DataOutputStream.h"
#include "../../net/DataInputStream.h"
#include "../../exception/ExcSocketStringLaengeUeberschritten.h"
#include "../../protokoll/Chat.h"
#include "../PaketManager.h"
#include "../../util/Debug.h"

using namespace std;

Paket03ChatMessage::Paket03ChatMessage() {
	PaketServer::id = 0x03;
	PaketServer::prio = 50;
}

Paket03ChatMessage::Paket03ChatMessage(string _message) {
	PaketClient::id = 0x03;
	PaketClient::prio = 50;

	this->message = _message;
}

PaketServer *Paket03ChatMessage::gebeInstanz() {
	return new Paket03ChatMessage();
}

bool Paket03ChatMessage::registierePaket() {
	PaketManager::registrierePaket(new Paket03ChatMessage());

	return true;
}

void Paket03ChatMessage::schreibePaketInhalt(DataOutputStream *out) {
	out->schreibeString(this->message);
}

void Paket03ChatMessage::lesePaketInhalt(DataInputStream *in) {
	try {
		this->message = in->leseString(119);
	} catch (ExcSocketStringLaengeUeberschritten &exception) {
		throw ExcSocketStringLaengeUeberschritten(PaketServer::id);
	}
}

void Paket03ChatMessage::verarbeitePaket() {
	// Steuerzeichen §
	//this->message.substr(0, 1);

	// Farbcode
	string farbe = this->message.substr(1, 1);

	// eigentliche Nachricht
	string nachricht = this->message.substr(2);

#ifdef DEBUG_ON
	string farbcode;
	if (farbe == "0") {
		farbcode = "#000000";
	} else if (farbe == "1") {
		farbcode = "#0000aa";
	} else if (farbe == "2") {
		farbcode = "#00aa00";
	} else if (farbe == "3") {
		farbcode = "#00aaaa";
	} else if (farbe == "4") {
		farbcode = "#aa0000";
	} else if (farbe == "5") {
		farbcode = "#aa00aa";
	} else if (farbe == "6") {
		farbcode = "#ffaa00";
	} else if (farbe == "7") {
		farbcode = "#aaaaaa";
	} else if (farbe == "8") {
		farbcode = "#555555";
	} else if (farbe == "9") {
		farbcode = "#5555ff";
	} else if (farbe == "a") {
		farbcode = "#55ff55";
	} else if (farbe == "b") {
		farbcode = "#55ffff";
	} else if (farbe == "c") {
		farbcode = "#ff5555";
	} else if (farbe == "d") {
		farbcode = "#ff55ff";
	} else if (farbe == "e") {
		farbcode = "#ffff55";
	} else if (farbe == "f") {
		farbcode = "#ffffff";
	} else {
		farbcode = "unbakannt";
	}

	char *buffer = new char[200];
	sprintf(buffer, "farbe=%s, text=%s", farbcode.data(), nachricht.data());
	Debug::schreibePaketLog("Paket03ChatMessage", buffer);
	delete[] buffer;
#endif

	Chat::gebeChat()->fuegeNachrichtHinzu(nachricht, farbe);
}
