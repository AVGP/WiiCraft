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

#include "FehlerMenue.h"

#if defined _WIN32 || defined __CYGWIN__
#include <iostream>
#endif
#include <stdlib.h>
#include "../gui/Hintergrund.h"
#include "../gui/Text.h"
#include "../gui/Button.h"
#include "../gui/GrafikHandler.h"

using namespace std;

FehlerMenue *FehlerMenue::fehlerMenue;

void FehlerMenue::initialisiere(string fehlerText) {
	FehlerMenue::fehlerMenue = new FehlerMenue(fehlerText);
}

void FehlerMenue::deinitialisiere() {
	delete FehlerMenue::fehlerMenue;
}

FehlerMenue::FehlerMenue(string fehlerText) {
	pthread_mutex_init(&this->mutexWait, NULL);
	pthread_cond_init(&this->condWait, NULL);

	this->hintergrund = new Hintergrund("bildMenueHintergrund");
	this->hintergrund->setzeCursorAnzeigen(true);

	this->textFehler = new Text(200, 160, fehlerText);
	this->textFehler->sichtbarkeit(true);

	this->buttonOk = new Button(254, 220, "Ok");
	this->buttonOk->setzeBeimKlicken(&FehlerMenue::ok);

	this->hintergrund->fuegeUnterElementHinzu(this->textFehler);
	this->hintergrund->fuegeUnterElementHinzu(this->buttonOk);
}

FehlerMenue::~FehlerMenue() {
	pthread_mutex_destroy(&this->mutexWait);
	pthread_cond_destroy(&this->condWait);
}

void FehlerMenue::zeigeFehlerMenue() {
	GrafikHandler::gebeGrafikHandler()->setzeAnzeigeElement(
			FehlerMenue::fehlerMenue->hintergrund);

	while (true) {
#if defined _WIN32 || defined __CYGWIN__
		string input = "";
		getline(cin, input);

		FehlerMenue::fehlerMenue->buttonOk->beimKlicken(0);
#else
		pthread_mutex_lock(&FehlerMenue::fehlerMenue->mutexWait);
		pthread_cond_wait(&FehlerMenue::fehlerMenue->condWait,
				&FehlerMenue::fehlerMenue->mutexWait);
		pthread_mutex_unlock(&FehlerMenue::fehlerMenue->mutexWait);
#endif

		FehlerMenue::fehlerMenue->hintergrund->setzeTastaturAnzeigen(false);
		FehlerMenue::fehlerMenue->textFehler->sichtbarkeit(false);
		FehlerMenue::fehlerMenue->buttonOk->sichtbarkeit(false);

		exit(0);
	}
}

void FehlerMenue::ok() {
	pthread_mutex_lock(&FehlerMenue::fehlerMenue->mutexWait);
	pthread_cond_signal(&FehlerMenue::fehlerMenue->condWait);
	pthread_mutex_unlock(&FehlerMenue::fehlerMenue->mutexWait);
}
