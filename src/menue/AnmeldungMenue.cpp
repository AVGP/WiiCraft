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

#include "AnmeldungMenue.h"

#if defined _WIN32 || defined __CYGWIN__
#include <iostream>
#endif
#include "../gui/Hintergrund.h"
#include "../gui/TextFeld.h"
#include "../gui/PasswortFeld.h"
#include "../gui/Text.h"
#include "../gui/Button.h"
#include "../gui/Bild.h"
#include "../gui/GrafikHandler.h"
#include "../protokoll/Session.h"
#include "../exception/ExcSocketHTTPServerLoginFehlgeschlagen.h"
#include "../thread/HTTPSessionAktualisierenThread.h"

using namespace std;

AnmeldungMenue *AnmeldungMenue::anmeldungMenue;

void AnmeldungMenue::initialisiere() {
	AnmeldungMenue::anmeldungMenue = new AnmeldungMenue();
}

void AnmeldungMenue::deinitialisiere() {
	delete AnmeldungMenue::anmeldungMenue;
}

AnmeldungMenue::AnmeldungMenue() {
	pthread_mutex_init(&this->mutexwait, NULL);
	pthread_cond_init(&this->condwait, NULL);

	this->hintergrund = new Hintergrund("bildMenueHintergrund");
	this->hintergrund->setzeTastaturAnzeigen(true);
	this->hintergrund->setzeCursorAnzeigen(true);

	Bild *bild = new Bild(144, 20, "logo");
	this->textFehler = new Text(250, 260, "");
	this->textFehler->setzeHintergrundFarbe(0xff33337f);
	this->textAnmelden = new Text(200, 160, "am Minecraft Server anmelden...");
	this->textAnmelden->sichtbarkeit(false);

	this->textBenutzer = new Text(250, 124, "Benutzer:");
	this->textFeldBenutzer = new TextFeld(250, 140, "");
	this->textFeldBenutzer->setzeBeimKlicken(
			&AnmeldungMenue::auswaehlenBunutzer);
	this->textPasswort = new Text(250, 164, "Passwort:");
	this->textFeldPasswort = new PasswortFeld(250, 180, "");
	this->textFeldPasswort->setzeBeimKlicken(
			&AnmeldungMenue::auswaehlenPasswort);
	this->buttonAnmelden = new Button(254, 220, "Anmelden");
	this->buttonAnmelden->setzeBeimKlicken(&AnmeldungMenue::anmelden);

	this->hintergrund->fuegeUnterElementHinzu(bild);
	this->hintergrund->fuegeUnterElementHinzu(this->textFehler);
	this->hintergrund->fuegeUnterElementHinzu(this->textAnmelden);
	this->hintergrund->fuegeUnterElementHinzu(this->textBenutzer);
	this->hintergrund->fuegeUnterElementHinzu(this->textFeldBenutzer);
	this->hintergrund->fuegeUnterElementHinzu(this->textPasswort);
	this->hintergrund->fuegeUnterElementHinzu(this->textFeldPasswort);
	this->hintergrund->fuegeUnterElementHinzu(this->buttonAnmelden);
}

AnmeldungMenue::~AnmeldungMenue() {
	pthread_mutex_destroy(&this->mutexwait);
	pthread_cond_destroy(&this->condwait);
}

void AnmeldungMenue::zeigeAnmeldungMenue() {
	GrafikHandler::gebeGrafikHandler()->setzeAnzeigeElement(
			AnmeldungMenue::anmeldungMenue->hintergrund);
	GrafikHandler::gebeGrafikHandler()->setzeAusgewaehltesElement(
			AnmeldungMenue::anmeldungMenue->textFeldBenutzer);

	while (true) {
#if defined _WIN32 || defined __CYGWIN__
		string input = "";
		getline(cin, input);

		AnmeldungMenue::anmeldungMenue->textFeldBenutzer->setzeText(input);

		input = "";
		getline(cin, input);
		AnmeldungMenue::anmeldungMenue->textFeldPasswort->setzeText(input);

		AnmeldungMenue::anmeldungMenue->buttonAnmelden->beimKlicken(0);
#else
		pthread_mutex_lock(&AnmeldungMenue::anmeldungMenue->mutexwait);
		pthread_cond_wait(&AnmeldungMenue::anmeldungMenue->condwait,
				&AnmeldungMenue::anmeldungMenue->mutexwait);
		pthread_mutex_unlock(&AnmeldungMenue::anmeldungMenue->mutexwait);
#endif

		AnmeldungMenue::anmeldungMenue->hintergrund->setzeTastaturAnzeigen(
				false);
		AnmeldungMenue::anmeldungMenue->textFehler->sichtbarkeit(false);
		AnmeldungMenue::anmeldungMenue->textBenutzer->sichtbarkeit(false);
		AnmeldungMenue::anmeldungMenue->textFeldBenutzer->sichtbarkeit(false);
		AnmeldungMenue::anmeldungMenue->textPasswort->sichtbarkeit(false);
		AnmeldungMenue::anmeldungMenue->textFeldPasswort->sichtbarkeit(false);
		AnmeldungMenue::anmeldungMenue->buttonAnmelden->sichtbarkeit(false);
		AnmeldungMenue::anmeldungMenue->textAnmelden->sichtbarkeit(true);

		try {
			Session::anmelden(
					AnmeldungMenue::anmeldungMenue->textFeldBenutzer->gebeText(),
					AnmeldungMenue::anmeldungMenue->textFeldPasswort->gebeText());
		} catch (ExcSocketHTTPServerLoginFehlgeschlagen &exception) {

			AnmeldungMenue::anmeldungMenue->textFehler->setzeText(
					exception.gebeFehler());
			AnmeldungMenue::anmeldungMenue->hintergrund->setzeTastaturAnzeigen(
					true);
			AnmeldungMenue::anmeldungMenue->textFehler->sichtbarkeit(true);
			AnmeldungMenue::anmeldungMenue->textBenutzer->sichtbarkeit(true);
			AnmeldungMenue::anmeldungMenue->textFeldBenutzer->sichtbarkeit(
					true);
			AnmeldungMenue::anmeldungMenue->textPasswort->sichtbarkeit(true);
			AnmeldungMenue::anmeldungMenue->textFeldPasswort->setzeText("");
			AnmeldungMenue::anmeldungMenue->textFeldPasswort->sichtbarkeit(
					true);
			AnmeldungMenue::anmeldungMenue->buttonAnmelden->sichtbarkeit(true);
			AnmeldungMenue::anmeldungMenue->textAnmelden->sichtbarkeit(false);
			continue;
		}

		HTTPSessionAktualisierenThread::aktualisiereSessionRegelmaessig();

		break;
	}
}

void AnmeldungMenue::anmelden() {
	pthread_mutex_lock(&AnmeldungMenue::anmeldungMenue->mutexwait);
	pthread_cond_signal(&AnmeldungMenue::anmeldungMenue->condwait);
	pthread_mutex_unlock(&AnmeldungMenue::anmeldungMenue->mutexwait);
}

void AnmeldungMenue::auswaehlenBunutzer() {
	GrafikHandler::gebeGrafikHandler()->setzeAusgewaehltesElement(
			AnmeldungMenue::anmeldungMenue->textFeldBenutzer);
}

void AnmeldungMenue::auswaehlenPasswort() {
	GrafikHandler::gebeGrafikHandler()->setzeAusgewaehltesElement(
			AnmeldungMenue::anmeldungMenue->textFeldPasswort);
}
