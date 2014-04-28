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

#include "Verbindung.h"

#include "paket/PaketFFDisconnectKick.h"
#include "../util/Debug.h"


using namespace std;

Socket *Verbindung::socket;
PaketeSchreibenThread *Verbindung::vSchreiben;
PaketeLesenThread *Verbindung::vLesen;
PaketeVerarbeitenThread *Verbindung::vVerarbeitung;

bool Verbindung::verbinde(string server, int port) {
	Verbindung::socket = new Socket();

	bool ret = Verbindung::socket->connect(server.data(), port);
	if (ret) {
		Verbindung::vSchreiben = new PaketeSchreibenThread(Verbindung::socket);
		Verbindung::vVerarbeitung = new PaketeVerarbeitenThread();
		Verbindung::vLesen = new PaketeLesenThread(Verbindung::socket);
	}

	return ret;
}

void Verbindung::starteSchnittstelle() {
	Verbindung::vLesen->start();
	Verbindung::vVerarbeitung->start();
	Verbindung::vSchreiben->start();
}

void Verbindung::warte() {
	Verbindung::vVerarbeitung->join();
	Verbindung::vSchreiben->join();
	Verbindung::vLesen->join();
}

void Verbindung::zuVerschickendenPaketenHinzufuegen(PaketClient *p) {
	Verbindung::vSchreiben->verschickePaket(p);
}

void Verbindung::zuVerarbeitendenPaketenHinzufuegen(PaketServer *p) {
	Verbindung::vVerarbeitung->verarbeitePaket(p);
}

void Verbindung::beenden(bool aktiv) {
	if (aktiv) {
#ifdef DEBUG_ON
		Debug::schreibeLog("sd:/apps/WiiCraft/Paket.log",
				"Spiel wird aktiv verlassen.\n", Debug::DATEI_ERWEITERN);
#endif
		PaketClient *p = new PaketFFDisconnectKick("Spiel wurde verlassen.");
		Verbindung::zuVerschickendenPaketenHinzufuegen(p);
		return;
	}
#ifdef DEBUG_ON
	else {

		Debug::schreibeLog("sd:/apps/WiiCraft/Paket.log",
				"Spiel wird passiv verlassen.\n", Debug::DATEI_ERWEITERN);
	}
#endif

	Verbindung::vLesen->stop();
	Verbindung::vVerarbeitung->stop();
	Verbindung::vSchreiben->stop();
}
