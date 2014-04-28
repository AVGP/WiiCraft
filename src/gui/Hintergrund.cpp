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

#include "Hintergrund.h"

#include "GrafikHandler.h"
#include "Tastatur.h"
#if defined _WIN32 || defined __CYGWIN__
#include "../util/WiiFunction.h"
#else /* __wii__ */
#include <grrlib.h>
#endif /* __wii__ */

using namespace std;

Hintergrund::Hintergrund() {
	ContainerElement::setzeStandardWerte();

	this->tastatur = Tastatur::gebeTastatur();
	this->setzeX(0);
	this->setzeY(0);
	this->setzeHoehe(480);
	this->setzeBreite(640);
	this->setzeTastaturAnzeigen(false);

	this->fuegeUnterElementHinzu(this->tastatur);
}

Hintergrund::Hintergrund(string _textur) {
	ContainerElement::setzeStandardWerte();

	this->tastatur = Tastatur::gebeTastatur();
	this->textur = _textur;
	this->setzeX(0);
	this->setzeY(0);
	this->setzeHoehe(480);
	this->setzeBreite(640);
	this->setzeTastaturAnzeigen(false);

	this->fuegeUnterElementHinzu(this->tastatur);
}

Hintergrund::~Hintergrund() {
}

void Hintergrund::zeichneElement() {
	if (this->istSichtbar()) {
		GRRLIB_2dMode();

		if (!this->textur.empty()) {
			for (int breite = -40; breite < (640 + 80); breite += 32) {
				for (int hoehe = -40; hoehe < (480 + 80); hoehe += 32) {
					GRRLIB_DrawImg(
							breite,
							hoehe,
							GrafikHandler::gebeGrafikHandler()->gebeBild(
									this->textur), 0, 2, 2, 0xFFFFFFFF);
				}
			}
		} else {
			GRRLIB_FillScreen(0x000000ff);
		}

		this->zeichneUnterElement();

		if (this->istCursorAnzeigbar()) {
			this->zeichneCursor();
		}
	}
}

void Hintergrund::setzeTastaturAnzeigen(bool _tastaturAnzeigen) {
	this->tastatur->sichtbarkeit(_tastaturAnzeigen);
}

bool Hintergrund::zeigeTastatur() {
	return this->tastatur->istSichtbar();
}
