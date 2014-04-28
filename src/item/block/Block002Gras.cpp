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

#include "Block002Gras.h"

#include "../../util/GrrlibErsatz.h"
#include "../ItemManager.h"

using namespace std;

Item *Block002Gras::gebeInstanz() {
	return new Block002Gras();
}

bool Block002Gras::registiereItem() {
	ItemManager::registriereItem(new Block002Gras());

	return true;
}

Block002Gras::Block002Gras() {
	this->setzeStandardWerte();

	Item::id = 0x002;
}

void Block002Gras::zeichne(float x, float y, float z, byte meta) {
	float x1 = x + 1.0f;
	float y1 = y + 1.0f;
	float z1 = z + 1.0f;

	// TODO korrekte Farbe rendern
	// Fuer Biome und Schnee, oben wird eingefaerbt und
	// die Seiten wird Erdblock plus eingefaerbte Textur verwendet

	// sued
	guVector sued[4] = { { x, y1, z1 }, { x1, y1, z1 }, { x1, y, z1 }, { x, y,
			z1 } };
	GrrlibErsatz::GRRLIB_DrawImgQuadTile(sued, 3);

	// nord
	guVector nord[4] =
			{ { x1, y1, z }, { x, y1, z }, { x, y, z }, { x1, y, z } };
	GrrlibErsatz::GRRLIB_DrawImgQuadTile(nord, 3);

	// ost
	guVector ost[4] = { { x1, y1, z1 }, { x1, y1, z }, { x1, y, z },
			{ x1, y, z1 } };
	GrrlibErsatz::GRRLIB_DrawImgQuadTile(ost, 3);

	// west
	guVector west[4] =
			{ { x, y1, z }, { x, y1, z1 }, { x, y, z1 }, { x, y, z } };
	GrrlibErsatz::GRRLIB_DrawImgQuadTile(west, 3);

	// oben
	guVector oben[4] = { { x, y1, z }, { x1, y1, z }, { x1, y1, z1 }, { x, y1,
			z1 } };
	GrrlibErsatz::GRRLIB_DrawImgQuadTile(oben, 0);

	// unten
	guVector unten[4] =
			{ { x1, y, z }, { x, y, z }, { x, y, z1 }, { x1, y, z1 } };
	GrrlibErsatz::GRRLIB_DrawImgQuadTile(unten, 2);
}

bool Block002Gras::istDurchsichtig() {
	return false;
}
