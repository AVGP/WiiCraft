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

#ifndef ENTITY_H_
#define ENTITY_H_

#include <map>
#if defined _WIN32 || defined __CYGWIN__
#include <pthread.h>
#else
#include "../util/pthread.h"
#endif

namespace std {

class Entity {
public:
	static void initialisiere();
	static void deinitialisiere();
	static Entity *gebeEntity(int _id);
	static void loescheEntity(int _id);
	void setzeId(int _id);
	void setzeKoordinaten(double _x, double _y, double _z);
	static void setzeEntity(Entity *entity);

	double gebeX();
	double gebeY();
	double gebeZ();
	int gebeChunkX();
	int gebeChunkZ();
	int gebeId();
protected:
	static map<int, Entity *> entities;

	int id;
	double x;
	double y;
	double z;
	int chunkX;
	int chunkZ;

	pthread_mutex_t mutex;
	static pthread_mutex_t staticmutex;

	Entity();

private:
	Entity(int _id);
};

}
#endif /* ENTITY_H_ */
