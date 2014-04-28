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

#include "ServerAuswahlMenue.h"

#include <cstdlib>
#if defined _WIN32 || defined __CYGWIN__
#include <iostream>
#endif
#include "../protokoll/Verbindung.h"
#include "../protokoll/paket/Paket02Handshake.h"
#include "../gui/Hintergrund.h"
#include "../gui/TextFeld.h"
#include "../gui/Text.h"
#include "../gui/Button.h"
#include "../gui/Bild.h"
#include "../gui/GrafikHandler.h"
#include "../protokoll/Session.h"
#include "../exception/ExcSocketHTTPServerLoginFehlgeschlagen.h"

using namespace std;

ServerAuswahlMenue *ServerAuswahlMenue::serverAuswahlMenue;

void ServerAuswahlMenue::initialisiere() {
	ServerAuswahlMenue::serverAuswahlMenue = new ServerAuswahlMenue();
}

void ServerAuswahlMenue::deinitialisiere() {
	delete ServerAuswahlMenue::serverAuswahlMenue;
}

ServerAuswahlMenue::ServerAuswahlMenue() {
	pthread_mutex_init(&this->mutexwait, NULL);
	pthread_cond_init(&this->condwait, NULL);

	this->hintergrund = new Hintergrund("bildMenueHintergrund");
	this->hintergrund->setzeTastaturAnzeigen(true);
	this->hintergrund->setzeCursorAnzeigen(true);

	Bild *bild = new Bild(144, 20, "logo");
	this->textFehler = new Text(250, 260, "");
	this->textFehler->setzeHintergrundFarbe(0xff33337f);
	this->textBetreten = new Text(200, 160, "Server betreten...");
	this->textBetreten->sichtbarkeit(false);

	this->textServer = new Text(250, 124, "Server:");
	this->textFeldServer = new TextFeld(250, 140, "");
	this->textFeldServer->setzeBeimKlicken(
			&ServerAuswahlMenue::auswaehlenServer);
	this->textPort = new Text(250, 164, "Port:");
	this->textFeldPort = new TextFeld(250, 180, "25565");
	this->textFeldPort->setzeBeimKlicken(&ServerAuswahlMenue::auswaehlenPort);
	this->buttonBetreten = new Button(254, 220, "Betreten");
	this->buttonBetreten->setzeBeimKlicken(&ServerAuswahlMenue::betreten);

	this->hintergrund->fuegeUnterElementHinzu(bild);
	this->hintergrund->fuegeUnterElementHinzu(this->textFehler);
	this->hintergrund->fuegeUnterElementHinzu(this->textBetreten);
	this->hintergrund->fuegeUnterElementHinzu(this->textServer);
	this->hintergrund->fuegeUnterElementHinzu(this->textFeldServer);
	this->hintergrund->fuegeUnterElementHinzu(this->textPort);
	this->hintergrund->fuegeUnterElementHinzu(this->textFeldPort);
	this->hintergrund->fuegeUnterElementHinzu(this->buttonBetreten);
}

ServerAuswahlMenue::~ServerAuswahlMenue() {
	pthread_mutex_destroy(&this->mutexwait);
	pthread_cond_destroy(&this->condwait);
}

void ServerAuswahlMenue::zeigeServerAuswahlMenue() {
	GrafikHandler::gebeGrafikHandler()->setzeAnzeigeElement(
			ServerAuswahlMenue::serverAuswahlMenue->hintergrund);
	GrafikHandler::gebeGrafikHandler()->setzeAusgewaehltesElement(
			ServerAuswahlMenue::serverAuswahlMenue->textFeldServer);

	while (true) {
#if defined _WIN32 || defined __CYGWIN__
		string input = "";
		getline(cin, input);

		ServerAuswahlMenue::serverAuswahlMenue->textFeldServer->setzeText(
				input);

		input = "";
		getline(cin, input);

		ServerAuswahlMenue::serverAuswahlMenue->textFeldPort->setzeText(
				input);

		ServerAuswahlMenue::serverAuswahlMenue->buttonBetreten->beimKlicken(0);
#else
		pthread_mutex_lock(&ServerAuswahlMenue::serverAuswahlMenue->mutexwait);
		pthread_cond_wait(&ServerAuswahlMenue::serverAuswahlMenue->condwait,
				&ServerAuswahlMenue::serverAuswahlMenue->mutexwait);
		pthread_mutex_unlock(
				&ServerAuswahlMenue::serverAuswahlMenue->mutexwait);
#endif
		ServerAuswahlMenue::serverAuswahlMenue->hintergrund->setzeTastaturAnzeigen(
				false);
		ServerAuswahlMenue::serverAuswahlMenue->textFehler->sichtbarkeit(false);
		ServerAuswahlMenue::serverAuswahlMenue->textServer->sichtbarkeit(false);
		ServerAuswahlMenue::serverAuswahlMenue->textFeldServer->sichtbarkeit(
				false);
		ServerAuswahlMenue::serverAuswahlMenue->textPort->sichtbarkeit(false);
		ServerAuswahlMenue::serverAuswahlMenue->textFeldPort->sichtbarkeit(
				false);
		ServerAuswahlMenue::serverAuswahlMenue->buttonBetreten->sichtbarkeit(
				false);
		ServerAuswahlMenue::serverAuswahlMenue->textBetreten->sichtbarkeit(
				true);

		try {
			string _server =
					ServerAuswahlMenue::serverAuswahlMenue->textFeldServer->gebeText();
			string _portString =
					ServerAuswahlMenue::serverAuswahlMenue->textFeldPort->gebeText();
			int _portInt = atoi(_portString.c_str());
			bool verbunden = Verbindung::verbinde(_server, _portInt);

			if (verbunden) {
				Verbindung::starteSchnittstelle();

				string benutzerUndHost;
				benutzerUndHost.append(Session::gebeBenutzer());
				benutzerUndHost.append(";");
				benutzerUndHost.append(_server);
				benutzerUndHost.append(";");
				benutzerUndHost.append(_portString);

				PaketClient *p = new Paket02Handshake(benutzerUndHost);
				Verbindung::zuVerschickendenPaketenHinzufuegen(p);
			} else {
				throw ExcSocketHTTPServerLoginFehlgeschlagen(
						"Verbindung zum Server konnte nicht hergestellt werden.");
			}
		} catch (ExcSocketHTTPServerLoginFehlgeschlagen &exception) {

			ServerAuswahlMenue::serverAuswahlMenue->textFehler->setzeText(
					exception.gebeFehler());
			ServerAuswahlMenue::serverAuswahlMenue->hintergrund->setzeTastaturAnzeigen(
					true);
			ServerAuswahlMenue::serverAuswahlMenue->textFehler->sichtbarkeit(
					true);
			ServerAuswahlMenue::serverAuswahlMenue->textServer->sichtbarkeit(
					true);
			ServerAuswahlMenue::serverAuswahlMenue->textFeldServer->sichtbarkeit(
					true);
			ServerAuswahlMenue::serverAuswahlMenue->textPort->sichtbarkeit(
					true);
			ServerAuswahlMenue::serverAuswahlMenue->textFeldPort->sichtbarkeit(
					true);
			ServerAuswahlMenue::serverAuswahlMenue->buttonBetreten->sichtbarkeit(
					true);
			ServerAuswahlMenue::serverAuswahlMenue->textBetreten->sichtbarkeit(
					false);
			continue;
		}
		break;
	}
}

void ServerAuswahlMenue::betreten() {
	pthread_mutex_lock(&ServerAuswahlMenue::serverAuswahlMenue->mutexwait);
	pthread_cond_signal(&ServerAuswahlMenue::serverAuswahlMenue->condwait);
	pthread_mutex_unlock(&ServerAuswahlMenue::serverAuswahlMenue->mutexwait);
}

void ServerAuswahlMenue::auswaehlenServer() {
	GrafikHandler::gebeGrafikHandler()->setzeAusgewaehltesElement(
			ServerAuswahlMenue::serverAuswahlMenue->textFeldServer);
}

void ServerAuswahlMenue::auswaehlenPort() {
	GrafikHandler::gebeGrafikHandler()->setzeAusgewaehltesElement(
			ServerAuswahlMenue::serverAuswahlMenue->textFeldPort);
}
