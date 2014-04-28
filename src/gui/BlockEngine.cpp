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

#include "BlockEngine.h"

#include <cmath>
#if defined _WIN32 || defined __CYGWIN__
#include "../util/WiiFunction.h"
#else /* __wii__ */
#include <grrlib.h>
#endif /* __wii__ */
#include "../welt/Welt.h"
#include "../entity/Spieler.h"
#include "../welt/ChunkLaden.h"
#include "GrafikHandler.h"
#include "../util/GrrlibErsatz.h"

#define PI 3.14159265

using namespace std;

BlockEngine::BlockEngine() {
	ContainerElement::setzeStandardWerte();

	this->setzeX(0);
	this->setzeY(0);
	this->setzeHoehe(480);
	this->setzeBreite(640);
}

BlockEngine::~BlockEngine() {
}

void BlockEngine::zeichneElement() {
	if (this->istSichtbar()) {
		this->zeichne3DElemente();
		this->zeichneUnterElement();
	}
}

void BlockEngine::zeichne3DElemente() {
	Spieler *spieler = Spieler::getSpieler();

	if (spieler != NULL) {
		float spielerX = (float) spieler->gebeX();
		float spielerY = ((float) spieler->gebeY()) + 1.62f;
		float spielerZ = (float) spieler->gebeZ();

		float abstand = spieler->gebeAbstand() * PI / 180;
		float winkel = spieler->gebeWinkel() * PI / 180;

		float viewX = -cos(abstand) * sin(winkel);
		float viewY = -sin(abstand);
		float viewZ = cos(abstand) * cos(winkel);

		GRRLIB_Camera3dSettings(spielerX, spielerY, spielerZ, 0, 1, 0,
				spielerX + viewX, spielerY + viewY, spielerZ + viewZ);
		GRRLIB_3dMode(0.001, 48, 70, 0, 0);

		GrrlibErsatz::GRRLIB_SetTexture(
				GrafikHandler::gebeGrafikHandler()->gebeBild("terrain"), 0);

		Welt *welt = Welt::gebeWelt();
		if (welt != NULL) {
			welt->zeichne();
		}
	}
}

void BlockEngine::setzeCursorPosition(float x, float y, float angle) {
	float x_zentrum = (x - 320);
	float y_zentrum = (y - 240);

	if (x_zentrum < 10 && x_zentrum > -10) {
		x_zentrum = 0;
	}

	if (y_zentrum < 10 && y_zentrum > -10) {
		y_zentrum = 0;
	}

	Spieler *spieler = Spieler::getSpieler();

	if (spieler != NULL) {
		float abstand = spieler->gebeAbstand() + (0.007 * y_zentrum);
		float winkel = spieler->gebeWinkel() + (0.007 * x_zentrum);

		if (abstand > 90)
			abstand = 90;
		if (abstand < -90)
			abstand = -90;
		if (winkel > 180)
			winkel -= 360;
		if (winkel < -180)
			winkel += 360;

		spieler->setzeBlickfeld(winkel, abstand);
	}
}
