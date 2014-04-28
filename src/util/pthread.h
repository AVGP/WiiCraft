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

#ifndef PTHREAD_H_
#define PTHREAD_H_

#if defined _WIN32 || defined __CYGWIN__
#else /* __wii__ */

#include <ogcsys.h>
#include <gccore.h>
#include <ogc/lwp.h>
#define STACKSIZE 4*1024

typedef lwp_t pthread_t;
typedef mutex_t pthread_mutex_t;
typedef lwpq_t pthread_cond_t;
typedef void* pthread_mutexattr_t;
typedef void* pthread_condattr_t;
typedef int pthread_attr_t;

inline int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
		void *(*start_routine)(void*), void *arg);

inline int pthread_join(pthread_t thread, void **value_ptr) {
	return LWP_JoinThread(thread, value_ptr);
}

inline int pthread_mutex_init(pthread_mutex_t *mutex,
		const pthread_mutexattr_t *attr);
inline int pthread_mutex_destroy(pthread_mutex_t *mutex);
inline int pthread_mutex_lock(pthread_mutex_t *mutex);
inline int pthread_mutex_unlock(pthread_mutex_t *mutex);

inline int pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *attr);
inline int pthread_cond_destroy(pthread_cond_t *cond);
inline int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
inline int pthread_cond_signal(pthread_cond_t *cond);

inline int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
		void *(*start_routine)(void*), void *arg) {
	*thread = 0;
	return LWP_CreateThread(thread, start_routine, arg, 0, STACKSIZE, 64);
}

inline int pthread_mutex_init(pthread_mutex_t *mutex,
		const pthread_mutexattr_t *attr) {
	return LWP_MutexInit(mutex, 0);
}
inline int pthread_mutex_destroy(pthread_mutex_t *mutex) {
	return LWP_MutexDestroy(*mutex);
}
inline int pthread_mutex_lock(pthread_mutex_t *mutex) {
	return LWP_MutexLock(*mutex);
}
inline int pthread_mutex_trylock(pthread_mutex_t *mutex) {
	return LWP_MutexTryLock(*mutex);
}
inline int pthread_mutex_unlock(pthread_mutex_t *mutex) {
	return LWP_MutexUnlock(*mutex);
}

inline int pthread_cond_init(pthread_cond_t *cond,
		const pthread_condattr_t *attr) {
	return LWP_InitQueue(cond);
}
inline int pthread_cond_destroy(pthread_cond_t *cond) {
	LWP_CloseQueue(*cond);
	return 0;
}
inline int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex) {
	pthread_mutex_unlock(mutex);
	signed int r = LWP_ThreadSleep(*cond);
	pthread_mutex_lock(mutex);
	return r;
}
inline int pthread_cond_signal(pthread_cond_t *cond) {
	LWP_ThreadSignal(*cond);

	return 0;
}

#endif /* __wii__ */

#endif /* PTHREAD_H_ */
