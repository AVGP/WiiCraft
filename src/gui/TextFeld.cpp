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

#include "TextFeld.h"

#include <cmath>
#include "GrafikHandler.h"
#if defined _WIN32 || defined __CYGWIN__
#include "../util/WiiFunction.h"
#else /* __wii__ */
#include <grrlib.h>
#endif /* __wii__ */

using namespace std;

TextFeld::TextFeld(float _x, float _y) {
	TextElement::setzeStandardWerte();

	this->setzeX(_x);
	this->setzeY(_y);
	this->berechneAusmasse();
	time(&this->cursorZeit);
}

TextFeld::TextFeld(float _x, float _y, string _text) {
	TextElement::setzeStandardWerte();

	this->setzeX(_x);
	this->setzeY(_y);
	this->setzeText(_text);
	this->berechneAusmasse();
	time(&this->cursorZeit);
}

TextFeld::~TextFeld() {
}

void TextFeld::berechneAusmasse() {
	this->setzeHoehe(18);
	this->setzeBreite(104);
}

void TextFeld::zeichneElement() {
	if (this->istSichtbar()) {
		GRRLIB_2dMode();

		string _text = this->gebeText();

		bool deaktiviert = this->istDeaktiviert();
		int textFarbe = 0xffffffff;
		int textFarbeSchatten = 0x383838ff;

		float _x = this->gebeX();
		float _y = this->gebeY();
		float _breite = this->gebeBreite();
		float _hoehe = this->gebeHoehe();

		unsigned int zeichenPlatz = (unsigned int) floor(
				(_breite - 4.0 - 8.0) / 8.0);

		if (_text.size() > zeichenPlatz) {
			_text = _text.substr(_text.size() - zeichenPlatz);
		}

		if (this->istAusgewaehlt()) {
			time_t neueCursorZeit;
			time(&neueCursorZeit);

			if (((int) difftime(this->cursorZeit, neueCursorZeit) * -1) == 1) {
				_text.append("_");
			} else if (((int) difftime(this->cursorZeit, neueCursorZeit) * -1)
					> 1) {
				time(&this->cursorZeit);
			}
		}

		GRRLIB_Rectangle(_x, _y, _breite, _hoehe, 0x000000ff, 1);
		GRRLIB_Rectangle(_x, _y, _breite, _hoehe, 0xffffffff, 0);

		if (_text.size() > 0) {
			_text = this->konvertiereAnzeigeText(_text);

			// Textschatten
			if (!deaktiviert) {
				GRRLIB_Printf(_x + 3, _y + 5,
						GrafikHandler::gebeGrafikHandler()->gebeBild("font"),
						textFarbeSchatten, 1, _text.data());
			}

			// Text
			GRRLIB_Printf(_x + 2, _y + 4,
					GrafikHandler::gebeGrafikHandler()->gebeBild("font"),
					textFarbe, 1, _text.data());
		}
	}
}

