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

#ifndef PAKET0DPLAYERPOSITIONLOOK_H_
#define PAKET0DPLAYERPOSITIONLOOK_H_

#include "../PaketServer.h"
#include "../PaketClient.h"

namespace std {

class DataOutputStream;
class DataInputStream;

class Paket0DPlayerPositionLook: public PaketServer, public PaketClient {
public:
	Paket0DPlayerPositionLook(double _x, double _y, double _stance, double _z,
			float _yaw, float _pitch, bool _onGround);
	PaketServer *gebeInstanz();
	static bool registierePaket();
	void schreibePaketInhalt(DataOutputStream *out);
	void lesePaketInhalt(DataInputStream *in);
	void verarbeitePaket();
private:

	double x;
	double y;
	double z;
	double stance;
	float yaw;
	float pitch;
	bool onGround;

	Paket0DPlayerPositionLook();
};
}
#endif /* PAKET0DPLAYERPOSITIONLOOK_H_ */
