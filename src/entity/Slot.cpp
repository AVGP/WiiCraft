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

#include "Slot.h"

#include <sstream>
#include "../net/DataInputStream.h"
#include "../item/ItemManager.h"
#include "../item/Item.h"
#include "../item/item/Item166Karte.h"
#include "../exception/ExcItemUnbekanntesItem.h"
#include "../exception/ExcSlot.h"
#include "../menue/FehlerMenue.h"
#include "../util/Debug.h"

using namespace std;

vector<Slot *> Slot::leseSlotArray(DataInputStream *in, short count) {
	vector<Slot *> slotArray;

	for (short i = 0; i < count; i++) {
		slotArray.push_back(Slot::leseSlot(in));
	}

	return slotArray;
}

Slot *Slot::leseSlot(DataInputStream *in) {
	short itemId = in->leseShort();
	if (itemId >= 0) {
		byte stapelGroesse = in->leseByte();
		short itemHaltbarkeit = in->leseShort();

		Item *item = NULL;

		try {
			item = ItemManager::getInstanz(itemId);
		} catch (ExcItemUnbekanntesItem &exception) {
			stringstream ss;
			ss << "Fehler: Item(";
			ss << exception.gebeItemId();
			ss << ") noch nicht eingebaut.";
			FehlerMenue::initialisiere(ss.str());
			FehlerMenue::zeigeFehlerMenue();
		}

		item->setzeHaltbarkeit(itemHaltbarkeit);

		if (item->istZerstoerbar()) {
			short byteAnzahl = in->leseShort();
			if (byteAnzahl >= 0) {

				byte *kartenDaten = new byte[byteAnzahl];
				for (short i = 0; i < byteAnzahl; i++) {
					kartenDaten[i] = in->leseByte();
				}

				if (itemId == 0x166) {
					((Item166Karte *) item)->setzeKartenDaten(kartenDaten);
				} else {
					throw ExcSlot(itemId);
				}
			}
		}

		Slot *slot = new Slot(item, stapelGroesse);
		return slot;
	}

	return new Slot();
}

void Slot::schreibeSlot(DataOutputStream *out, Slot *slot) {
	// TODO muss noch umgesetzt werden
}

Slot::Slot(Item *_item, byte _stapelGroesse) {
	this->item = _item;
	this->stapelGroesse = _stapelGroesse;
}

Slot::Slot() {
}

Slot::~Slot() {
	delete this->item;
}
