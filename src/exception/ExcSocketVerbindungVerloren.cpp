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

#include "ExcSocketVerbindungVerloren.h"

#include <cstdio>
#include "../util/Debug.h"

using namespace std;

ExcSocketVerbindungVerloren::ExcSocketVerbindungVerloren(signed int _errno, string _methode, int _laenge) {
	this->errno = _errno;
	this->methode = _methode;
	this->laenge = _laenge;

#ifdef DEBUG_ON
	string errtext;

	if (this->errno == 1) {
		errtext = "EPERM"; /* Operation not permitted */
	} else if (this->errno == 2) {
		errtext = "ENOENT"; /* No such file or directory */
	} else if (this->errno == 3) {
		errtext = "ESRCH"; /* No such process */
	} else if (this->errno == 4) {
		errtext = "EINTR"; /* Interrupted system call */
	} else if (this->errno == 5) {
		errtext = "EIO"; /* I/O error */
	} else if (this->errno == 6) {
		errtext = "ENXIO"; /* No such device or address */
	} else if (this->errno == 7) {
		errtext = "E2BIG"; /* Arg list too long */
	} else if (this->errno == 8) {
		errtext = "ENOEXEC"; /* Exec format error */
	} else if (this->errno == 9) {
		errtext = "EBADF"; /* Bad file number */
	} else if (this->errno == 10) {
		errtext = "ECHILD"; /* No child processes */
	} else if (this->errno == 11) {
		errtext = "EAGAIN"; /* Try again */
	} else if (this->errno == 12) {
		errtext = "ENOMEM"; /* Out of memory */
	} else if (this->errno == 13) {
		errtext = "EACCES"; /* Permission denied */
	} else if (this->errno == 14) {
		errtext = "EFAULT"; /* Bad address */
	} else if (this->errno == 15) {
		errtext = "ENOTBLK"; /* Block device required */
	} else if (this->errno == 16) {
		errtext = "EBUSY"; /* Device or resource busy */
	} else if (this->errno == 17) {
		errtext = "EEXIST"; /* File exists */
	} else if (this->errno == 18) {
		errtext = "EXDEV"; /* Cross-device link */
	} else if (this->errno == 19) {
		errtext = "ENODEV"; /* No such device */
	} else if (this->errno == 20) {
		errtext = "ENOTDIR"; /* Not a directory */
	} else if (this->errno == 21) {
		errtext = "EISDIR"; /* Is a directory */
	} else if (this->errno == 22) {
		errtext = "EINVAL"; /* Invalid argument */
	} else if (this->errno == 23) {
		errtext = "ENFILE"; /* File table overflow */
	} else if (this->errno == 21) {
		errtext = "EMFILE"; /* Too many open files */
	} else if (this->errno == 25) {
		errtext = "ENOTTY"; /* Not a typewriter */
	} else if (this->errno == 26) {
		errtext = "ETXTBSY"; /* Text file busy */
	} else if (this->errno == 27) {
		errtext = "EFBIG"; /* File too large */
	} else if (this->errno == 28) {
		errtext = "ENOSPC"; /* No space left on device */
	} else if (this->errno == 29) {
		errtext = "ESPIPE"; /* Illegal seek */
	} else if (this->errno == 30) {
		errtext = "EROFS"; /* Read-only file system */
	} else if (this->errno == 31) {
		errtext = "EMLINK"; /* Too many links */
	} else if (this->errno == 32) {
		errtext = "EPIPE"; /* Broken pipe */
	} else if (this->errno == 33) {
		errtext = "EDOM"; /* Math argument out of domain of func */
	} else if (this->errno == 34) {
		errtext = "ERANGE"; /* Math result not representable */
	} else if (this->errno == 35) {
		errtext = "EDEADLK"; /* Resource deadlock would occur */
	} else if (this->errno == 36) {
		errtext = "ENAMETOOLONG"; /* File name too long */
	} else if (this->errno == 37) {
		errtext = "ENOLCK"; /* No record locks available */
	} else if (this->errno == 38) {
		errtext = "ENOSYS"; /* Function not implemented */
	} else if (this->errno == 39) {
		errtext = "ENOTEMPTY"; /* Directory not empty */
	} else if (this->errno == 40) {
		errtext = "ELOOP"; /* Too many symbolic links encountered */
	} else if (this->errno == 42) {
		errtext = "ENOMSG"; /* No message of desired type */
	} else if (this->errno == 43) {
		errtext = "EIDRM"; /* Identifier removed */
	} else if (this->errno == 44) {
		errtext = "ECHRNG"; /* Channel number out of range */
	} else if (this->errno == 45) {
		errtext = "EL2NSYNC"; /* Level 2 not synchronized */
	} else if (this->errno == 46) {
		errtext = "EL3HLT"; /* Level 3 halted */
	} else if (this->errno == 47) {
		errtext = "EL3RST"; /* Level 3 reset */
	} else if (this->errno == 48) {
		errtext = "ELNRNG"; /* Link number out of range */
	} else if (this->errno == 49) {
		errtext = "EUNATCH"; /* Protocol driver not attached */
	} else if (this->errno == 50) {
		errtext = "ENOCSI"; /* No CSI structure available */
	} else if (this->errno == 51) {
		errtext = "EL2HLT"; /* Level 2 halted */
	} else if (this->errno == 52) {
		errtext = "EBADE"; /* Invalid exchange */
	} else if (this->errno == 53) {
		errtext = "EBADR"; /* Invalid request descriptor */
	} else if (this->errno == 54) {
		errtext = "EXFULL"; /* Exchange full */
	} else if (this->errno == 55) {
		errtext = "ENOANO"; /* No anode */
	} else if (this->errno == 56) {
		errtext = "EBADRQC"; /* Invalid request code */
	} else if (this->errno == 57) {
		errtext = "EBADSLT"; /* Invalid slot */
	} else if (this->errno == 59) {
		errtext = "EBFONT"; /* Bad font file format */
	} else if (this->errno == 60) {
		errtext = "ENOSTR"; /* Device not a stream */
	} else if (this->errno == 61) {
		errtext = "ENODATA"; /* No data available */
	} else if (this->errno == 62) {
		errtext = "ETIME"; /* Timer expired */
	} else if (this->errno == 63) {
		errtext = "ENOSR"; /* Out of streams resources */
	} else if (this->errno == 64) {
		errtext = "ENONET"; /* Machine is not on the network */
	} else if (this->errno == 65) {
		errtext = "ENOPKG"; /* Package not installed */
	} else if (this->errno == 66) {
		errtext = "EREMOTE"; /* Object is remote */
	} else if (this->errno == 67) {
		errtext = "ENOLINK"; /* Link has been severed */
	} else if (this->errno == 68) {
		errtext = "EADV"; /* Advertise error */
	} else if (this->errno == 69) {
		errtext = "ESRMNT"; /* Srmount error */
	} else if (this->errno == 70) {
		errtext = "ECOMM"; /* Communication error on send */
	} else if (this->errno == 71) {
		errtext = "EPROTO"; /* Protocol error */
	} else if (this->errno == 72) {
		errtext = "EMULTIHOP"; /* Multihop attempted */
	} else if (this->errno == 73) {
		errtext = "EDOTDOT"; /* RFS specific error */
	} else if (this->errno == 74) {
		errtext = "EBADMSG"; /* Not a data message */
	} else if (this->errno == 75) {
		errtext = "EOVERFLOW"; /* Value too large for defined data type */
	} else if (this->errno == 76) {
		errtext = "ENOTUNIQ"; /* Name not unique on network */
	} else if (this->errno == 77) {
		errtext = "EBADFD"; /* File descriptor in bad state */
	} else if (this->errno == 78) {
		errtext = "EREMCHG"; /* Remote address changed */
	} else if (this->errno == 79) {
		errtext = "ELIBACC"; /* Can not access a needed shared library */
	} else if (this->errno == 80) {
		errtext = "ELIBBAD"; /* Accessing a corrupted shared library */
	} else if (this->errno == 81) {
		errtext = "ELIBSCN"; /* .lib section in a.out corrupted */
	} else if (this->errno == 82) {
		errtext = "ELIBMAX"; /* Attempting to link in too many shared libraries */
	} else if (this->errno == 83) {
		errtext = "ELIBEXEC"; /* Cannot exec a shared library directly */
	} else if (this->errno == 84) {
		errtext = "EILSEQ"; /* Illegal byte sequence */
	} else if (this->errno == 85) {
		errtext = "ERESTART"; /* Interrupted system call should be restarted */
	} else if (this->errno == 86) {
		errtext = "ESTRPIPE"; /* Streams pipe error */
	} else if (this->errno == 87) {
		errtext = "EUSERS"; /* Too many users */
	} else if (this->errno == 88) {
		errtext = "ENOTSOCK"; /* Socket operation on non-socket */
	} else if (this->errno == 89) {
		errtext = "EDESTADDRREQ"; /* Destination address required */
	} else if (this->errno == 90) {
		errtext = "EMSGSIZE"; /* Message too long */
	} else if (this->errno == 91) {
		errtext = "EPROTOTYPE"; /* Protocol wrong type for socket */
	} else if (this->errno == 92) {
		errtext = "ENOPROTOOPT"; /* Protocol not available */
	} else if (this->errno == 93) {
		errtext = "EPROTONOSUPPORT"; /* Protocol not supported */
	} else if (this->errno == 94) {
		errtext = "ESOCKTNOSUPPORT"; /* Socket type not supported */
	} else if (this->errno == 95) {
		errtext = "EOPNOTSUPP"; /* Operation not supported on transport endpoint */
	} else if (this->errno == 96) {
		errtext = "EPFNOSUPPORT"; /* Protocol family not supported */
	} else if (this->errno == 97) {
		errtext = "EAFNOSUPPORT"; /* Address family not supported by protocol */
	} else if (this->errno == 98) {
		errtext = "EADDRINUSE"; /* Address already in use */
	} else if (this->errno == 99) {
		errtext = "EADDRNOTAVAIL"; /* Cannot assign requested address */
	} else if (this->errno == 100) {
		errtext = "ENETDOWN"; /* Network is down */
	} else if (this->errno == 101) {
		errtext = "ENETUNREACH"; /* Network is unreachable */
	} else if (this->errno == 102) {
		errtext = "ENETRESET"; /* Network dropped connection because of reset */
	} else if (this->errno == 103) {
		errtext = "ECONNABORTED"; /* Software caused connection abort */
	} else if (this->errno == 104) {
		errtext = "ECONNRESET"; /* Connection reset by peer */
	} else if (this->errno == 105) {
		errtext = "ENOBUFS"; /* No buffer space available */
	} else if (this->errno == 106) {
		errtext = "EISCONN"; /* Transport endpoint is already connected */
	} else if (this->errno == 107) {
		errtext = "ENOTCONN"; /* Transport endpoint is not connected */
	} else if (this->errno == 108) {
		errtext = "ESHUTDOWN"; /* Cannot send after transport endpoint shutdown */
	} else if (this->errno == 109) {
		errtext = "ETOOMANYREFS"; /* Too many references: cannot splice */
	} else if (this->errno == 110) {
		errtext = "ETIMEDOUT"; /* Connection timed out */
	} else if (this->errno == 111) {
		errtext = "ECONNREFUSED"; /* Connection refused */
	} else if (this->errno == 112) {
		errtext = "EHOSTDOWN"; /* Host is down */
	} else if (this->errno == 113) {
		errtext = "EHOSTUNREACH"; /* No route to host */
	} else if (this->errno == 114) {
		errtext = "EALREADY"; /* Operation already in progress */
	} else if (this->errno == 115) {
		errtext = "EINPROGRESS"; /* Operation now in progress */
	} else if (this->errno == 116) {
		errtext = "ESTALE"; /* Stale NFS file handle */
	} else if (this->errno == 117) {
		errtext = "EUCLEAN"; /* Structure needs cleaning */
	} else if (this->errno == 118) {
		errtext = "ENOTNAM"; /* Not a XENIX named type file */
	} else if (this->errno == 119) {
		errtext = "ENAVAIL"; /* No XENIX semaphores available */
	} else if (this->errno == 120) {
		errtext = "EISNAM"; /* Is a named type file */
	} else if (this->errno == 121) {
		errtext = "EREMOTEIO"; /* Remote I/O error */
	} else if (this->errno == 122) {
		errtext = "EDQUOT"; /* Quota exceeded */
	} else if (this->errno == 123) {
		errtext = "ENOMEDIUM"; /* No medium found */
	} else if (this->errno == 124) {
		errtext = "EMEDIUMTYPE"; /* Wrong medium type */
	} else {
		errtext = "unbekannt";
	}

	char *buffer = new char[200];
	sprintf(buffer, "ExcSocketVerbindungVerloren; errno=%i, text=%s, methode=%s, laenge=%i\n", _errno,
			errtext.data(), _methode.data(), _laenge);
	Debug::schreibeLog("sd:/apps/WiiCraft/exception.log", buffer,
			Debug::DATEI_ERWEITERN);
	delete[] buffer;
#endif
}
