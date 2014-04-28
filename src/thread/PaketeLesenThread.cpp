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

#include "PaketeLesenThread.h"

#include "../net/Socket.h"
#include "../net/DataInputStream.h"
#include "../protokoll/PaketServer.h"
#include "../exception/ExcSocketVerbindungVerloren.h"
#include "../exception/ExcPaketUnbekanntesPaket.h"
#include "../protokoll/Verbindung.h"

using namespace std;

PaketeLesenThread::PaketeLesenThread(Socket *_socket) {
	this->socket = _socket;
	this->gestoppt = false;
	this->iStream = new DataInputStream(this->socket);

	pthread_mutex_init(&this->mutexstop, NULL);
}

PaketeLesenThread::~PaketeLesenThread() {
	pthread_mutex_destroy(&this->mutexstop);
}

int PaketeLesenThread::exec() {
	bool ok;
	do {
		if (this->istGestopped()) {
			break;
		}

		try {
			ok = PaketServer::lesePaket(this->iStream);
		} catch (ExcSocketVerbindungVerloren &exception) {
			this->stop();
			Verbindung::beenden(false);
			break;
		} catch (ExcPaketUnbekanntesPaket &exception) {
			this->stop();
			Verbindung::beenden(true);
			break;
		}
	} while (ok);

#ifdef DEBUG_ON
	char *buffer = new char[100];
	pthread_mutex_lock(&this->mutexqueue);
	sprintf(buffer, "Lesen wird gestoppt, letzteId: %x\n",
			PaketServer::letztePaketId);
	pthread_mutex_unlock(&this->mutexqueue);
	Debug::schreibeLog("sd:/apps/WiiCraft/Paket.log", buffer,
			Debug::DATEI_ERWEITERN);
	delete[] buffer;
#endif

	return 0;
}

void PaketeLesenThread::stop() {
	pthread_mutex_lock(&this->mutexstop);
	this->gestoppt = true;
	pthread_mutex_unlock(&this->mutexstop);
}

bool PaketeLesenThread::istGestopped() {
	bool b = false;

	pthread_mutex_lock(&this->mutexstop);
	b = this->gestoppt;
	pthread_mutex_unlock(&this->mutexstop);

	return b;
}
