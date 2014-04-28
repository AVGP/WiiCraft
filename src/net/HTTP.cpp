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
 * http://www.c-plusplus.de/forum/169861-full
 */

#include "HTTP.h"

#include <fstream>
#include <sstream>
#include <cstring>
#include "Socket.h"
#include "../exception/ExcSocketHTTP.h"
#include "../gui/LadeBalken.h"

using namespace std;

string HTTP::get(string server, short port, string site) {
	Socket *socket = new Socket();

	bool ret = socket->connect(server.data(), port);

	if (!ret) {
		throw ExcSocketHTTP("connect");
	}

	string request = "GET ";
	request.append(site);
	request.append(" HTTP/1.1\r\nHost: ");
	request.append(server);
	request.append("\r\nConnection: close\r\n\r\n");

	socket->sendAll(request.c_str(), request.size());

	int code = 100; // 100 = Continue
	string Protokoll;
	stringstream firstLine; // Die erste Linie ist anders aufgebaut als der Rest
	while (code == 100) {
		socket->getLine(firstLine);
		firstLine >> Protokoll;
		firstLine >> code;
		if (code == 100) {
			socket->getLine(firstLine); // Leere Zeile nach Continue ignorieren
		}
	}

	if (code != 200) {
		throw ExcSocketHTTP("kein 200");
	}

	bool chunked = false;
	const int noSizeGiven = -1;
	int size = noSizeGiven;

	while (true) {
		stringstream sstream;
		socket->getLine(sstream);
		if (sstream.str() == "\r") { // Header zu Ende?
			break;
		}

		string left; // Das was links steht
		sstream >> left;
		sstream.ignore(); // ignoriert Leerzeichen

		if (left == "Content-Length:") {
			sstream >> size;
		}

		if (left == "Transfer-Encoding:") {
			string transferEncoding;
			sstream >> transferEncoding;
			if (transferEncoding == "chunked") {
				chunked = true;
			}
		}
	}

	int recvSize = 0; // Empfangene Bytes insgesamt
	char *buf = new char[1024];
	int bytesRecv = -1; // Empfangene Bytes des letzten recv

	string returnStr;

	if (size != noSizeGiven) { // Wenn die Groesse ueber Content-length gegeben wurde
		while (recvSize < size) {
			if ((bytesRecv = socket->recv(buf, sizeof(buf), 0)) <= 0) {
				// vorzeitiges Datenende
				break;
			}
			recvSize += bytesRecv;
			returnStr.append(buf, bytesRecv);
		}
	} else {
		if (!chunked) {
			while (bytesRecv != 0) {
				if ((bytesRecv = socket->recv(buf, sizeof(buf), 0)) < 0) {
					throw ExcSocketHTTP("kein Download ohne Groesse");
				}
				returnStr.append(buf, bytesRecv);
			}
		} else {
			while (true) {
				stringstream sstream;
				socket->getLine(sstream);
				int chunkSize = -1;
				sstream >> hex >> chunkSize; // Groesse des naechsten Parts einlesen
				if (chunkSize <= 0) {
					break;
				}
				recvSize = 0; // vor jeder Schleife wieder auf 0 setzen
				while (recvSize < chunkSize) {
					int bytesToRecv = chunkSize - recvSize;
					// an recv als Groesse entweder sizeof(buf) oder aber bytesToRecv uebergeben, wenn nur noch ein kleines Stueck empfangen werden muss
					if ((bytesRecv = socket->recv(
							buf,
							((unsigned) bytesToRecv > sizeof(buf) ?
									sizeof(buf) : bytesToRecv), 0)) <= 0) {
						throw ExcSocketHTTP("kein Download mit Chunked");
					}
					recvSize += bytesRecv;
					returnStr.append(buf, bytesRecv);
				}

				for (int i = 0; i < 2; ++i) {
					char temp;
					socket->recv(&temp, 1, 0);
				}
			}
		}
	}

	delete[] buf;

	return returnStr;
}

bool HTTP::getFile(string server, short port, string site, string dateiname, LadeBalken *l) {
	int gelesen = 0;
	Socket *socket = new Socket();

	bool ret = socket->connect(server.data(), port);

	if (!ret) {
		throw ExcSocketHTTP("connect");
	}

	string request = "GET ";
	request.append(site);
	request.append(" HTTP/1.1\r\nHost: ");
	request.append(server);
	request.append("\r\nConnection: close\r\n\r\n");

	socket->sendAll(request.c_str(), request.size());

	int code = 100; // 100 = Continue
	string Protokoll;
	stringstream firstLine; // Die erste Linie ist anders aufgebaut als der Rest
	while (code == 100) {
		socket->getLine(firstLine);
		firstLine >> Protokoll;
		firstLine >> code;
		if (code == 100) {
			socket->getLine(firstLine); // Leere Zeile nach Continue ignorieren
		}
	}

	if (code != 200) {
		throw ExcSocketHTTP("kein 200");
	}

	bool chunked = false;
	const int noSizeGiven = -1;
	int size = noSizeGiven;

	while (true) {
		stringstream sstream;
		socket->getLine(sstream);
		if (sstream.str() == "\r") { // Header zu Ende?
			break;
		}

		string left; // Das was links steht
		sstream >> left;
		sstream.ignore(); // ignoriert Leerzeichen

		if (left == "Content-Length:") {
			sstream >> size;
		}

		if (left == "Transfer-Encoding:") {
			string transferEncoding;
			sstream >> transferEncoding;
			if (transferEncoding == "chunked") {
				chunked = true;
			}
		}
	}

	int recvSize = 0; // Empfangene Bytes insgesamt
	char *buf = new char[1024];
	int bytesRecv = -1; // Empfangene Bytes des letzten recv
	char *file;

	string returnStr;

	if (size != noSizeGiven) { // Wenn die Groesse ueber Content-length gegeben wurde
		file = new char[size];
		while (recvSize < size) {
			if ((bytesRecv = socket->recv(buf, sizeof(buf), 0)) <= 0) {
				// vorzeitiges Datenende
				break;
			}
			memcpy(file + recvSize, buf, bytesRecv);
			recvSize += bytesRecv;
			gelesen += bytesRecv;

			l->setzeFortschritt((gelesen*100)/size);
		}
	} else {
		file = new char[1024];
		if (!chunked) {
			while (bytesRecv != 0) {
				if ((bytesRecv = socket->recv(buf, sizeof(buf), 0)) < 0) {
					throw ExcSocketHTTP("kein Download ohne Groesse");
				}
				char *tmp = new char[gelesen + bytesRecv];
				memcpy(tmp, file, gelesen);
				delete file;
				file = tmp;
				memcpy(file + gelesen, buf, bytesRecv);
				gelesen += bytesRecv;

				l->setzeFortschritt(gelesen%100);
			}
		} else {
			while (true) {
				stringstream sstream;
				socket->getLine(sstream);
				int chunkSize = -1;
				sstream >> hex >> chunkSize; // Groesse des naechsten Parts einlesen
				if (chunkSize <= 0) {
					break;
				}
				recvSize = 0; // vor jeder Schleife wieder auf 0 setzen
				while (recvSize < chunkSize) {
					int bytesToRecv = chunkSize - recvSize;
					// an recv als Groesse entweder sizeof(buf) oder aber bytesToRecv uebergeben, wenn nur noch ein kleines Stueck empfangen werden muss
					if ((bytesRecv = socket->recv(
							buf,
							((unsigned) bytesToRecv > sizeof(buf) ?
									sizeof(buf) : bytesToRecv), 0)) <= 0) {
						throw ExcSocketHTTP("kein Download mit Chunked");
					}
					char *tmp = new char[gelesen + bytesRecv];
					memcpy(tmp, file, gelesen);
					delete file;
					file = tmp;
					memcpy(file + gelesen, buf, bytesRecv);
					gelesen += bytesRecv;
					recvSize += bytesRecv;

					l->setzeFortschritt(gelesen%100);
				}

				for (int i = 0; i < 2; ++i) {
					char temp;
					socket->recv(&temp, 1, 0);
				}
			}
		}
	}

	delete[] buf;

    fstream f;
    f.open(dateiname.data(), ios::out|ios::binary);
    f.write(file, gelesen);
    f.close();

    delete[] file;

	return true;
}
