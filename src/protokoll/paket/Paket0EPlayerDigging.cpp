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
 * status:
 * 0	Started digging
 * 2	Finished digging
 * 4	Drop item
 * 5	Shoot arrow / finish eating
 *
 * face:
 * 0	-Y
 * 1	+Y
 * 2	-Z
 * 3	+Z
 * 4	-X
 * 5	+X
 */

#include "Paket0EPlayerDigging.h"

#include "../../net/DataOutputStream.h"

using namespace std;

Paket0EPlayerDigging::Paket0EPlayerDigging(byte _status, int _x, byte _y,
		int _z, byte _face) {
	PaketClient::id = 0x0e;
	PaketClient::prio = 50;

	this->status = _status;
	this->x = _x;
	this->y = _y;
	this->z = _z;
	this->face = _face;
}

void Paket0EPlayerDigging::schreibePaketInhalt(DataOutputStream *out) {
	out->schreibeByte(this->status);
	out->schreibeInt(this->x);
	out->schreibeByte(this->y);
	out->schreibeInt(this->z);
	out->schreibeByte(this->face);
}
