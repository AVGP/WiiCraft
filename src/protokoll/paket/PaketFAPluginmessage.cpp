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

#include "PaketFAPluginmessage.h"

#include <cstdio>
#include <cstdlib>
#include "../../net/DataOutputStream.h"
#include "../../net/DataInputStream.h"
#include "../../exception/ExcSocketStringLaengeUeberschritten.h"
#include "../PaketManager.h"
#include "../../util/Debug.h"

using namespace std;

PaketFAPluginmessage::PaketFAPluginmessage() {
	PaketServer::id = 0xfa;
	PaketServer::prio = 50;
}

PaketFAPluginmessage::PaketFAPluginmessage(string _channel, short _length,
		byte *_data) {
	PaketClient::id = 0xfa;
	PaketClient::prio = 50;

	this->channel = _channel;
	this->length = _length;
	this->data = _data;
}

PaketFAPluginmessage::~PaketFAPluginmessage() {
	free(this->data);
}

PaketServer *PaketFAPluginmessage::gebeInstanz() {
	return new PaketFAPluginmessage();
}

bool PaketFAPluginmessage::registierePaket() {
	PaketManager::registrierePaket(new PaketFAPluginmessage());

	return true;
}

void PaketFAPluginmessage::schreibePaketInhalt(DataOutputStream *out) {
	out->schreibeString(this->channel);
	out->schreibeShort(this->length);
	for (short i = 0; i < this->length; i++) {
		out->schreibeByte(this->data[i]);
	}
}

void PaketFAPluginmessage::lesePaketInhalt(DataInputStream *in) {
	try {
		this->channel = in->leseString(16);
	} catch (ExcSocketStringLaengeUeberschritten &exception) {
		throw ExcSocketStringLaengeUeberschritten(PaketServer::id);
	}

	this->length = in->leseShort();
	this->data = new byte[this->length];

	for (short i = 0; i < this->length; i++) {
		this->data[i] = in->leseByte();
	}
}

void PaketFAPluginmessage::verarbeitePaket() {
#ifdef DEBUG_ON
	char *buffer = new char[200];
	sprintf(buffer, "channel: %s, length: %i", this->channel.data(),
			this->length);
	Debug::schreibePaketLog("PaketFAPluginmessage", buffer);
	delete[] buffer;
#endif
	// TODO nur fuer Plugin API
}
