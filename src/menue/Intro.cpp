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

#include "Intro.h"

#include <unistd.h>
#include <time.h>
#include "../gui/GrafikHandler.h"
#include "../gui/Hintergrund.h"
#include "../gui/Bild.h"
#include "../gui/Text.h"

using namespace std;

bool Intro::abbruch = false;

void Intro::zeigeIntro() {

	Hintergrund *h1 = new Hintergrund();
	Hintergrund *h2 = new Hintergrund();

	h1->setzeBeimKlicken(&Intro::abbrechen);
	h2->setzeBeimKlicken(&Intro::abbrechen);

	Bild *b1 = new Bild(256, 150, "logo_orbitalfrosch");
	Bild *b2 = new Bild(144, 160, "logo");
	h1->fuegeUnterElementHinzu(b1);
	h2->fuegeUnterElementHinzu(b2);

	Text *t1 = new Text(256, 280, "Orbitalfrosch");
	Text *t2 = new Text(275, 295, "presents");
	h1->fuegeUnterElementHinzu(t1);
	h1->fuegeUnterElementHinzu(t2);

	GrafikHandler::gebeGrafikHandler()->setzeAnzeigeElement(h1);

	time_t start;
	time_t ende;

	time(&start);

	while (true) {
		time(&ende);

		if (Intro::abbruch || ((int) difftime(start, ende) * -1) == 5) {
			break;
		}
		usleep(16666);
	}

	Intro::abbruch = false;
	GrafikHandler::gebeGrafikHandler()->setzeAnzeigeElement(h2);

	time(&start);

	while (true) {
		time(&ende);

		if (Intro::abbruch || ((int) difftime(start, ende) * -1) == 5) {
			break;
		}
		usleep(16666);
	}
	Intro::abbruch = false;
}

void Intro::abbrechen() {
	Intro::abbruch = true;
}
