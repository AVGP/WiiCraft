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

#include "Debug.h"

#ifdef DEBUG_ON
#if defined __wii__
#include <sdcard/wiisd_io.h>
#include <fat.h>
#include <stdio.h>
#endif
#include "../exception/ExcDateiOeffnen.h"

using namespace std;

bool Debug::mount = false;

void Debug::schreibeLog(string dateiName, string nachricht, bool flag) {
	Debug::initSD();
	FILE * pFile;
	string s = "w";

	if (flag == Debug::DATEI_ERWEITERN) {
		s = "a";
	}

#if defined _WIN32 || defined __CYGWIN__
	string replace = "sd:/apps/WiiCraft/";
	string with = "/cygdrive/c/";
	int pos = dateiName.find(replace);
	dateiName.erase(pos, replace.length());
	dateiName.insert(pos, with);
#endif

	pFile = fopen(dateiName.data(), s.data());
	if (pFile != NULL) {
		fprintf(pFile, "%s", nachricht.data());

		fclose(pFile);
	} else {
		throw ExcDateiOeffnen(dateiName.data());
	}
}

void Debug::initSD() {
	// SD-Karte nur einmal mounten
	if (!Debug::mount) {
		Debug::mount = true;
	} else {
		return;
	}

	Debug::deInitSD();
#if defined __wii__
	fatMountSimple("sd", &__io_wiisd);
#endif
}

void Debug::deInitSD() {
#if defined __wii__
	fatUnmount("sd:/");
	__io_wiisd.shutdown();
#endif
}

void Debug::schreibePaketLog(string paketName, string nachricht) {
	if (paketName != "Paket03ChatMessage") {
		return;
	}

	printf("%s: %s\n", paketName.data(), nachricht.data());
}

void Debug::start() {
	Debug::schreibeLog("sd:/apps/WiiCraft/exception.log", "",
			Debug::DATEI_UEBERSCHREIBEN);
	Debug::schreibeLog("sd:/apps/WiiCraft/Paket.log", "",
			Debug::DATEI_UEBERSCHREIBEN);
	Debug::schreibeLog("sd:/apps/WiiCraft/Debug.log", "",
			Debug::DATEI_UEBERSCHREIBEN);
}
#endif
