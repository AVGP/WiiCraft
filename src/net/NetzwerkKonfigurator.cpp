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

#include "NetzwerkKonfigurator.h"

#if defined _WIN32 || defined __CYGWIN__
#elif defined __wii__
#include <network.h>
#endif

using namespace std;

char NetzwerkKonfigurator::localip[16];
char NetzwerkKonfigurator::netmask[16];
char NetzwerkKonfigurator::gateway[16];
bool NetzwerkKonfigurator::istInitialisieren;

bool NetzwerkKonfigurator::initialisieren() {
	signed int ret;

	if (NetzwerkKonfigurator::istInitialisieren) {
		return true;
	}

#if defined __wii__
	ret = if_config(NetzwerkKonfigurator::localip, NetzwerkKonfigurator::netmask, NetzwerkKonfigurator::gateway, true);
#else
	ret = 0;
#endif
	if (ret >= 0) {
		NetzwerkKonfigurator::istInitialisieren = true;
		return true;
	} else {
		NetzwerkKonfigurator::istInitialisieren = false;
		return false;
	}
}
