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

#include "KontrollerHandler.h"

#include <cstdlib>
#if defined _WIN32 || defined __CYGWIN__
#else /* __wii__ */
#include <wiiuse/wpad.h>
#endif /* __wii__ */
#include "../gui/GrafikHandler.h"

using namespace std;

KontrollerHandler* KontrollerHandler::kontrollerHandler =
		new KontrollerHandler();

KontrollerHandler::KontrollerHandler() {
	WPAD_Init();
	WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);
	WPAD_SetVRes(0, 640, 480);
}

KontrollerHandler::~KontrollerHandler() {
	WPAD_Shutdown();
}

KontrollerHandler *KontrollerHandler::gebeKontrollerHandler() {
	return KontrollerHandler::kontrollerHandler;
}

void KontrollerHandler::aktualisiere() {
	WPAD_ScanPads();
	WPADData *Data = WPAD_Data(WPAD_CHAN_0);
	WPADData data = *Data;

	WPAD_IR(WPAD_CHAN_0, &(data.ir));

	this->setzeCursorPosition(data.ir.x, data.ir.y, data.ir.angle);

	u32 gedrueckt = WPAD_ButtonsDown(0);
	//u32 losgelassen = WPAD_ButtonsUp(0);
	//u32 gehalten = WPAD_ButtonsHeld(0);

	if (gedrueckt) {
		this->gedrueckt(gedrueckt);
	}

	if (gedrueckt & WPAD_BUTTON_HOME) {
		exit(0);
	}
}

void KontrollerHandler::setzeCursorPosition(float x, float y, float angle) {
	GrafikHandler::gebeGrafikHandler()->setzeCursorPosition(x, y, angle);
}

void KontrollerHandler::gedrueckt(u32 gedrueckt) {
	GrafikHandler::gebeGrafikHandler()->gedrueckt(gedrueckt);
}
