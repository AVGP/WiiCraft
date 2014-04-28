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

#include "ItemBlock.h"

#include "../gui/GrafikHandler.h"
#include "../util/GrrlibErsatz.h"
#if defined _WIN32 || defined __CYGWIN__
#include "../util/WiiFunction.h"
#else /* __wii__ */
#include <grrlib.h>
#endif /* __wii__ */

using namespace std;

void ItemBlock::setzeBlockType(byte _typ) {
	this->typ = _typ;
}

void ItemBlock::setzeBlockMetadata(byte _data) {
	this->meta = _data;
}

void ItemBlock::setzeBlockLicht(byte _licht) {
	this->blockLicht = _licht;
}

void ItemBlock::setzeBlockHimmelLicht(byte _licht) {
	this->himmelLicht = _licht;
}

void ItemBlock::zeichneBlock(float x, float y, float z, int textur) {
	float x1 = x + 1.0f;
	float y1 = y + 1.0f;
	float z1 = z + 1.0f;

	// sued
	guVector sued[4] = { { x, y1, z1 }, { x1, y1, z1 }, { x1, y, z1 }, { x, y,
			z1 } };
	GrrlibErsatz::GRRLIB_DrawImgQuadTile(sued, textur);

	// nord
	guVector nord[4] =
			{ { x1, y1, z }, { x, y1, z }, { x, y, z }, { x1, y, z } };
	GrrlibErsatz::GRRLIB_DrawImgQuadTile(nord, textur);

	// ost
	guVector ost[4] = { { x1, y1, z1 }, { x1, y1, z }, { x1, y, z },
			{ x1, y, z1 } };
	GrrlibErsatz::GRRLIB_DrawImgQuadTile(ost, textur);

	// west
	guVector west[4] =
			{ { x, y1, z }, { x, y1, z1 }, { x, y, z1 }, { x, y, z } };
	GrrlibErsatz::GRRLIB_DrawImgQuadTile(west, textur);

	// oben
	guVector oben[4] = { { x, y1, z }, { x1, y1, z }, { x1, y1, z1 }, { x, y1,
			z1 } };
	GrrlibErsatz::GRRLIB_DrawImgQuadTile(oben, textur);

	// unten
	guVector unten[4] =
			{ { x1, y, z }, { x, y, z }, { x, y, z1 }, { x1, y, z1 } };
	GrrlibErsatz::GRRLIB_DrawImgQuadTile(unten, textur);
}

void ItemBlock::zeichnePflanze(float x, float y, float z, int textur,
		byte art) {
	float x1 = x + 1.0f;
	float y1 = y + 1.0f;
	float z1 = z + 1.0f;

	if (art == 1) {
		// sued
		guVector sued[4] = { { x, y1, z1 - 0.2 }, { x1, y1, z1 - 0.2 }, { x1, y,
				z1 - 0.2 }, { x, y, z1 - 0.2 } };
		GrrlibErsatz::GRRLIB_DrawImgQuadTile(sued, textur);

		// nord
		guVector nord[4] = { { x1, y1, z + 0.2 }, { x, y1, z + 0.2 }, { x, y, z
				+ 0.2 }, { x1, y, z + 0.2 } };
		GrrlibErsatz::GRRLIB_DrawImgQuadTile(nord, textur);

		// ost
		guVector ost[4] = { { x1 - 0.2, y1, z1 }, { x1 - 0.2, y1, z }, { x1
				- 0.2, y, z }, { x1 - 0.2, y, z1 } };
		GrrlibErsatz::GRRLIB_DrawImgQuadTile(ost, textur);

		// west
		guVector west[4] = { { x + 0.2, y1, z }, { x + 0.2, y1, z1 }, { x + 0.2,
				y, z1 }, { x + 0.2, y, z } };
		GrrlibErsatz::GRRLIB_DrawImgQuadTile(west, textur);
	} else {
		// ost
		guVector ost[4] = { { x1, y1, z1 }, { x, y1, z }, { x, y, z }, { x1, y,
				z1 } };
		GrrlibErsatz::GRRLIB_DrawImgQuadTile(ost, textur);

		// west
		guVector west[4] = { { x1, y1, z }, { x, y1, z1 }, { x, y, z1 }, { x1,
				y, z } };
		GrrlibErsatz::GRRLIB_DrawImgQuadTile(west, textur);
	}
}
