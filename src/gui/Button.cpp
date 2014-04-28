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

#include "Button.h"

#include <cmath>
#include "GrafikHandler.h"
#if defined _WIN32 || defined __CYGWIN__
#include "../util/WiiFunction.h"
#else /* __wii__ */
#include <grrlib.h>
#endif /* __wii__ */

using namespace std;

Button::Button(float _x, float _y, string _text) {
	TextElement::setzeStandardWerte();

	this->setzeX(_x);
	this->setzeY(_y);
	this->setzeText(_text);
	this->berechneAusmasse();
}

Button::~Button() {
}

void Button::berechneAusmasse() {
	this->setzeHoehe(16);
	this->setzeBreite(
			32 + ceil((8.0 * (float) this->gebeText().size()) / 16.0) * 16);
}

void Button::zeichneElement() {
	if (this->istSichtbar()) {
		GRRLIB_2dMode();

		string _text = this->gebeText();

		bool deaktiviert = this->istDeaktiviert();
		short index = 12;
		int textFarbe = 0xffffffff;
		int textFarbeSchatten = 0x383838ff;

		if (!deaktiviert) {
			if (this->istCursorDarueber()) {
				index = 24;
				textFarbe = 0xffffa0ff;
				textFarbeSchatten = 0x3f3f28ff;
			}
		} else {
			index = 0;
			textFarbe = 0xa0a0a0ff;
		}

		float _x = this->gebeX();
		float _y = this->gebeY();

		if (_text.size() > 0) {
			// Bild fuer Buttonanfang
			GRRLIB_DrawTile(_x, _y,
					GrafikHandler::gebeGrafikHandler()->gebeBild("bild_button"),
					0, 1, 1, 0xffffffff, index);

			// dynamische Anzahl an Bilder fuer Buttonmitte
			for (int i = 0; i < (int) ceil((float) _text.size() / 2.0); i++) {
				GRRLIB_DrawTile(
						_x + 16 + i * 16,
						_y,
						GrafikHandler::gebeGrafikHandler()->gebeBild(
								"bild_button"), 0, 1, 1, 0xffffffff,
						index + 1 + (i % 10));
			}

			// Bild fuer Buttonende
			GRRLIB_DrawTile(_x + this->gebeBreite() - 16, _y,
					GrafikHandler::gebeGrafikHandler()->gebeBild("bild_button"),
					0, 1, 1, 0xffffffff, index + 11);

			_text = this->konvertiereAnzeigeText(_text);

			// Textschatten
			if (!deaktiviert) {
				GRRLIB_Printf(_x + 17, _y + 5,
						GrafikHandler::gebeGrafikHandler()->gebeBild("font"),
						textFarbeSchatten, 1, _text.data());
			}

			// Text
			GRRLIB_Printf(_x + 16, _y + 4,
					GrafikHandler::gebeGrafikHandler()->gebeBild("font"),
					textFarbe, 1, _text.data());
		}
	}
}
