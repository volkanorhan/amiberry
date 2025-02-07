#ifndef __COMMON_H__
#define __COMMON_H__

#define CONFIG_QEMU

//#define DEBUG 1

#ifndef CONFIG_QEMU
#include "version.h"
#endif
#include "sysconfig.h"
#include "slirp_config.h"

#define SLIRP_ICMP 0

#ifdef _WIN32
#include <stdint.h>

typedef uint8_t u_int8_t;
typedef uint16_t u_int16_t;
typedef uint32_t u_int32_t;
typedef uint64_t u_int64_t;

typedef u_int8_t uint8;
typedef u_int16_t uint16;
typedef u_int32_t uint32;

typedef char *caddr_t;
typedef int socklen_t;
typedef unsigned long ioctlsockopt_t;

/* Should be UINT_PTR but SLIRP code has <= 0 tests */
#define SLIRP_SOCKET INT_PTR

#ifdef _MSC_VER
#define container_of(address, type, field) ((type *)( \
        (PCHAR)(address) - \
        (ULONG_PTR)(&((type *)0)->field)))
#endif

#include <winsock2.h>
#include <Ws2tcpip.h>
#include <sys/timeb.h>
#include <iphlpapi.h>

# define USE_FIONBIO 1

/* Basilisk II Router defines those */
# define udp_read_completion slirp_udp_read_completion
# define write_udp slirp_write_udp
# define init_udp slirp_init_udp
# define final_udp slirp_final_udp
#else //!_WIN32
typedef int ioctlsockopt_t;

#define container_of(address, type, field) ((type *)( \
        (char*)(address) - \
        (unsigned long)(&((type *)0)->field)))

# define WSAGetLastError() (int)(errno)
# define WSASetLastError(e) (void)(errno = (e))
# define WSAEWOULDBLOCK EWOULDBLOCK
# define WSAEINPROGRESS EINPROGRESS
# define WSAENOTCONN ENOTCONN
# define WSAEHOSTUNREACH EHOSTUNREACH
# define WSAENETUNREACH ENETUNREACH
# define WSAECONNREFUSED ECONNREFUSED

# define SLIRP_SOCKET int

# define ioctlsocket ioctl
# define closesocket(s) close(s)
# define O_BINARY 0

#include <sys/time.h>
#endif

#include "sysdeps.h"

#include <sys/types.h>
#ifdef HAVE_SYS_BITYPES_H
# include <sys/bitypes.h>
#endif
#ifdef HAVE_STDINT_H
# include <stdint.h>
#endif

#ifdef NEED_TYPEDEFS
typedef char int8_t;
typedef unsigned char u_int8_t;

# if SIZEOF_SHORT == 2
    typedef short int16_t;
    typedef unsigned short u_int16_t;
# else
#  if SIZEOF_INT == 2
    typedef int int16_t;
    typedef unsigned int u_int16_t;
#  else
    #error Cannot find a type with sizeof() == 2
#  endif
# endif

# if SIZEOF_SHORT == 4
   typedef short int32_t;
   typedef unsigned short u_int32_t;
# else
#  if SIZEOF_INT == 4
    typedef int int32_t;
    typedef unsigned int u_int32_t;
#  else
    #error Cannot find a type with sizeof() == 4
#  endif
# endif
#endif /* NEED_TYPEDEFS */

/* Basilisk II types glue */
typedef u_int8_t uint8;
typedef u_int16_t uint16;
typedef u_int32_t uint32;

#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif

#ifdef HAVE_STDLIB_H
# include <stdlib.h>
#endif

#include <stdio.h>
#include <errno.h>

#ifndef HAVE_MEMMOVE
#define memmove(x, y, z) bcopy(y, x, z)
#endif

#if TIME_WITH_SYS_TIME
# include <sys/time.h>
# include <time.h>
#else
# if HAVE_SYS_TIME_H
#  include <sys/time.h>
# else
#  include <time.h>
# endif
#endif

#ifdef HAVE_STRING_H
# include <string.h>
#else
# include <strings.h>
#endif

#ifndef _WIN32
#include <sys/uio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#ifdef GETTIMEOFDAY_ONE_ARG
#define gettimeofday(x, y) gettimeofday(x)
#endif

/* Systems lacking strdup() definition in <string.h>. */
#if defined(ultrix)
char *strdup(const char *);
#endif

/* Systems lacking malloc() definition in <stdlib.h>. */
#if defined(ultrix) || defined(hcx)
void *malloc(size_t arg);
void free(void *ptr);
#endif

#ifndef HAVE_INET_ATON
int inet_aton(const char *cp, struct in_addr *ia);
#endif

#include <fcntl.h>
#ifndef NO_UNIX_SOCKETS
#include <sys/un.h>
#endif
#include <signal.h>
#ifdef HAVE_SYS_SIGNAL_H
# include <sys/signal.h>
#endif
#ifndef _WIN32
#include <sys/socket.h>
#endif

#if defined(HAVE_SYS_IOCTL_H)
# include <sys/ioctl.h>
#endif

#ifdef HAVE_SYS_SELECT_H
# include <sys/select.h>
#endif

#ifdef HAVE_SYS_WAIT_H
# include <sys/wait.h>
#endif

#ifdef HAVE_SYS_FILIO_H
# include <sys/filio.h>
#endif

#ifdef USE_PPP
#include <ppp/slirppp.h>
#endif

#ifdef __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

#include <sys/stat.h>

/* Avoid conflicting with the libc insque() and remque(), which
   have different prototypes. */
#define insque slirp_insque
#define remque slirp_remque

#ifdef HAVE_SYS_STROPTS_H
#include <sys/stropts.h>
#endif

#include "debug.h"

#if defined __GNUC__
#define PACKED__ __attribute__ ((packed))
#elif defined __sgi
#define PRAGMA_PACK_SUPPORTED 1
#define PACKED__
#elif _MSC_VER
#define PRAGMA_PACK_SUPPORTED 1
#define PACKED__
#else
#error "Packed attribute or pragma shall be supported"
#endif

#include "ip.h"
#include "tcp.h"
#include "tcp_timer.h"
#include "tcp_var.h"
#include "tcpip.h"
#include "udp.h"
#include "ip_icmp.h"
#include "icmp_var.h"
#include "mbuf.h"
#include "sbuf.h"
#include "socket.h"
#include "if.h"
#include "main.h"
#include "misc.h"
#include "ctl.h"
#ifdef USE_PPP
#include "ppp/pppd.h"
#include "ppp/ppp.h"
#endif

#include "bootp.h"
#include "tftp.h"
#include "libslirp.h"

extern struct ttys *ttys_unit[MAX_INTERFACES];

#ifndef NULL
#define NULL (void *)0
#endif

#ifndef FULL_BOLT
void if_start(void);
#else
void if_start(struct ttys *);
#endif

#ifdef BAD_SPRINTF
# define vsprintf vsprintf_len
# define sprintf sprintf_len
 extern int vsprintf_len(char *, const char *, va_list);
 extern int sprintf_len(char *, const char *, ...);
#endif

#ifdef DECLARE_SPRINTF
# ifndef BAD_SPRINTF
 extern int vsprintf(char *, const char *, va_list);
# endif
 extern int vfprintf(FILE *, const char *, va_list);
#endif

#ifndef HAVE_STRERROR
 extern char *strerror(int error);
#endif

//#ifndef HAVE_INDEX
// char *index(const char *, int);
//#endif

#ifndef HAVE_GETHOSTID
 long gethostid(void);
#endif

void lprint(const char *, ...);

#ifndef _WIN32
#include <netdb.h>
#endif

#define DEFAULT_BAUD 115200

/* cksum.c */
u_short cksum(struct mbuf *m, int len);

/* if.c */
void if_init(void);
void if_output(struct socket *, struct mbuf *);

/* ip_input.c */
void ip_init(void);
void ip_cleanup(void);
void ip_input(struct mbuf *);
struct ip * ip_reass(struct ip *, struct ipq *);
void ip_freef(struct ipq *);
void ip_enq(struct ipasfrag *, struct ipasfrag *);
void ip_deq(struct ipasfrag *);
void ip_slowtimo(void);
void ip_stripoptions(struct mbuf *, struct mbuf *);

/* ip_output.c */
int ip_output(struct socket *, struct mbuf *);

/* tcp_input.c */
int tcp_reass(struct tcpcb *, struct tcpiphdr *, struct mbuf *);
void tcp_input(struct mbuf *, int, struct socket *);
void tcp_dooptions(struct tcpcb *, u_char *, int, struct tcpiphdr *);
void tcp_xmit_timer(struct tcpcb *, int);
u_int tcp_mss(struct tcpcb *, u_int);

/* tcp_output.c */
int tcp_output(struct tcpcb *);
void tcp_setpersist(struct tcpcb *);

/* tcp_subr.c */
void tcp_init(void);
void tcp_cleanup(void);
void tcp_template(struct tcpcb *);
void tcp_respond(struct tcpcb *, struct tcpiphdr *, struct mbuf *, tcp_seq, tcp_seq, int);
struct tcpcb * tcp_newtcpcb(struct socket *);
struct tcpcb * tcp_close(struct tcpcb *);
void tcp_drain(void);
void tcp_sockclosed(struct tcpcb *);
int tcp_fconnect(struct socket *);
void tcp_connect(struct socket *);
int tcp_attach(struct socket *);
u_int8_t tcp_tos(struct socket *);
int tcp_emu(struct socket *, struct mbuf *);
int tcp_ctl(struct socket *);
struct tcpcb *tcp_drop(struct tcpcb *tp, int err);

#ifdef USE_PPP
#define MIN_MRU MINMRU
#define MAX_MRU MAXMRU
#else
#define MIN_MRU 128
#define MAX_MRU 16384
#endif

#ifndef _MSC_VER
#define min(x,y) ((x) < (y) ? (x) : (y))
#define max(x,y) ((x) > (y) ? (x) : (y))
#endif

#endif
