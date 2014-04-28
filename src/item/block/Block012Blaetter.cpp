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

#include "Block012Blaetter.h"

#include "../ItemManager.h"

using namespace std;

Item *Block012Blaetter::gebeInstanz() {
	return new Block012Blaetter();
}

bool Block012Blaetter::registiereItem() {
	ItemManager::registriereItem(new Block012Blaetter());

	return true;
}

Block012Blaetter::Block012Blaetter() {
	this->setzeStandardWerte();

	Item::id = 0x012;
}

void Block012Blaetter::zeichne(float x, float y, float z, byte meta) {
	// Wie auch beim Baumstamm entscheidet der Wert ueber die Baumart. Zusaetzlich
	// springt der Wert auf 8, wenn ein Block neben den Blaettern updated. In
	// diesem Fall wird ueberprueft, ob die Blaetter decayen sollen. Vom Spieler
	// platzierte Blaetter haben den Wert 4. Dieser Wert verhindert das Decayen
	// der Blaetter und ueberschreibt den Wert 8.

	if ((meta & 0x3) == 0) { // Normale Blaetter
		ItemBlock::zeichneBlock(x, y, z, 52);
	} else if ((meta & 0x3) == 1) { // Fichtenblaetter
		ItemBlock::zeichneBlock(x, y, z, 132);
	} else if ((meta & 0x3) == 2) { // Birkenblaetter
		ItemBlock::zeichneBlock(x, y, z, 52);
	} else if ((meta & 0x3) == 3) { // Dschungelblaetter
		ItemBlock::zeichneBlock(x, y, z, 196);
	}
}

bool Block012Blaetter::istDurchsichtig() {
	return true;
}
