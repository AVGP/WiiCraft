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

#include "UpdateHandler.h"

#include <sstream>
#include <fstream>
#include "../net/HTTP.h"
#include "../exception/ExcSocketHTTP.h"
#include "../exception/ExcSocketHTTPServerLoginFehlgeschlagen.h"
#include "../util/Pfad.h"
#include "../gui/LadeBalken.h"

using namespace std;

bool UpdateHandler::istUpdateVorhanden() {
	string get = "/wiicraft/meta.xml";

	HTTP * h = new HTTP();
	string response;

	try {
		response = h->get("freielancommunity.de", 80, get);
	} catch (ExcSocketHTTP &exception) {
		throw ExcSocketHTTPServerLoginFehlgeschlagen(
				"Verbindung zu freielancommunity.de nicht moeglich");
	}

	short pos1 = response.find("<release_date>");
	short pos2 = response.find("</release_date>", pos1 + 1);
	string serverReleaseVersion = response.substr(pos1 + 14, pos2 - pos1 - 14);

	string pfad = Pfad::gebePfad();
	pfad.append("meta.xml");
	string metaDatei;

	fstream fin(pfad.data());
	string buffer;
	int i = 0;
	while (fin.good()) {
		getline(fin, buffer);
		metaDatei.append(buffer);
		i++;
	}
	fin.close();

	pos1 = metaDatei.find("<release_date>");
	pos2 = metaDatei.find("</release_date>", pos1 + 1);
	string clientReleaseVersion = metaDatei.substr(pos1 + 14, pos2 - pos1 - 14);

	std::istringstream stm1;
	stm1.str(clientReleaseVersion);
	double clientReleaseVersionD;
	stm1 >> clientReleaseVersionD;

	std::istringstream stm2;
	stm2.str(serverReleaseVersion);
	double serverReleaseVersionD;
	stm2 >> serverReleaseVersionD;

	if (clientReleaseVersionD < serverReleaseVersionD) {
		return true;
	}

	return false;
}

bool UpdateHandler::ladeUpdate(LadeBalken *l) {
	if (!UpdateHandler::ladeDol(l)) {
		return false;
	}
	if (!UpdateHandler::ladeIcon(l)) {
		return false;
	}
	if (!UpdateHandler::ladeXML(l)) {
		return false;
	}

	return true;
}

bool UpdateHandler::ladeXML(LadeBalken *l) {
	string get = "/wiicraft/meta.xml";

	HTTP * h = new HTTP();

	string pfad = Pfad::gebePfad();
	pfad.append("meta.xml");

	try {
		return h->getFile("freielancommunity.de", 80, get, pfad, l);
	} catch (ExcSocketHTTP &exception) {
		throw ExcSocketHTTPServerLoginFehlgeschlagen(
				"Verbindung zu freielancommunity.de nicht moeglich");
	}

	return false;
}

bool UpdateHandler::ladeIcon(LadeBalken *l) {
	string get = "/wiicraft/icon.png";

	HTTP * h = new HTTP();

	string pfad = Pfad::gebePfad();
	pfad.append("icon.png");

	try {
		return h->getFile("freielancommunity.de", 80, get, pfad, l);
	} catch (ExcSocketHTTP &exception) {
		throw ExcSocketHTTPServerLoginFehlgeschlagen(
				"Verbindung zu freielancommunity.de nicht moeglich");
	}

	return false;
}

bool UpdateHandler::ladeDol(LadeBalken *l) {
	string get = "/wiicraft/WiiCraft.dol";

	HTTP * h = new HTTP();

	string pfad = Pfad::gebePfad();
	pfad.append("boot.dol");

	try {
		return h->getFile("freielancommunity.de", 80, get, pfad, l);
	} catch (ExcSocketHTTP &exception) {
		throw ExcSocketHTTPServerLoginFehlgeschlagen(
				"Verbindung zu freielancommunity.de nicht moeglich");
	}

	return false;
}
