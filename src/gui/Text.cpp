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

#include "Text.h"

#include "GrafikHandler.h"
#if defined _WIN32 || defined __CYGWIN__
#include "../util/WiiFunction.h"
#else /* __wii__ */
#include <grrlib.h>
#endif /* __wii__ */

using namespace std;

Text::Text(float _x, float _y, string _text) {
	TextElement::setzeStandardWerte();

	pthread_mutex_init(&this->mutexFarbe, NULL);

	this->setzeX(_x);
	this->setzeY(_y);
	this->setzeText(_text);
	this->berechneAusmasse();
	this->setzeTextFarbe(0xffffffff);
	this->setzeHintergrundFarbe(0);
}

Text::~Text() {
	pthread_mutex_destroy(&this->mutexFarbe);
}

void Text::berechneAusmasse() {
	string _text = this->gebeText();

	this->setzeHoehe(_text.size() ? 8 : 0);
	this->setzeBreite(8.0 * (float) _text.size());
}

void Text::zeichneElement() {
	if (this->istSichtbar()) {
		string _text = this->gebeText();
		_text = this->konvertiereAnzeigeText(_text);
		u32 _textFarbe = this->gebeTextFarbe();
		u32 _hintergrundFarbe = this->gebeHintergrundFarbe();

		float _x = this->gebeX();
		float _y = this->gebeY();

		GRRLIB_2dMode();
		if (_hintergrundFarbe > 0) {
			float _breite = this->gebeBreite();
			float _hoehe = this->gebeHoehe();
			GRRLIB_Rectangle(_x, _y, _breite, _hoehe, _hintergrundFarbe, 1);
		}
		GRRLIB_Printf(_x, _y,
				GrafikHandler::gebeGrafikHandler()->gebeBild("font"),
				_textFarbe, 1, _text.data());
	}
}

void Text::setzeTextFarbe(u32 _textFarbe) {
	pthread_mutex_lock(&this->mutexFarbe);
	this->textFarbe = _textFarbe;
	pthread_mutex_unlock(&this->mutexFarbe);
}

u32 Text::gebeTextFarbe() {
	pthread_mutex_lock(&this->mutexFarbe);
	u32 _textFarbe = this->textFarbe;
	pthread_mutex_unlock(&this->mutexFarbe);

	return _textFarbe;
}

void Text::setzeHintergrundFarbe(u32 _hintergrundFarbe) {
	pthread_mutex_lock(&this->mutexFarbe);
	this->hintergrundFarbe = _hintergrundFarbe;
	pthread_mutex_unlock(&this->mutexFarbe);
}

u32 Text::gebeHintergrundFarbe() {
	pthread_mutex_lock(&this->mutexFarbe);
	u32 _hintergrundFarbe = this->hintergrundFarbe;
	pthread_mutex_unlock(&this->mutexFarbe);

	return _hintergrundFarbe;
}
