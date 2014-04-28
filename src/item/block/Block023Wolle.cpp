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

#include "Block023Wolle.h"

#include "../ItemManager.h"

using namespace std;

Item *Block023Wolle::gebeInstanz() {
	return new Block023Wolle();
}

bool Block023Wolle::registiereItem() {
	ItemManager::registriereItem(new Block023Wolle());

	return true;
}

Block023Wolle::Block023Wolle() {
	this->setzeStandardWerte();

	Item::id = 0x023;
}

void Block023Wolle::zeichne(float x, float y, float z, byte meta) {
	if (meta == 1) { // Orange
		ItemBlock::zeichneBlock(x, y, z, 210);
	} else if (meta == 2) { // Magenta
		ItemBlock::zeichneBlock(x, y, z, 194);
	} else if (meta == 3) { // Hellblau
		ItemBlock::zeichneBlock(x, y, z, 178);
	} else if (meta == 4) { // Gelb
		ItemBlock::zeichneBlock(x, y, z, 162);
	} else if (meta == 5) { // Hellgruen
		ItemBlock::zeichneBlock(x, y, z, 146);
	} else if (meta == 6) { // Pink
		ItemBlock::zeichneBlock(x, y, z, 130);
	} else if (meta == 7) { // Grau
		ItemBlock::zeichneBlock(x, y, z, 114);
	} else if (meta == 8) { // Hellgrau
		ItemBlock::zeichneBlock(x, y, z, 225);
	} else if (meta == 9) { // Cyan
		ItemBlock::zeichneBlock(x, y, z, 209);
	} else if (meta == 10) { // Lila
		ItemBlock::zeichneBlock(x, y, z, 193);
	} else if (meta == 11) { // Blau
		ItemBlock::zeichneBlock(x, y, z, 177);
	} else if (meta == 12) { // Braun
		ItemBlock::zeichneBlock(x, y, z, 161);
	} else if (meta == 13) { // Dunkelgruen
		ItemBlock::zeichneBlock(x, y, z, 145);
	} else if (meta == 14) { // Rot
		ItemBlock::zeichneBlock(x, y, z, 129);
	} else if (meta == 15) { // Schwarz
		ItemBlock::zeichneBlock(x, y, z, 113);
	} else { // Weiss
		ItemBlock::zeichneBlock(x, y, z, 64);
	}
}

bool Block023Wolle::istDurchsichtig() {
	return false;
}
