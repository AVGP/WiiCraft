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

#include "SpielThread.h"

#include <unistd.h>
#include "../protokoll/Verbindung.h"
#include "../menue/Intro.h"
#include "../menue/UpdateMenue.h"
#include "../menue/AnmeldungMenue.h"
#include "../menue/ServerAuswahlMenue.h"
#include "../menue/Anzeige3D.h"
#include "../welt/Welt.h"
#include "../welt/ChunkLaden.h"
#include "../entity/Spieler.h"

using namespace std;

SpielThread::SpielThread() {
}

SpielThread::~SpielThread() {
}

int SpielThread::exec() {
	Intro::zeigeIntro();

	UpdateMenue::initialisiere();
	UpdateMenue::zeigeUpdateMenue();

	AnmeldungMenue::initialisiere();
	AnmeldungMenue::zeigeAnmeldungMenue();

	UpdateMenue::deinitialisiere();

	ServerAuswahlMenue::initialisiere();
	ServerAuswahlMenue::zeigeServerAuswahlMenue();
	AnmeldungMenue::deinitialisiere();

	// Chunks im vorraus laden
	while (true) {
		Welt *welt = Welt::gebeWelt();
		if (welt != 0) {
			ChunkLaden::gebeChunkLaden()->aktualisiereChunks(
					Spieler::getSpieler()->gebeChunkX(),
					Spieler::getSpieler()->gebeChunkZ());

			if (welt->gebeAnzahlGeladeneChunks()
					== ChunkLaden::gebeMaximaleAnzahlGeladeneChunks()) {
				break;
			}
		}
		usleep(50);
	}

	Anzeige3D::initialisiere();
	Anzeige3D::zeigeAnzeige3D();
	ServerAuswahlMenue::deinitialisiere();

	Verbindung::warte();

	return 0;
}
