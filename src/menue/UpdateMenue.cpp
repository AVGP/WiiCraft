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

#include "UpdateMenue.h"

#include <stdlib.h>
#if defined _WIN32 || defined __CYGWIN__
#include <iostream>
#endif
#include "../gui/Hintergrund.h"
#include "../gui/Text.h"
#include "../gui/LadeBalken.h"
#include "../gui/Button.h"
#include "../gui/GrafikHandler.h"
#include "../util/UpdateHandler.h"
#include "../util/KontrollerHandler.h"
#include "../exception/ExcSocketHTTPServerLoginFehlgeschlagen.h"

using namespace std;

UpdateMenue *UpdateMenue::updateMenue;

void UpdateMenue::initialisiere() {
	UpdateMenue::updateMenue = new UpdateMenue();
}

void UpdateMenue::deinitialisiere() {
	delete UpdateMenue::updateMenue;
}

UpdateMenue::UpdateMenue() {
	pthread_mutex_init(&this->mutexwait, NULL);
	pthread_cond_init(&this->condwait, NULL);

	this->updateHerunterlanden = false;

	this->hintergrund = new Hintergrund("bildMenueHintergrund");
	this->hintergrund->setzeCursorAnzeigen(true);

	this->text = new Text(250, 200, "Suche nach Update");
	this->ladeBalken = new LadeBalken(270, 220);
	this->ladeBalken->sichtbarkeit(false);

	this->buttonJa = new Button(250, 240, "Ja");
	this->buttonJa->sichtbarkeit(false);
	this->buttonJa->setzeBeimKlicken(&UpdateMenue::starteUpdate);

	this->buttonNein = new Button(300, 240, "Nein");
	this->buttonNein->sichtbarkeit(false);
	this->buttonNein->setzeBeimKlicken(&UpdateMenue::keinUpdate);

	this->hintergrund->fuegeUnterElementHinzu(this->text);
	this->hintergrund->fuegeUnterElementHinzu(this->ladeBalken);
	this->hintergrund->fuegeUnterElementHinzu(this->buttonJa);
	this->hintergrund->fuegeUnterElementHinzu(this->buttonNein);
}

UpdateMenue::~UpdateMenue() {
	pthread_mutex_destroy(&this->mutexwait);
	pthread_cond_destroy(&this->condwait);

	delete this->hintergrund;

	delete this->text;
	delete this->ladeBalken;
	delete this->buttonJa;
	delete this->buttonNein;
}

void UpdateMenue::zeigeUpdateMenue() {
	GrafikHandler::gebeGrafikHandler()->setzeAnzeigeElement(
			UpdateMenue::updateMenue->hintergrund);

	bool updateVorhanden;
	try {
		updateVorhanden = UpdateHandler::istUpdateVorhanden();
	} catch (ExcSocketHTTPServerLoginFehlgeschlagen &exception) {
		updateVorhanden = false;
	}

	if (updateVorhanden) {
		UpdateMenue::updateMenue->text->setzeText(
				"Update gefunden. Soll es installiert werden?");
		UpdateMenue::updateMenue->buttonJa->sichtbarkeit(true);
		UpdateMenue::updateMenue->buttonNein->sichtbarkeit(true);
#if defined _WIN32 || defined __CYGWIN__
		string input = "";
		getline(cin, input);

		UpdateMenue::updateMenue->buttonNein->beimKlicken(0);
#else
		pthread_mutex_lock(&UpdateMenue::updateMenue->mutexwait);
		pthread_cond_wait(&UpdateMenue::updateMenue->condwait,
				&UpdateMenue::updateMenue->mutexwait);
		pthread_mutex_unlock(&UpdateMenue::updateMenue->mutexwait);
#endif
		if (UpdateMenue::updateMenue->updateHerunterlanden) {
			UpdateMenue::updateMenue->text->setzeText(
					"Update wird heruntergeladen");
			UpdateMenue::updateMenue->ladeBalken->sichtbarkeit(true);
			UpdateMenue::updateMenue->buttonJa->sichtbarkeit(false);
			UpdateMenue::updateMenue->buttonNein->sichtbarkeit(false);

			UpdateHandler::ladeUpdate(UpdateMenue::updateMenue->ladeBalken);

			GrafikHandler::gebeGrafikHandler()->stop();
			GrafikHandler::gebeGrafikHandler()->join();

			delete GrafikHandler::gebeGrafikHandler();
			delete KontrollerHandler::gebeKontrollerHandler();

			exit(0);
		}
	}
}

void UpdateMenue::keinUpdate() {
	UpdateMenue::updateMenue->updateHerunterlanden = false;

	pthread_mutex_lock(&UpdateMenue::updateMenue->mutexwait);
	pthread_cond_signal(&UpdateMenue::updateMenue->condwait);
	pthread_mutex_unlock(&UpdateMenue::updateMenue->mutexwait);
}

void UpdateMenue::starteUpdate() {
	UpdateMenue::updateMenue->updateHerunterlanden = true;

	pthread_mutex_lock(&UpdateMenue::updateMenue->mutexwait);
	pthread_cond_signal(&UpdateMenue::updateMenue->condwait);
	pthread_mutex_unlock(&UpdateMenue::updateMenue->mutexwait);
}
