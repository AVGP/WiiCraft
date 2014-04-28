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

#include "Paket66WindowClick.h"

#include <cstdlib>
#include "../../net/DataOutputStream.h"
#include "../../entity/Slot.h"

using namespace std;

Paket66WindowClick::Paket66WindowClick(byte _windowId, short _slot,
		byte _rightClick, short _actionNumber, bool _shift,
		Slot *_clickedItem) {
	PaketClient::id = 0x66;
	PaketClient::prio = 50;

	this->windowId = _windowId;
	this->slot = _slot;
	this->rightClick = _rightClick;
	this->actionNumber = _actionNumber;
	this->shift = _shift;
	this->clickedItem = _clickedItem;
}

Paket66WindowClick::~Paket66WindowClick() {
	free(this->clickedItem);
}

void Paket66WindowClick::schreibePaketInhalt(DataOutputStream *out) {
	out->schreibeByte(this->windowId);
	out->schreibeShort(this->slot);
	out->schreibeByte(this->rightClick);
	out->schreibeShort(this->actionNumber);
	out->schreibeBoolean(this->shift);
	Slot::schreibeSlot(out, this->clickedItem);
}
