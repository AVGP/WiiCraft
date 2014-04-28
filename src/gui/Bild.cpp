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

#include "Bild.h"

#include "GrafikHandler.h"
#if defined _WIN32 || defined __CYGWIN__
#include "../util/WiiFunction.h"
#else /* __wii__ */
#include <grrlib.h>
#endif /* __wii__ */

using namespace std;

Bild::Bild(float _x, float _y, string _textur, float _drehung,
		float _skralierungX, float _skralierungY, unsigned int _farbe) {
	this->setzeStandardWerte();

	this->setzeX(_x);
	this->setzeY(_y);
	this->setzeHoehe(
			GrafikHandler::gebeGrafikHandler()->gebeBild(_textur)->h
					* _skralierungY);
	this->setzeBreite(
			GrafikHandler::gebeGrafikHandler()->gebeBild(_textur)->w
					* _skralierungX);
	this->textur = _textur;
	this->drehung = _drehung;
	this->skralierungX = _skralierungX;
	this->skralierungY = _skralierungY;
	this->farbe = farbe;
}

Bild::Bild(float _x, float _y, string _textur) {
	this->setzeStandardWerte();

	this->setzeX(_x);
	this->setzeY(_y);
	this->setzeHoehe(GrafikHandler::gebeGrafikHandler()->gebeBild(_textur)->h);
	this->setzeBreite(GrafikHandler::gebeGrafikHandler()->gebeBild(_textur)->w);
	this->textur = _textur;
	this->drehung = 0;
	this->skralierungX = 1;
	this->skralierungY = 1;
	this->farbe = 0xffffffff;
}

Bild::~Bild() {
}

void Bild::zeichneElement() {
	if (this->istSichtbar()) {
		GRRLIB_2dMode();
		GRRLIB_DrawImg(this->gebeX(), this->gebeY(),
				GrafikHandler::gebeGrafikHandler()->gebeBild(this->textur),
				this->drehung, this->skralierungX, this->skralierungY,
				this->farbe);
	}
}
