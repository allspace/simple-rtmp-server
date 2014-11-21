#ifndef SRS_WIN_PORTING_H
#define SRS_WIN_PORTING_H

#if !defined(_WIN32) || defined(__CYGWIN__) 		/*not on windows or it's cygwin. _WIN32 includes both 32-bit and 64-bit*/

#define SOCKET int
#define SOCKET_ERRNO()	errno
#define SOCKET_RESET(x) x=-1
#define SOCKET_CLOSE(x) if(x>=0){::close(x);x=-1}
#define SOCKET_CHECK(x) (x>=0)

#else /*on windows, but not on cygwin*/

#include <sys/stat.h>
#include <time.h>
#include <winsock2.h>
#include <stdint.h>

#define S_IRGRP 0
#define S_IWGRP 0
#define S_IXGRP 0
#define S_IRWXG 0
#define S_IROTH 0
#define S_IWOTH 0
#define S_IXOTH 0
#define S_IRWXO 0

#define PRId64 "lld"

#define ETIME			WSAETIMEDOUT
#define ECONNRESET      WSAECONNRESET
#define SOCKET_ERRNO()    WSAGetLastError()
#define SOCKET_RESET(x) x=INVALID_SOCKET
#define SOCKET_CLOSE(x) if(x!=INVALID_SOCKET){::closesocket(x);x=INVALID_SOCKET;}
#define SOCKET_CHECK(x) (x!=INVALID_SOCKET)
#define SOCKET_BUFF(x)  ((char*)x)

typedef uint32_t u_int32_t;
typedef uint8_t  u_int8_t;
typedef int socklen_t;
struct iovec {
   void* iov_base; /* Starting address */
   size_t iov_len; /* Length in bytes */
};

#define snprintf _snprintf
ssize_t writev(int fd, const struct iovec *iov, int iovcnt);
const char* inet_ntop(int af, const void *src, char *dst, size_t size);
int gettimeofday(struct timeval* tv, struct timezone* tz);
pid_t getpid(void);
//typedef int64_t useconds_t;
int usleep(useconds_t usec);

#endif

#endif //SRS_WIN_PORTING_H
