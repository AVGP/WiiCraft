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

#include "Spieler.h"

#include <stdlib.h>
#if defined _WIN32 || defined __CYGWIN__
#include <pthread.h>
#else
#include "../util/pthread.h"
#endif
#include "../thread/SpielerBewegungSendenThread.h"

using namespace std;

Spieler *Spieler::spieler = NULL;

Spieler::Spieler(int entityId) {
	pthread_mutex_init(&this->mutex, NULL);

	this->setzeId(entityId);

	Entity::setzeKoordinaten(0, 0, 0);

	this->winkel = 0;
	this->abstand = 0;
	this->haltung = 0;
	this->istAufBoden = false;
	this->istFliegend = false;
	this->istFliegenMoeglich = false;
	this->istEinfachesAbbauenAktiv = false;

	this->istUnverwundbar = false;
	this->lebensEnergie = 0;
	this->saettigung = 0;
	this->ueberSaettigung = 0;

	this->erfahrungsPunkteAktuelleStufe = 0;
	this->level = 0;
	this->erfahrungsPunkteGesamt = 0;

	this->spielerBewegungSendenThread = new SpielerBewegungSendenThread(this,
			this->x, this->y, this->z, this->winkel, this->abstand,
			this->haltung, this->istAufBoden, this->istFliegend);
	this->spielerBewegungSendenThread->start();

	Entity::setzeEntity(this);
}

Spieler::~Spieler() {
	this->spielerBewegungSendenThread->stop();
	this->spielerBewegungSendenThread->join();

	pthread_mutex_destroy(&this->mutex);
}

Spieler *Spieler::getSpieler() {
	return Spieler::spieler;
}

void Spieler::initialisiereSpieler(int entityId) {
	if (Spieler::spieler != NULL) {
		delete Spieler::spieler;
		Entity::deinitialisiere();
	}

	Entity::initialisiere();
	Spieler::spieler = new Spieler(entityId);
}

void Spieler::setzeKoordinaten(double _x, double _y, double _z) {
	Entity::setzeKoordinaten(_x, _y, _z);

	this->spielerBewegungSendenThread->aktualisieren();
}

void Spieler::setzeBlickfeld(float _winkel, float _abstand) {
	pthread_mutex_lock(&this->mutex);
	this->winkel = _winkel;
	this->abstand = _abstand;
	pthread_mutex_unlock(&this->mutex);
}

void Spieler::setzeHaltung(double _haltung) {
	pthread_mutex_lock(&this->mutex);
	this->haltung = _haltung;
	pthread_mutex_unlock(&this->mutex);
}

void Spieler::setzeAufBoden(bool _istAufBoden) {
	pthread_mutex_lock(&this->mutex);
	this->istAufBoden = _istAufBoden;
	pthread_mutex_unlock(&this->mutex);
}

double Spieler::gebeHaltung() {
	pthread_mutex_lock(&this->mutex);
	double _haltung = this->haltung;
	pthread_mutex_unlock(&this->mutex);

	return _haltung;
}

float Spieler::gebeWinkel() {
	pthread_mutex_lock(&this->mutex);
	float _winkel = this->winkel;
	pthread_mutex_unlock(&this->mutex);

	return _winkel;
}

float Spieler::gebeAbstand() {
	pthread_mutex_lock(&this->mutex);
	double _abstand = this->abstand;
	pthread_mutex_unlock(&this->mutex);

	return _abstand;
}

bool Spieler::gebeIstAufBoden() {
	pthread_mutex_lock(&this->mutex);
	bool _istAufBoden = this->istAufBoden;
	pthread_mutex_unlock(&this->mutex);

	return _istAufBoden;
}

bool Spieler::gebeIstFliegend() {
	pthread_mutex_lock(&this->mutex);
	bool _istFliegend = this->istFliegend;
	pthread_mutex_unlock(&this->mutex);

	return _istFliegend;
}

bool Spieler::gebeIstFliegenMoeglich() {
	pthread_mutex_lock(&this->mutex);
	bool _istFliegenMoeglich = this->istFliegenMoeglich;
	pthread_mutex_unlock(&this->mutex);

	return _istFliegenMoeglich;
}

bool Spieler::gebeIstEinfachesAbbauenAktiv() {
	pthread_mutex_lock(&this->mutex);
	bool _istEinfachesAbbauenAktiv = this->istEinfachesAbbauenAktiv;
	pthread_mutex_unlock(&this->mutex);

	return _istEinfachesAbbauenAktiv;
}

bool Spieler::gebeIstUnverwundbar() {
	pthread_mutex_lock(&this->mutex);
	bool _istUnverwundbar = this->istUnverwundbar;
	pthread_mutex_unlock(&this->mutex);

	return _istUnverwundbar;
}

void Spieler::setzeFaehigkeit(bool _istFliegend, bool _istFliegenMoeglich,
		bool _istEinfachesAbbauenAktiv, bool _istUnverwundbar) {
	pthread_mutex_lock(&this->mutex);
	this->istFliegend = _istFliegend;
	this->istFliegenMoeglich = _istFliegenMoeglich;
	this->istEinfachesAbbauenAktiv = _istEinfachesAbbauenAktiv;
	this->istUnverwundbar = _istUnverwundbar;
	pthread_mutex_unlock(&this->mutex);
}

void Spieler::setzeLebensEnergie(short _lebensEnergie) {
	pthread_mutex_lock(&this->mutex);
	this->lebensEnergie = _lebensEnergie;
	pthread_mutex_unlock(&this->mutex);
}

void Spieler::setzeSaettigung(short _saettigung) {
	pthread_mutex_lock(&this->mutex);
	this->saettigung = _saettigung;
	pthread_mutex_unlock(&this->mutex);
}

void Spieler::setzeUeberSaettigung(float _ueberSaettigung) {
	pthread_mutex_lock(&this->mutex);
	this->ueberSaettigung = _ueberSaettigung;
	pthread_mutex_unlock(&this->mutex);
}

void Spieler::setzeErfahrungsPunkteAktuelleStufe(
		float _erfahrungsPunkteAktuelleStufe) {
	pthread_mutex_lock(&this->mutex);
	this->erfahrungsPunkteAktuelleStufe = _erfahrungsPunkteAktuelleStufe;
	pthread_mutex_unlock(&this->mutex);
}

void Spieler::setzeLevel(short _level) {
	pthread_mutex_lock(&this->mutex);
	this->level = _level;
	pthread_mutex_unlock(&this->mutex);
}

void Spieler::setzeErfahrungsPunkteGesamt(short _erfahrungsPunkteGesamt) {
	pthread_mutex_lock(&this->mutex);
	this->erfahrungsPunkteGesamt = _erfahrungsPunkteGesamt;
	pthread_mutex_unlock(&this->mutex);
}
