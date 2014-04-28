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

#include "Socket.h"

#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <errno.h>
#if defined _WIN32 || defined __CYGWIN__
#include <arpa/inet.h>
#include <netdb.h>
#elif defined __wii__
#include <ogcsys.h>
#include <network.h>
#include <ogc/lwp_watchdog.h>
#endif
#include "NetzwerkKonfigurator.h"
#include "../exception/ExcSocketVerbindungVerloren.h"

using namespace std;

bool Socket::connect(const char *host, const u16 port) {

	if (!NetzwerkKonfigurator::initialisieren()) {
		return false;
	}

	this->socket = net_socket(AF_INET, SOCK_STREAM, 0);
	if (this->socket < 0) {
		return false;
	}

	struct sockaddr_in server;

	struct in_addr myaddr;

	if (inet_aton(host, &myaddr)) {
		memset(&server, 0, sizeof(struct sockaddr_in));
		server.sin_family = PF_INET;
#if defined __wii__
		server.sin_len = sizeof(struct sockaddr_in);
#endif
		server.sin_port = htons(port);
		memcpy((char *) &server.sin_addr, &myaddr.s_addr,
				sizeof(struct in_addr));
	} else {
		struct hostent *hp = net_gethostbyname(host);

		if (!hp || !(hp->h_addrtype == PF_INET)) {
			return false;
		}

		memset(&server, 0, sizeof(struct sockaddr_in));
		server.sin_family = PF_INET;
#if defined __wii__
		server.sin_len = sizeof(struct sockaddr_in);
#endif
		server.sin_port = htons(port);
		memcpy((char *) &server.sin_addr, hp->h_addr_list[0], hp->h_length);
	}

	server.sin_port = htons(port);
	if (net_connect(this->socket, (struct sockaddr *) &server, sizeof(server))
			< 0) {
		return false;
	}

	return true;
}

bool Socket::disconnect() {
	return net_close(this->socket);
}

int Socket::write(const void *buf, int len) {
	s32 anzahlGeschriebeneByte = net_write(this->socket, buf, len);

	// Verbindung verloren
	if (anzahlGeschriebeneByte <= 0) {
		throw ExcSocketVerbindungVerloren(errno, "write", len);
	}

	return anzahlGeschriebeneByte;
}

int Socket::sendAll(const char* const buf, const int size) {
	int bytesSent = 0; // Anzahl Bytes die wir bereits vom Buffer gesendet haben
	do {
		int result = net_send(this->socket, buf + bytesSent, size - bytesSent,
				0);
		if (result < 0) { // Wenn send einen Wert < 0 zurueck gibt deutet dies auf einen Fehler hin.
			return -1;
		}
		bytesSent += result;
	} while (bytesSent < size);

	return bytesSent;
}

int Socket::read(void *buf, int len) {
	s32 anzahlGeleseneByte = net_read(this->socket, buf, len);

	// Verbindung verloren
	if (anzahlGeleseneByte <= 0) {
		throw ExcSocketVerbindungVerloren(errno, "read", len);
	}

	return anzahlGeleseneByte;
}

// Liest eine Zeile des Sockets in einen stringstream
bool Socket::getLine(stringstream& line) {
	for (char c; net_recv(this->socket, &c, 1, 0) > 0; line << c) {
		if (c == '\n') {
			return true;
		}
	}
	return false;
}

int Socket::recv(char *buf, int len, int flags) {
	return net_recv(this->socket, buf, len, flags);
}
