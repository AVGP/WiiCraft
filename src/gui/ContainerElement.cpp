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

#include "ContainerElement.h"

#include <cmath>
#include "GrafikHandler.h"
#if defined _WIN32 || defined __CYGWIN__
#include "../util/WiiFunction.h"
#else /* __wii__ */
#include <grrlib.h>
#endif /* __wii__ */

using namespace std;

ContainerElement::~ContainerElement() {
	pthread_mutex_destroy(&this->mutexUnterElemente);
	pthread_mutex_destroy(&this->mutexCursor);
	pthread_mutex_destroy(&this->mutexCursorAnzeigbar);
}

void ContainerElement::setzeStandardWerte() {
	GrafikElement::setzeStandardWerte();

	pthread_mutex_init(&this->mutexUnterElemente, NULL);
	pthread_mutex_init(&this->mutexCursor, NULL);
	pthread_mutex_init(&this->mutexCursorAnzeigbar, NULL);

	this->setzeCursorAnzeigen(false);
}

void ContainerElement::fuegeUnterElementHinzu(GrafikElement *neuesElement) {
	pthread_mutex_lock(&this->mutexUnterElemente);
	this->unterElemente.push_back(neuesElement);
	pthread_mutex_unlock(&this->mutexUnterElemente);
}

void ContainerElement::zeichneUnterElement() {
	pthread_mutex_lock(&this->mutexUnterElemente);
	if (!this->unterElemente.empty()) {
		for (list<GrafikElement *>::iterator it = this->unterElemente.begin();
				it != this->unterElemente.end(); ++it) {
			(*it)->zeichneElement();
		}
	}
	pthread_mutex_unlock(&this->mutexUnterElemente);
}

void ContainerElement::setzeCursorPosition(float x, float y, float angle) {
	bool positionGeandert = false;
	pthread_mutex_lock(&this->mutexCursor);

	if (this->cursorX != x || this->cursorY != y) {
		positionGeandert = true;
	}

	this->cursorX = x;
	this->cursorY = y;
	this->cursorAngle = angle;
	pthread_mutex_unlock(&this->mutexCursor);

	if (positionGeandert) {
		this->informiereUnterElementeUeberCursorDarueber();
	}
}

void ContainerElement::informiereUnterElementeUeberCursorDarueber() {

	pthread_mutex_lock(&this->mutexCursor);
	float _x = this->cursorX;
	float _y = this->cursorY;
	float _angle = this->cursorAngle;
	pthread_mutex_unlock(&this->mutexCursor);

	pthread_mutex_lock(&this->mutexUnterElemente);
	if (!this->unterElemente.empty()) {
		bool gefunden = false;

		for (std::list<GrafikElement*>::reverse_iterator it =
				this->unterElemente.rbegin(); it != this->unterElemente.rend();
				++it) {
			if (!(*it)->istSichtbar()) {
				continue;
			}

			float eX = (*it)->gebeX();
			float eY = (*it)->gebeY();

			if (!gefunden && _x >= eX && _x <= eX + (*it)->gebeBreite()
					&& _y >= eY && _y <= eY + (*it)->gebeHoehe()) {
				(*it)->setzeCursorDarueber(true);
				ContainerElement* unterContainer =
						dynamic_cast<ContainerElement*>(*it);
				if (unterContainer != 0) {
					unterContainer->setzeCursorPosition(_x, _y, _angle);
				}
				gefunden = true;
			} else {
				ContainerElement* unterContainer =
						dynamic_cast<ContainerElement*>(*it);
				if (unterContainer != 0) {
					unterContainer->setzeCursorPosition(_x, _y, _angle);
				}
				(*it)->setzeCursorDarueber(false);
			}
		}
	}
	pthread_mutex_unlock(&this->mutexUnterElemente);
}

void ContainerElement::gedrueckt(u32 gedrueckt) {
	bool gefunden = false;

	pthread_mutex_lock(&this->mutexCursor);
	float _x = this->cursorX;
	float _y = this->cursorY;
	pthread_mutex_unlock(&this->mutexCursor);

	pthread_mutex_lock(&this->mutexUnterElemente);
	if (!this->unterElemente.empty()) {

		for (std::list<GrafikElement*>::reverse_iterator it =
				this->unterElemente.rbegin(); it != this->unterElemente.rend();
				++it) {
			if (!(*it)->istSichtbar()) {
				continue;
			}

			float eX = (*it)->gebeX();
			float eY = (*it)->gebeY();

			if (_x >= eX && _x <= eX + (*it)->gebeBreite() && _y >= eY
					&& _y <= eY + (*it)->gebeHoehe()) {
				(*it)->beimKlicken(gedrueckt);
				gefunden = true;

				ContainerElement* unterContainer =
						dynamic_cast<ContainerElement*>(*it);
				if (unterContainer != 0) {
					unterContainer->gedrueckt(gedrueckt);
				}
				break;
			}
		}
	}
	pthread_mutex_unlock(&this->mutexUnterElemente);

	if (!gefunden) {
		this->beimKlicken(gedrueckt);
	}
}

void ContainerElement::zeichneCursor() {
	pthread_mutex_lock(&this->mutexCursor);
	float _x = this->cursorX;
	float _y = this->cursorY;
	float angle = this->cursorAngle;
	pthread_mutex_unlock(&this->mutexCursor);

	GRRLIB_DrawImg(_x, _y,
			GrafikHandler::gebeGrafikHandler()->gebeBild("cursor1"),
			fmod(angle + 180, 360), 1, 1, 0xffffffff);
	GRRLIB_DrawImg(_x, _y,
			GrafikHandler::gebeGrafikHandler()->gebeBild("cursor2"),
			fmod(angle + 270, 360), 1, 1, 0xffffffff);
	GRRLIB_DrawImg(_x, _y,
			GrafikHandler::gebeGrafikHandler()->gebeBild("cursor3"),
			fmod(angle + 90, 360), 1, 1, 0xffffffff);
	GRRLIB_DrawImg(_x, _y,
			GrafikHandler::gebeGrafikHandler()->gebeBild("cursor4"), angle, 1,
			1, 0xffffffff);
}

void ContainerElement::setzeCursorAnzeigen(bool _anzeigen) {
	pthread_mutex_lock(&this->mutexCursorAnzeigbar);
	this->cursorAnzeigbar = _anzeigen;
	pthread_mutex_unlock(&this->mutexCursorAnzeigbar);
}

bool ContainerElement::istCursorAnzeigbar() {
	pthread_mutex_lock(&this->mutexCursorAnzeigbar);
	bool anzeigen = this->cursorAnzeigbar;
	pthread_mutex_unlock(&this->mutexCursorAnzeigbar);

	return anzeigen;
}
