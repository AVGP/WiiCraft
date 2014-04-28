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

#include "GrafikElement.h"

using namespace std;

GrafikElement::~GrafikElement() {
	pthread_mutex_destroy(&this->mutexSichtbarkeit);
	pthread_mutex_destroy(&this->mutexDeaktiviert);
	pthread_mutex_destroy(&this->mutexCursorDarueber);
	pthread_mutex_destroy(&this->mutexPosition);
	pthread_mutex_destroy(&this->mutexAusfuehrenBeimKlicken);
	pthread_mutex_destroy(&this->mutexAusgewaehlt);
}

void GrafikElement::setzeStandardWerte() {
	pthread_mutex_init(&this->mutexSichtbarkeit, NULL);
	pthread_mutex_init(&this->mutexDeaktiviert, NULL);
	pthread_mutex_init(&this->mutexCursorDarueber, NULL);
	pthread_mutex_init(&this->mutexPosition, NULL);
	pthread_mutex_init(&this->mutexAusfuehrenBeimKlicken, NULL);
	pthread_mutex_init(&this->mutexAusgewaehlt, NULL);

	this->sichtbarkeit(true);
	this->deaktivieren(false);
	this->auswaehlen(false);
	this->setzeCursorDarueber(false);
	this->setzeBeimKlicken(&GrafikElement::tueNix);
	this->setzeX(0);
	this->setzeY(0);
	this->setzeBreite(0);
	this->setzeHoehe(0);
}

bool GrafikElement::istAusgewaehlt() {
	pthread_mutex_lock(&this->mutexAusgewaehlt);
	bool _ausgewaehlt = this->ausgewaehlt;
	pthread_mutex_unlock(&this->mutexAusgewaehlt);

	return _ausgewaehlt;
}

void GrafikElement::auswaehlen(bool _ausgewaehlt) {
	pthread_mutex_lock(&this->mutexAusgewaehlt);
	this->ausgewaehlt = _ausgewaehlt;
	pthread_mutex_unlock(&this->mutexAusgewaehlt);
}

void GrafikElement::sichtbarkeit(bool _sichtbar) {
	pthread_mutex_lock(&this->mutexSichtbarkeit);
	this->sichtbar = _sichtbar;
	pthread_mutex_unlock(&this->mutexSichtbarkeit);

	this->setzeCursorDarueber(false);
}

bool GrafikElement::istSichtbar() {
	pthread_mutex_lock(&this->mutexSichtbarkeit);
	bool _sichtbar = this->sichtbar;
	pthread_mutex_unlock(&this->mutexSichtbarkeit);

	return _sichtbar;
}

void GrafikElement::deaktivieren(bool _deaktiviert) {
	pthread_mutex_lock(&this->mutexDeaktiviert);
	this->deaktiviert = _deaktiviert;
	pthread_mutex_unlock(&this->mutexDeaktiviert);
}

bool GrafikElement::istDeaktiviert() {
	pthread_mutex_lock(&this->mutexDeaktiviert);
	bool _deaktiviert = this->deaktiviert;
	pthread_mutex_unlock(&this->mutexDeaktiviert);

	return _deaktiviert;
}

void GrafikElement::setzeCursorDarueber(bool _cursorDarueber) {
	pthread_mutex_lock(&this->mutexCursorDarueber);
	this->cursorDarueber = _cursorDarueber;
	pthread_mutex_unlock(&this->mutexCursorDarueber);
}

bool GrafikElement::istCursorDarueber() {
	pthread_mutex_lock(&this->mutexCursorDarueber);
	bool _cursorDarueber = this->cursorDarueber;
	pthread_mutex_unlock(&this->mutexCursorDarueber);

	return _cursorDarueber;
}

float GrafikElement::gebeX() {
	pthread_mutex_lock(&this->mutexPosition);
	float _x = this->x;
	pthread_mutex_unlock(&this->mutexPosition);

	return _x;
}

float GrafikElement::gebeY() {
	pthread_mutex_lock(&this->mutexPosition);
	float _y = this->y;
	pthread_mutex_unlock(&this->mutexPosition);

	return _y;
}

float GrafikElement::gebeBreite() {
	pthread_mutex_lock(&this->mutexPosition);
	float _breite = this->breite;
	pthread_mutex_unlock(&this->mutexPosition);

	return _breite;
}

float GrafikElement::gebeHoehe() {
	pthread_mutex_lock(&this->mutexPosition);
	float _hoehe = this->hoehe;
	pthread_mutex_unlock(&this->mutexPosition);

	return _hoehe;
}

void GrafikElement::setzeX(float _x) {
	pthread_mutex_lock(&this->mutexPosition);
	this->x = _x;
	pthread_mutex_unlock(&this->mutexPosition);
}

void GrafikElement::setzeY(float _y) {
	pthread_mutex_lock(&this->mutexPosition);
	this->y = _y;
	pthread_mutex_unlock(&this->mutexPosition);
}

void GrafikElement::setzeBreite(float _breite) {
	pthread_mutex_lock(&this->mutexPosition);
	this->breite = _breite;
	pthread_mutex_unlock(&this->mutexPosition);
}

void GrafikElement::setzeHoehe(float _hoehe) {
	pthread_mutex_lock(&this->mutexPosition);
	this->hoehe = _hoehe;
	pthread_mutex_unlock(&this->mutexPosition);
}

void GrafikElement::setzeBeimKlicken(void(*_ausfuehrenBeimKlicken)()) {
	this->ausfuehrenBeimKlicken = _ausfuehrenBeimKlicken;
}

void GrafikElement::beimKlicken(u32 gedrueckt) {
	this->ausfuehrenBeimKlicken();
}

void GrafikElement::tueNix() {
}
