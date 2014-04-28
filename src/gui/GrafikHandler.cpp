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

#include "GrafikHandler.h"

#include <cmath>
#include <sstream>
#include "../exception/ExcGrafikNichtGefunden.h"
#include "Hintergrund.h"
#include "BlockEngine.h"
#include "bilder/bildMenueHintergrund.h"
#include "bilder/terrain.h"
#include "bilder/logo_orbitalfrosch.h"
#include "bilder/logo.h"
#include "bilder/font.h"
#include "bilder/cursor1.h"
#include "bilder/cursor2.h"
#include "bilder/cursor3.h"
#include "bilder/cursor4.h"
#include "bilder/bild_ladebalken.h"
#include "bilder/bild_button.h"
#include "../util/KontrollerHandler.h"

#ifdef DEBUG_ON
#include <time.h>
#include "../welt/Welt.h"
#include "../entity/Spieler.h"
#endif

using namespace std;

GrafikHandler *GrafikHandler::grafikHandler;
#ifdef DEBUG_ON
int GrafikHandler::blockAnzahl = 0;
#endif

void GrafikHandler::initialisiere() {
	GrafikHandler::grafikHandler = new GrafikHandler();
	GrafikHandler::grafikHandler->start();
}

GrafikHandler *GrafikHandler::gebeGrafikHandler() {
	return GrafikHandler::grafikHandler;
}

GrafikHandler::GrafikHandler() {
	this->gestoppt = false;
	this->element = new Hintergrund();
	this->ausgewaehltesElement = this->element;

	pthread_mutex_init(&this->mutexStop, NULL);
	pthread_mutex_init(&this->mutexZeichne, NULL);

	GRRLIB_Init();
	GRRLIB_SetAntiAliasing(false);

	this->ladeBilder();
	this->ladeTexturMatrix();

	GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xff);
}

GrafikHandler::~GrafikHandler() {
	GRRLIB_Exit();

	pthread_mutex_destroy(&this->mutexStop);
	pthread_mutex_destroy(&this->mutexZeichne);
}

int GrafikHandler::exec() {
#ifdef DEBUG_ON
	int fps = 0;
	int fpsNeu = 0;
	time_t alteZeit;
	time_t neueZeit;
	time(&alteZeit);
	time(&neueZeit);
#endif

	while (!this->istGestopped()) {
		KontrollerHandler::gebeKontrollerHandler()->aktualisiere();

		pthread_mutex_lock(&this->mutexZeichne);
		this->element->zeichneElement();
		pthread_mutex_unlock(&this->mutexZeichne);

#ifdef DEBUG_ON
		GRRLIB_2dMode();
		GRRLIB_Printf(0, 20,
				GrafikHandler::gebeGrafikHandler()->gebeBild("font"),
				0xffffffff, 1, "FPS: %i", fps);
		GRRLIB_Printf(0, 30,
				GrafikHandler::gebeGrafikHandler()->gebeBild("font"),
				0xffffffff, 1, "Bloecke: %i", GrafikHandler::blockAnzahl);
		GrafikHandler::blockAnzahl = 0;

		Welt *welt = Welt::gebeWelt();
		if (welt != 0) {
			string chunks = "Chunks: ";
			ostringstream stream;

			if (stream << welt->gebeAnzahlGeladeneChunks()) {
			} else {
				stream << "0";
			}
			stream << "/";
			if (stream << welt->gebeAnzahlChunks()) {
			} else {
				stream << "0";
			}
			chunks.append(stream.str().data());

			string uhrzeit = "Uhrzeit: ";
			uhrzeit.append(welt->gebeUhrzeitString());

			GRRLIB_Printf(0, 40,
					GrafikHandler::gebeGrafikHandler()->gebeBild("font"),
					0xffffffff, 1, chunks.data());

			GRRLIB_Printf(0, 50,
					GrafikHandler::gebeGrafikHandler()->gebeBild("font"),
					0xffffffff, 1, uhrzeit.data());
		}

		Spieler *spieler = Spieler::getSpieler();
		if (spieler != 0) {
			string x_str = "x: ";
			string y_str = "y: ";
			string z_str = "z: ";
			ostringstream x_stream;
			ostringstream y_stream;
			ostringstream z_stream;

			x_stream << (float) spieler->gebeX();
			y_stream << (float) spieler->gebeY() + 1.62f;
			z_stream << (float) spieler->gebeZ();

			x_str.append(x_stream.str().data());
			y_str.append(y_stream.str().data());
			z_str.append(z_stream.str().data());

			GRRLIB_Printf(0, 60,
					GrafikHandler::gebeGrafikHandler()->gebeBild("font"),
					0xffffffff, 1, x_str.data());
			GRRLIB_Printf(0, 70,
					GrafikHandler::gebeGrafikHandler()->gebeBild("font"),
					0xffffffff, 1, y_str.data());
			GRRLIB_Printf(0, 80,
					GrafikHandler::gebeGrafikHandler()->gebeBild("font"),
					0xffffffff, 1, z_str.data());
			GRRLIB_Printf(0, 90,
					GrafikHandler::gebeGrafikHandler()->gebeBild("font"),
					0xffffffff, 1, "Chunk X: %i", spieler->gebeChunkX());
			GRRLIB_Printf(0, 100,
					GrafikHandler::gebeGrafikHandler()->gebeBild("font"),
					0xffffffff, 1, "Chunk Z: %i", spieler->gebeChunkZ());

			float pitch = spieler->gebeAbstand();
			float yaw = spieler->gebeWinkel();

			float viewX = -cos(pitch) * sin(yaw);
			float viewY = -sin(pitch);
			float viewZ = cos(pitch) * cos(yaw);

			string abstand_str = "Abstand: ";
			string winkel_str = "Winkel: ";
			string kamera_x_str = "Kamera X: ";
			string kamera_y_str = "Kamera Y: ";
			string kamera_z_str = "Kamera Z: ";
			string view_x_str = "View X: ";
			string view_y_str = "View Y: ";
			string view_z_str = "View Z: ";
			ostringstream abstand_stream;
			ostringstream winkel_stream;
			ostringstream kamera_x_stream;
			ostringstream kamera_y_stream;
			ostringstream kamera_z_stream;
			ostringstream view_x_stream;
			ostringstream view_y_stream;
			ostringstream view_z_stream;

			abstand_stream << pitch;
			winkel_stream << yaw;
			kamera_x_stream << (float) spieler->gebeX() + viewX;
			kamera_y_stream << (float) spieler->gebeY() + viewY + 1.62f;
			kamera_z_stream << (float) spieler->gebeZ() + viewZ;
			view_x_stream << viewX;
			view_y_stream << viewY;
			view_z_stream << viewZ;

			abstand_str.append(abstand_stream.str().data());
			winkel_str.append(winkel_stream.str().data());
			kamera_x_str.append(kamera_x_stream.str().data());
			kamera_y_str.append(kamera_y_stream.str().data());
			kamera_z_str.append(kamera_z_stream.str().data());
			view_x_str.append(view_x_stream.str().data());
			view_y_str.append(view_y_stream.str().data());
			view_z_str.append(view_z_stream.str().data());

			GRRLIB_Printf(0, 110,
					GrafikHandler::gebeGrafikHandler()->gebeBild("font"),
					0xffffffff, 1, abstand_str.data());
			GRRLIB_Printf(0, 120,
					GrafikHandler::gebeGrafikHandler()->gebeBild("font"),
					0xffffffff, 1, winkel_str.data());

			GRRLIB_Printf(0, 130,
					GrafikHandler::gebeGrafikHandler()->gebeBild("font"),
					0xffffffff, 1, kamera_x_str.data());
			GRRLIB_Printf(0, 140,
					GrafikHandler::gebeGrafikHandler()->gebeBild("font"),
					0xffffffff, 1, kamera_y_str.data());
			GRRLIB_Printf(0, 150,
					GrafikHandler::gebeGrafikHandler()->gebeBild("font"),
					0xffffffff, 1, kamera_z_str.data());
			GRRLIB_Printf(0, 160,
					GrafikHandler::gebeGrafikHandler()->gebeBild("font"),
					0xffffffff, 1, view_x_str.data());
			GRRLIB_Printf(0, 170,
					GrafikHandler::gebeGrafikHandler()->gebeBild("font"),
					0xffffffff, 1, view_y_str.data());
			GRRLIB_Printf(0, 180,
					GrafikHandler::gebeGrafikHandler()->gebeBild("font"),
					0xffffffff, 1, view_z_str.data());

		}

		fpsNeu++;
		time(&neueZeit);
		if (((int) difftime(alteZeit, neueZeit) * -1) > 1) {
			time(&alteZeit);
			fps = fpsNeu / 2;
			fpsNeu = 0;
		}
#endif

		GRRLIB_Render();
	}
	return 0;
}

void GrafikHandler::stop() {
	pthread_mutex_lock(&this->mutexStop);
	this->gestoppt = true;
	pthread_mutex_unlock(&this->mutexStop);
}

bool GrafikHandler::istGestopped() {
	bool b = false;

	pthread_mutex_lock(&this->mutexStop);
	b = this->gestoppt;
	pthread_mutex_unlock(&this->mutexStop);

	return b;
}

void GrafikHandler::setzeAnzeigeElement(GrafikElement *neuesElement) {
	pthread_mutex_lock(&this->mutexZeichne);
	this->element = neuesElement;
	this->setzeAusgewaehltesElement(this->element);
	pthread_mutex_unlock(&this->mutexZeichne);
}

void GrafikHandler::ladeBilder() {
	this->bilder["bildMenueHintergrund"] = GRRLIB_LoadTexture(
			bildMenueHintergrund);
	this->bilder["terrain"] = GRRLIB_LoadTexture(terrain);
	GRRLIB_InitTileSet(this->bilder["terrain"], 16, 16, 0);
	this->bilder["logo_orbitalfrosch"] = GRRLIB_LoadTexture(logo_orbitalfrosch);
	this->bilder["logo"] = GRRLIB_LoadTexture(logo);
	this->bilder["font"] = GRRLIB_LoadTexture(font);
	GRRLIB_InitTileSet(this->bilder["font"], 8, 8, 0);
	this->bilder["cursor1"] = GRRLIB_LoadTexture(cursor1);
	this->bilder["cursor2"] = GRRLIB_LoadTexture(cursor2);
	this->bilder["cursor3"] = GRRLIB_LoadTexture(cursor3);
	this->bilder["cursor4"] = GRRLIB_LoadTexture(cursor4);
	this->bilder["bild_ladebalken"] = GRRLIB_LoadTexture(bild_ladebalken);
	GRRLIB_InitTileSet(this->bilder["bild_ladebalken"], 100, 4, 0);
	this->bilder["bild_button"] = GRRLIB_LoadTexture(bild_button);
	GRRLIB_InitTileSet(this->bilder["bild_button"], 16, 16, 0);
}

void GrafikHandler::ladeTexturMatrix() {
	GRRLIB_texImg *terrain = this->gebeBild("terrain");
	this->texturMatrix = new TexturMatrix[256];
	for (short nr = 0; nr < 256; nr++) {
		this->texturMatrix[nr].s1 = (nr % terrain->nbtilew)
				* terrain->ofnormaltexx;
		this->texturMatrix[nr].s2 = this->texturMatrix[nr].s1
				+ terrain->ofnormaltexx;
		this->texturMatrix[nr].t1 = (int) (nr / terrain->nbtilew)
				* terrain->ofnormaltexy;
		this->texturMatrix[nr].t2 = this->texturMatrix[nr].t1
				+ terrain->ofnormaltexy;
	}
}

TexturMatrix GrafikHandler::gebeTexturMatrix(int nr) {
	return this->texturMatrix[nr];
}

GRRLIB_texImg *GrafikHandler::gebeBild(string name) {
	return this->bilder[name];
}

void GrafikHandler::setzeCursorPosition(float x, float y, float angle) {
	BlockEngine *blockEngine = dynamic_cast<BlockEngine *>(this->element);
	if (blockEngine != 0) {
		blockEngine->setzeCursorPosition(x, y, angle);
	} else {
		((ContainerElement *) this->element)->setzeCursorPosition(x, y, angle);
	}
}

void GrafikHandler::gedrueckt(u32 gedrueckt) {
	((ContainerElement *) this->element)->gedrueckt(gedrueckt);
}

void GrafikHandler::setzeAusgewaehltesElement(
		GrafikElement *_ausgewaehltesElement) {
	this->ausgewaehltesElement->auswaehlen(false);
	this->ausgewaehltesElement = _ausgewaehltesElement;
	this->ausgewaehltesElement->auswaehlen(true);
}

GrafikElement *GrafikHandler::gebeAusgewaehltesElement() {
	return this->ausgewaehltesElement;
}
