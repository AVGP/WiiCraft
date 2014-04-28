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

/*
 * Weitere Infos unter:
 * http://wiki.vg/Authentication#Login
 */

#include "Session.h"

#include <cstdio>
#include <sstream>
#include "../net/HTTP.h"
#include "../exception/ExcSocketHTTP.h"
#include "../exception/ExcSocketHTTPServerLoginFehlgeschlagen.h"
#include "../exception/ExcSocketHTTPServerJoinFehlgeschlagen.h"
#include "../exception/ExcSocketHTTPServerRefreshFehlgeschlagen.h"
#include "../util/ClientInfo.h"

using namespace std;

string Session::currentVersion;
string Session::downloadTicket;
string Session::caseCorrectUsername;
string Session::sessionId;

void Session::anmelden(string benutzer, string passwort) {
	Session::caseCorrectUsername = benutzer;
	/**
	 *string get = "/?user=";
	 *get.append(benutzer);
	 *get.append("&password=");
	 *get.append(passwort);
	 *get.append("&version=");
	 *get.append(ClientInfo::clientLauncherVersion);
  **
	 *HTTP *h = new HTTP();
	 *string response;
  **
	 *try {
	 *	response = h->get("login.minecraft.net", 80, get);
	 *} catch (ExcSocketHTTP &exception) {
	 *	throw ExcSocketHTTPServerLoginFehlgeschlagen(
	 *			"Verbindung zu login.minecraft.net nicht moeglich");
	 *}
  **
	 *if (response == "Old version") {
	 *	throw ExcSocketHTTPServerLoginFehlgeschlagen("Client-Launcher zu alt");
	 *} else if (response == "Bad login") {
	 *	throw ExcSocketHTTPServerLoginFehlgeschlagen("Benutzer oder Passwort falsch");
	 *}
  **
	 *short pos1 = response.find(':');
	 *if ((unsigned) pos1 == string::npos) {
	 *	throw ExcSocketHTTPServerLoginFehlgeschlagen("Login Fehler #1");
	 *}
  **
	 *short pos2 = response.find(':', pos1 + 1);
	 *if ((unsigned) pos2 == string::npos) {
	 *	throw ExcSocketHTTPServerLoginFehlgeschlagen("Login Fehler #2");
	 *}
  **
	 *short pos3 = response.find(':', pos2 + 1);
	 *if ((unsigned) pos3 == string::npos) {
	 *	throw ExcSocketHTTPServerLoginFehlgeschlagen("Login Fehler #3");
	 *}
  **
	 *Session::currentVersion = response.substr(0, pos1);
	 *Session::downloadTicket = response.substr(pos1 + 1, pos2 - pos1 - 1);
	 *Session::caseCorrectUsername = response.substr(pos2 + 1, pos3 - pos2 - 1);
	 *Session::sessionId = response.substr(pos3 + 1);
  **
	 *if (Session::currentVersion.length() == 0
	 *		|| Session::downloadTicket.length() == 0
	 *		|| Session::caseCorrectUsername.length() == 0
	 *		|| Session::sessionId.length() == 0) {
	 *	throw ExcSocketHTTPServerLoginFehlgeschlagen("Login Fehler #4");
	 *}
  **
	 *std::istringstream s(Session::currentVersion);
	 *double currentVersionD;
	 *if (!(s >> currentVersionD)) {
	 *	throw ExcSocketHTTPServerLoginFehlgeschlagen(
	 *			"Server-Version konnte nicht erkannt werden");
	 *}
	 *std::istringstream c(ClientInfo::clientVersion);
	 *double clientVersionD;
	 *if (!(c >> clientVersionD)) {
	 *	throw ExcSocketHTTPServerLoginFehlgeschlagen(
	 *			"Client-Version konnte nicht erkannt werden");
	 *}
  **
	 *if (clientVersionD > currentVersionD) {
	 *	string fehler = "Server-Version zu alt, Server: ";
	 *	fehler.append(Session::currentVersion);
	 *	fehler.append(" Client: ");
		fehler.append(ClientInfo::clientVersion);

		throw ExcSocketHTTPServerLoginFehlgeschlagen(fehler);
	} else if (clientVersionD < currentVersionD) {
		string fehler = "Client-Version zu alt, Server: ";
		fehler.append(Session::currentVersion);
		fehler.append(" Client: ");
		fehler.append(ClientInfo::clientVersion);

		throw ExcSocketHTTPServerLoginFehlgeschlagen(fehler);
		}
	 */

}

void Session::tretteServerBei(string serverHash) {
	/**
	 *string get = "/game/joinserver.jsp?user=";
	 *get.append(Session::caseCorrectUsername);
	 *get.append("&sessionId=");
	 *get.append(Session::sessionId);
	 *get.append("&serverId=");
	 *get.append(serverHash);
  **
	 *HTTP *h = new HTTP();
	 *string response;
  **
	 *try {
	 *	response = h->get("session.minecraft.net", 80, get);
	 *} catch (ExcSocketHTTP &exception) {
	 *	throw ExcSocketHTTPServerJoinFehlgeschlagen(
	 *			"Verbindung zu session.minecraft.net nicht moeglich");
	 *}
  **
	 *if (response != "OK") {
	 *	string ergebnis = "Response: ";
	 *	ergebnis.append(response);

		throw ExcSocketHTTPServerJoinFehlgeschlagen(ergebnis);
	}
	 */

}

void Session::bleibeVerbunden() {
	/**
	 *string get = "/session?name=";
	 *get.append(Session::caseCorrectUsername);
	 *get.append("&session=");
	 *get.append(Session::sessionId);
  **
	 *HTTP *h = new HTTP();
  **
	 *try {
	 *	// Rueckgabe wird nicht ausgewertet
	 *	h->get("login.minecraft.net", 80, get);
	 *} catch (ExcSocketHTTP &exception) {
	 *	throw ExcSocketHTTPServerRefreshFehlgeschlagen(
				"Verbindung zu login.minecraft.net nicht moeglich");
	}
	 */

}

string Session::gebeBenutzer() {
	return Session::caseCorrectUsername;
}
