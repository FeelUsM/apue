/*
* Наш заголовочный файл, который подключается перед любыми
* стандартными системными заголовочными файлами
*/
#ifndef _LIMITS_H
#define _LIMITS_H

#define _POSIX_C_SOURCE 200809L
#if defined(SOLARIS) /* Solaris 10 */
	#define _XOPEN_SOURCE 600
#else
	#define _XOPEN_SOURCE 700
#endif

// compile gcc -fno-diagnostics-show-caret src.c
#include <unistd.h> /* для удобства */
#if !defined(_POSIX_VERSION) || _POSIX_VERSION!=200809L
	#error "_POSIX_VERSION"
#endif
#if !defined(_POSIX2_VERSION) || _POSIX2_VERSION!=200809L
	#error "_POSIX2_VERSION"
#endif
#if !defined(_POSIX_ASYNCHRONOUS_IO) || _POSIX_ASYNCHRONOUS_IO!=200809L
	#error "_POSIX_ASYNCHRONOUS_IO"
#endif
#if !defined(_POSIX_BARRIERS) || _POSIX_BARRIERS!=200809L
	#error "_POSIX_BARRIERS"
#endif
#if !defined(_POSIX_CLOCK_SELECTION) || _POSIX_CLOCK_SELECTION!=200809L
	#error "_POSIX_CLOCK_SELECTION"
#endif
#if !defined(_POSIX_MAPPED_FILES) || _POSIX_MAPPED_FILES!=200809L
	#error "_POSIX_MAPPED_FILES"
#endif
#if !defined(_POSIX_MEMORY_PROTECTION) || _POSIX_MEMORY_PROTECTION!=200809L
	#error "_POSIX_MEMORY_PROTECTION"
#endif
#if !defined(_POSIX_READER_WRITER_LOCKS) || _POSIX_READER_WRITER_LOCKS!=200809L
	#error "_POSIX_READER_WRITER_LOCKS"
#endif
#if !defined(_POSIX_REALTIME_SIGNALS) || _POSIX_REALTIME_SIGNALS!=200809L
	#error "_POSIX_REALTIME_SIGNALS"
#endif
#if !defined(_POSIX_SEMAPHORES) || _POSIX_SEMAPHORES!=200809L
	#error "_POSIX_SEMAPHORES"
#endif
#if !defined(_POSIX_SPIN_LOCKS) || _POSIX_SPIN_LOCKS!=200809L
	#error "_POSIX_SPIN_LOCKS"
#endif
#if !defined(_POSIX_THREAD_SAFE_FUNCTIONS) || _POSIX_THREAD_SAFE_FUNCTIONS!=200809L
	#error "_POSIX_THREAD_SAFE_FUNCTIONS"
#endif
#if !defined(_POSIX_THREADS) || _POSIX_THREADS!=200809L
	#error "_POSIX_THREADS"
#endif
#if !defined(_POSIX_TIMEOUTS) || _POSIX_TIMEOUTS!=200809L
	#error "_POSIX_TIMEOUTS"
#endif
#if !defined(_POSIX_TIMERS) || _POSIX_TIMERS!=200809L
	#error "_POSIX_TIMERS"
#endif
#if !defined(_POSIX2_C_BIND) || _POSIX2_C_BIND!=200809L
	#error "_POSIX2_C_BIND"
#endif

#if !defined(_POSIX_JOB_CONTROL) || _POSIX_JOB_CONTROL<=0
	#error "_POSIX_JOB_CONTROL"
#endif
#if !defined(_POSIX_REGEXP) || _POSIX_REGEXP<=0
	#error "_POSIX_REGEXP"
#endif
#if !defined(_POSIX_SAVED_IDS) || _POSIX_SAVED_IDS<=0
	#error "_POSIX_SAVED_IDS"
#endif
#if !defined(_POSIX_SHELL) || _POSIX_SHELL<=0
	#error "_POSIX_SHELL"
#endif

#if !defined(_POSIX_VDISABLE) || _POSIX_VDISABLE==-1
	#error "_POSIX_VDISABLE"
#endif


#define XSTR(x) STR(x)
#define STR(x) #x

#ifdef _POSIX_ADVISORY_INFO
	#pragma message "_POSIX_ADVISORY_INFO = " XSTR(_POSIX_ADVISORY_INFO) // 200809L
#endif
#ifdef _POSIX_CPUTIME
	#pragma message "_POSIX_CPUTIME = " XSTR(_POSIX_CPUTIME) // 0
#endif
#ifdef _POSIX_IPV6
	#pragma message "_POSIX_IPV6 = " XSTR(_POSIX_IPV6) // 200809L
#endif
#ifdef _POSIX_MEMLOCK
	#pragma message "_POSIX_MEMLOCK = " XSTR(_POSIX_MEMLOCK) // 200809L
#endif
#ifdef _POSIX_MEMLOCK_RANGE
	#pragma message "_POSIX_MEMLOCK_RANGE = " XSTR(_POSIX_MEMLOCK_RANGE) // 200809L
#endif
#ifdef _POSIX_MESSAGE_PASSING
	#pragma message "_POSIX_MESSAGE_PASSING = " XSTR(_POSIX_MESSAGE_PASSING) // 200809L
#endif
#ifdef _POSIX_MONOTONIC_CLOCK
	#pragma message "_POSIX_MONOTONIC_CLOCK = " XSTR(_POSIX_MONOTONIC_CLOCK) // 0
#endif
#ifdef _POSIX_PRIORITIZED_IO
	#pragma message "_POSIX_PRIORITIZED_IO = " XSTR(_POSIX_PRIORITIZED_IO) // 200809L
#endif
#ifdef _POSIX_PRIORITY_SCHEDULING
	#pragma message "_POSIX_PRIORITY_SCHEDULING = " XSTR(_POSIX_PRIORITY_SCHEDULING) // 200809L
#endif
#ifdef _POSIX_RAW_SOCKETS
	#pragma message "_POSIX_RAW_SOCKETS = " XSTR(_POSIX_RAW_SOCKETS) // 200809L
#endif
#ifdef _POSIX_SHARED_MEMORY_OBJECTS
	#pragma message "_POSIX_SHARED_MEMORY_OBJECTS = " XSTR(_POSIX_SHARED_MEMORY_OBJECTS) // 200809L
#endif
#ifdef _POSIX_SPAWN
	#pragma message "_POSIX_SPAWN = " XSTR(_POSIX_SPAWN) // 200809L
#endif
#ifdef _POSIX_SPORADIC_SERVER
	#pragma message "_POSIX_SPORADIC_SERVER = " XSTR(_POSIX_SPORADIC_SERVER) // -1
#endif
#ifdef _POSIX_SYNCHRONIZED_IO
	#pragma message "_POSIX_SYNCHRONIZED_IO = " XSTR(_POSIX_SYNCHRONIZED_IO) // 200809L
#endif
#ifdef _POSIX_THREAD_CPUTIME
	#pragma message "_POSIX_THREAD_CPUTIME = " XSTR(_POSIX_THREAD_CPUTIME) // 0
#endif
#ifdef _POSIX_THREAD_PRIO_INHERIT
	#pragma message "_POSIX_THREAD_PRIO_INHERIT = " XSTR(_POSIX_THREAD_PRIO_INHERIT) // 200809L
#endif
#ifdef _POSIX_THREAD_PRIO_PROTECT
	#pragma message "_POSIX_THREAD_PRIO_PROTECT = " XSTR(_POSIX_THREAD_PRIO_PROTECT) // 200809L
#endif
#ifdef _POSIX_THREAD_PRIORITY_SCHEDULING
	#pragma message "_POSIX_THREAD_PRIORITY_SCHEDULING = " XSTR(_POSIX_THREAD_PRIORITY_SCHEDULING) // 200809L
#endif
#ifdef _POSIX_THREAD_SPORADIC_SERVER
	#pragma message "_POSIX_THREAD_SPORADIC_SERVER = " XSTR(_POSIX_THREAD_SPORADIC_SERVER) // -1
#endif
#ifdef _POSIX_TRACE
	#pragma message "_POSIX_TRACE = " XSTR(_POSIX_TRACE) // -1
#endif
#ifdef _POSIX_TRACE_EVENT_FILTER
	#pragma message "_POSIX_TRACE_EVENT_FILTER = " XSTR(_POSIX_TRACE_EVENT_FILTER) // -1
#endif
#ifdef _POSIX_TRACE_INHERIT
	#pragma message "_POSIX_TRACE_INHERIT = " XSTR(_POSIX_TRACE_INHERIT) // -1
#endif
#ifdef _POSIX_TRACE_LOG
	#pragma message "_POSIX_TRACE_LOG = " XSTR(_POSIX_TRACE_LOG) // -1
#endif
#ifdef _POSIX_TYPED_MEMORY_OBJECTS
	#pragma message "_POSIX_TYPED_MEMORY_OBJECTS = " XSTR(_POSIX_TYPED_MEMORY_OBJECTS) // -1
#endif
#ifdef _XOPEN_CRYPT
	#pragma message "_XOPEN_CRYPT = " XSTR(_XOPEN_CRYPT)
#endif
#ifdef _XOPEN_REALTIME
	#pragma message "_XOPEN_REALTIME = " XSTR(_XOPEN_REALTIME) // 1
#endif
#ifdef _XOPEN_REALTIME_THREADS
	#pragma message "_XOPEN_REALTIME_THREADS = " XSTR(_XOPEN_REALTIME_THREADS) // 1
#endif
#ifdef _XOPEN_STREAMS
	#pragma message "_XOPEN_STREAMS = " XSTR(_XOPEN_STREAMS)
#endif

#ifdef _POSIX_FSYNC
	#pragma message "_POSIX_FSYNC = " XSTR(_POSIX_FSYNC) // 200809L
#endif
#ifdef _POSIX_THREAD_ATTR_STACKADDR
	#pragma message "_POSIX_THREAD_ATTR_STACKADDR = " XSTR(_POSIX_THREAD_ATTR_STACKADDR) // 200809L
#endif
#ifdef _POSIX_THREAD_ATTR_STACKSIZE
	#pragma message "_POSIX_THREAD_ATTR_STACKSIZE = " XSTR(_POSIX_THREAD_ATTR_STACKSIZE) // 200809L
#endif
#ifdef _POSIX_THREAD_PROCESS_SHARED
	#pragma message "_POSIX_THREAD_PROCESS_SHARED = " XSTR(_POSIX_THREAD_PROCESS_SHARED) // 200809L
#endif
#ifdef _XOPEN_UNIX 
	#pragma message "_XOPEN_UNIX = " XSTR(_XOPEN_UNIX) // 1
#endif
#ifdef _XOPEN_VERSION 
	#pragma message "_XOPEN_VERSION = " XSTR(_XOPEN_VERSION) // 700
#endif


#endif /* _LIMITS_H */

/*
Base Definitions
    Introduction
    Conformance
    Definitions
    General Concepts
    File Format Notation
    Character Set
    Locale
    Environment Variables
    Regular Expressions
    Directory Structure and Devices
    General Terminal Interface
    Utility Conventions
    Headers 
	    Format of Entries
	    <aio.h>
	    <arpa/inet.h>
	    <assert.h>
	    <complex.h>
	    <cpio.h>
	    <ctype.h>
	    <dirent.h>
	    <dlfcn.h>
	    <errno.h>
	    <fcntl.h>
	    <fenv.h>
	    <float.h>
	    <fmtmsg.h>
	    <fnmatch.h>
	    <ftw.h>
	    <glob.h>
	    <grp.h>
	    <iconv.h>
	    <inttypes.h>
	    <iso646.h>
	    <langinfo.h>
	    <libgen.h>
	    <limits.h>
	    <locale.h>
	    <math.h>
	    <monetary.h>
	    <mqueue.h>
	    <ndbm.h>
	    <net/if.h>
	    <netdb.h>
	    <netinet/in.h>
	    <netinet/tcp.h>
	    <nl_types.h>
	    <poll.h>
	    <pthread.h>
	    <pwd.h>
	    <regex.h>
	    <sched.h>
	    <search.h>
	    <semaphore.h>
	    <setjmp.h>
	    <signal.h>
	    <spawn.h>
	    <stdarg.h>
	    <stdbool.h>
	    <stddef.h>
	    <stdint.h>
	    <stdio.h>
	    <stdlib.h>
	    <string.h>
	    <strings.h>
	    <stropts.h>
	    <sys/ipc.h>
	    <sys/mman.h>
	    <sys/msg.h>
	    <sys/resource.h>
	    <sys/select.h>
	    <sys/sem.h>
	    <sys/shm.h>
	    <sys/socket.h>
	    <sys/stat.h>
	    <sys/statvfs.h>
	    <sys/time.h>
	    <sys/times.h>
	    <sys/types.h>
	    <sys/uio.h>
	    <sys/un.h>
	    <sys/utsname.h>
	    <sys/wait.h>
	    <syslog.h>
	    <tar.h>
	    <termios.h>
	    <tgmath.h>
	    <time.h>
	    <trace.h>
	    <ulimit.h>
	    <unistd.h>
	    <utime.h>
	    <utmpx.h>
	    <wchar.h>
	    <wctype.h>
	    <wordexp.h>
System Interfaces 
    Introduction
    General Information
	    Use and Implementation of Interfaces
	    The Compilation Environment
	    Error Numbers
	    Signal Concepts
	    Standard I/O Streams
	    STREAMS
	    XSI Interprocess Communication
	    Realtime
	    Threads
	    Sockets
	    Tracing
	    Data Types
	    Status Information
	    File Descriptor Allocation
    System Interfaces
	    FD_CLR()
	    FD_ISSET()
	    FD_SET()
	    FD_ZERO()
	    _Exit()
	    _exit()
	    _longjmp()
	    _setjmp()
	    _tolower()
	    _toupper()
	    a64l()
	    abort()
	    abs()
	    accept()
	    access()
	    acosf()
	    acoshf()
	    acosh()
	    acoshl()
	    acos()
	    acosl()
	    aio_cancel()
	    aio_error()
	    aio_fsync()
	    aio_read()
	    aio_return()
	    aio_suspend()
	    aio_write()
	    alarm()
	    alphasort()
	    asctime()
	    asctime_r()
	    asinf()
	    asinhf()
	    asinh()
	    asinhl()
	    asin()
	    asinl()
	    assert()
	    atan2f()
	    atan2()
	    atan2l()
	    atanf()
	    atanhf()
	    atanh()
	    atanhl()
	    atan()
	    atanl()
	    atexit()
	    atof()
	    atoi()
	    atol()
	    atoll()
	    basename()
	    bind()
	    bsearch()
	    btowc()
	    cabsf()
	    cabs()
	    cabsl()
	    cacosf()
	    cacoshf()
	    cacosh()
	    cacoshl()
	    cacos()
	    cacosl()
	    calloc()
	    cargf()
	    carg()
	    cargl()
	    casinf()
	    casinhf()
	    casinh()
	    casinhl()
	    casin()
	    casinl()
	    catanf()
	    catanhf()
	    catanh()
	    catanhl()
	    catan()
	    catanl()
	    catclose()
	    catgets()
	    catopen()
	    cbrtf()
	    cbrt()
	    cbrtl()
	    ccosf()
	    ccoshf()
	    ccosh()
	    ccoshl()
	    ccos()
	    ccosl()
	    ceilf()
	    ceil()
	    ceill()
	    cexpf()
	    cexp()
	    cexpl()
	    cfgetispeed()
	    cfgetospeed()
	    cfsetispeed()
	    cfsetospeed()
	    chdir()
	    chmod()
	    chown()
	    cimagf()
	    cimag()
	    cimagl()
	    clearerr()
	    clock_getcpuclockid()
	    clock_getres()
	    clock_gettime()
	    clock()
	    clock_nanosleep()
	    clock_settime()
	    clogf()
	    clog()
	    clogl()
	    closedir()
	    close()
	    closelog()
	    confstr()
	    conjf()
	    conj()
	    conjl()
	    connect()
	    copysignf()
	    copysign()
	    copysignl()
	    cosf()
	    coshf()
	    cosh()
	    coshl()
	    cos()
	    cosl()
	    cpowf()
	    cpow()
	    cpowl()
	    cprojf()
	    cproj()
	    cprojl()
	    crealf()
	    creal()
	    creall()
	    creat()
	    crypt()
	    csinf()
	    csinhf()
	    csinh()
	    csinhl()
	    csin()
	    csinl()
	    csqrtf()
	    csqrt()
	    csqrtl()
	    ctanf()
	    ctanhf()
	    ctanh()
	    ctanhl()
	    ctan()
	    ctanl()
	    ctermid()
	    ctime()
	    ctime_r()
	    daylight
	    dbm_clearerr()
	    dbm_close()
	    dbm_delete()
	    dbm_error()
	    dbm_fetch()
	    dbm_firstkey()
	    dbm_nextkey()
	    dbm_open()
	    dbm_store()
	    difftime()
	    dirfd()
	    dirname()
	    div()
	    dlclose()
	    dlerror()
	    dlopen()
	    dlsym()
	    dprintf()
	    drand48()
	    dup2()
	    dup()
	    duplocale()
	    encrypt()
	    endgrent()
	    endhostent()
	    endnetent()
	    endprotoent()
	    endpwent()
	    endservent()
	    endutxent()
	    environ
	    erand48()
	    erfcf()
	    erfc()
	    erfcl()
	    erff()
	    erf()
	    erfl()
	    errno
	    execle()
	    execl()
	    execlp()
	    execve()
	    execv()
	    execvp()
	    exit()
	    exp2f()
	    exp2()
	    exp2l()
	    expf()
	    exp()
	    expl()
	    expm1f()
	    expm1()
	    expm1l()
	    fabsf()
	    fabs()
	    fabsl()
	    faccessat()
	    fattach()
	    fchdir()
	    fchmodat()
	    fchmod()
	    fchownat()
	    fchown()
	    fclose()
	    fcntl()
	    fdatasync()
	    fdetach()
	    fdimf()
	    fdim()
	    fdiml()
	    fdopendir()
	    fdopen()
	    feclearexcept()
	    fegetenv()
	    fegetexceptflag()
	    fegetround()
	    feholdexcept()
	    feof()
	    feraiseexcept()
	    ferror()
	    fesetenv()
	    fesetexceptflag()
	    fesetround()
	    fetestexcept()
	    feupdateenv()
	    fexecve()
	    fflush()
	    ffs()
	    fgetc()
	    fgetpos()
	    fgets()
	    fgetwc()
	    fgetws()
	    fileno()
	    flockfile()
	    floorf()
	    floor()
	    floorl()
	    fmaf()
	    fma()
	    fmal()
	    fmaxf()
	    fmax()
	    fmaxl()
	    fmemopen()
	    fminf()
	    fmin()
	    fminl()
	    fmodf()
	    fmod()
	    fmodl()
	    fmtmsg()
	    fnmatch()
	    fopen()
	    fork()
	    fpathconf()
	    fpclassify()
	    fprintf()
	    fputc()
	    fputs()
	    fputwc()
	    fputws()
	    fread()
	    freeaddrinfo()
	    free()
	    freelocale()
	    freopen()
	    frexpf()
	    frexp()
	    frexpl()
	    fscanf()
	    fseek()
	    fseeko()
	    fsetpos()
	    fstatat()
	    fstat()
	    fstatvfs()
	    fsync()
	    ftell()
	    ftello()
	    ftok()
	    ftruncate()
	    ftrylockfile()
	    ftw()
	    funlockfile()
	    futimens()
	    fwide()
	    fwprintf()
	    fwrite()
	    fwscanf()
	    gai_strerror()
	    getaddrinfo()
	    getchar()
	    getchar_unlocked()
	    getc()
	    getc_unlocked()
	    getcwd()
	    getdate_err
	    getdate()
	    getdelim()
	    getegid()
	    getenv()
	    geteuid()
	    getgid()
	    getgrent()
	    getgrgid()
	    getgrgid_r()
	    getgrnam()
	    getgrnam_r()
	    getgroups()
	    gethostent()
	    gethostid()
	    gethostname()
	    getitimer()
	    getline()
	    getlogin()
	    getlogin_r()
	    getmsg()
	    getnameinfo()
	    getnetbyaddr()
	    getnetbyname()
	    getnetent()
	    getopt()
	    getpeername()
	    getpgid()
	    getpgrp()
	    getpid()
	    getpmsg()
	    getppid()
	    getpriority()
	    getprotobyname()
	    getprotobynumber()
	    getprotoent()
	    getpwent()
	    getpwnam()
	    getpwnam_r()
	    getpwuid()
	    getpwuid_r()
	    getrlimit()
	    getrusage()
	    getservbyname()
	    getservbyport()
	    getservent()
	    gets()
	    getsid()
	    getsockname()
	    getsockopt()
	    getsubopt()
	    gettimeofday()
	    getuid()
	    getutxent()
	    getutxid()
	    getutxline()
	    getwchar()
	    getwc()
	    globfree()
	    glob()
	    gmtime()
	    gmtime_r()
	    grantpt()
	    hcreate()
	    hdestroy()
	    hsearch()
	    htonl()
	    htons()
	    hypotf()
	    hypot()
	    hypotl()
	    iconv_close()
	    iconv()
	    iconv_open()
	    if_freenameindex()
	    if_indextoname()
	    if_nameindex()
	    if_nametoindex()
	    ilogbf()
	    ilogb()
	    ilogbl()
	    imaxabs()
	    imaxdiv()
	    inet_addr()
	    inet_ntoa()
	    inet_ntop()
	    inet_pton()
	    initstate()
	    insque()
	    ioctl()
	    isalnum()
	    isalnum_l()
	    isalpha()
	    isalpha_l()
	    isascii()
	    isastream()
	    isatty()
	    isblank()
	    isblank_l()
	    iscntrl()
	    iscntrl_l()
	    isdigit()
	    isdigit_l()
	    isfinite()
	    isgraph()
	    isgraph_l()
	    isgreaterequal()
	    isgreater()
	    isinf()
	    islessequal()
	    islessgreater()
	    isless()
	    islower()
	    islower_l()
	    isnan()
	    isnormal()
	    isprint()
	    isprint_l()
	    ispunct()
	    ispunct_l()
	    isspace()
	    isspace_l()
	    isunordered()
	    isupper()
	    isupper_l()
	    iswalnum()
	    iswalnum_l()
	    iswalpha()
	    iswalpha_l()
	    iswblank()
	    iswblank_l()
	    iswcntrl()
	    iswcntrl_l()
	    iswctype()
	    iswctype_l()
	    iswdigit()
	    iswdigit_l()
	    iswgraph()
	    iswgraph_l()
	    iswlower()
	    iswlower_l()
	    iswprint()
	    iswprint_l()
	    iswpunct()
	    iswpunct_l()
	    iswspace()
	    iswspace_l()
	    iswupper()
	    iswupper_l()
	    iswxdigit()
	    iswxdigit_l()
	    isxdigit()
	    isxdigit_l()
	    j0()
	    j1()
	    jn()
	    jrand48()
	    kill()
	    killpg()
	    l64a()
	    labs()
	    lchown()
	    lcong48()
	    ldexpf()
	    ldexp()
	    ldexpl()
	    ldiv()
	    lfind()
	    lgammaf()
	    lgamma()
	    lgammal()
	    linkat()
	    link()
	    lio_listio()
	    listen()
	    llabs()
	    lldiv()
	    llrintf()
	    llrint()
	    llrintl()
	    llroundf()
	    llround()
	    llroundl()
	    localeconv()
	    localtime()
	    localtime_r()
	    lockf()
	    log10f()
	    log10()
	    log10l()
	    log1pf()
	    log1p()
	    log1pl()
	    log2f()
	    log2()
	    log2l()
	    logbf()
	    logb()
	    logbl()
	    logf()
	    log()
	    logl()
	    longjmp()
	    lrand48()
	    lrintf()
	    lrint()
	    lrintl()
	    lroundf()
	    lround()
	    lroundl()
	    lsearch()
	    lseek()
	    lstat()
	    malloc()
	    mblen()
	    mbrlen()
	    mbrtowc()
	    mbsinit()
	    mbsnrtowcs()
	    mbsrtowcs()
	    mbstowcs()
	    mbtowc()
	    memccpy()
	    memchr()
	    memcmp()
	    memcpy()
	    memmove()
	    memset()
	    mkdirat()
	    mkdir()
	    mkdtemp()
	    mkfifoat()
	    mkfifo()
	    mknodat()
	    mknod()
	    mkstemp()
	    mktime()
	    mlockall()
	    mlock()
	    mmap()
	    modff()
	    modf()
	    modfl()
	    mprotect()
	    mq_close()
	    mq_getattr()
	    mq_notify()
	    mq_open()
	    mq_receive()
	    mq_send()
	    mq_setattr()
	    mq_timedreceive()
	    mq_timedsend()
	    mq_unlink()
	    mrand48()
	    msgctl()
	    msgget()
	    msgrcv()
	    msgsnd()
	    msync()
	    munlockall()
	    munlock()
	    munmap()
	    nanf()
	    nan()
	    nanl()
	    nanosleep()
	    nearbyintf()
	    nearbyint()
	    nearbyintl()
	    newlocale()
	    nextafterf()
	    nextafter()
	    nextafterl()
	    nexttowardf()
	    nexttoward()
	    nexttowardl()
	    nftw()
	    nice()
	    nl_langinfo()
	    nl_langinfo_l()
	    nrand48()
	    ntohl()
	    ntohs()
	    openat()
	    opendir()
	    open()
	    openlog()
	    open_memstream()
	    open_wmemstream()
	    optarg
	    opterr
	    optind
	    optopt
	    pathconf()
	    pause()
	    pclose()
	    perror()
	    pipe()
	    poll()
	    popen()
	    posix_fadvise()
	    posix_fallocate()
	    posix_madvise()
	    posix_memalign()
	    posix_mem_offset()
	    posix_openpt()
	    posix_spawnattr_destroy()
	    posix_spawnattr_getflags()
	    posix_spawnattr_getpgroup()
	    posix_spawnattr_getschedparam()
	    posix_spawnattr_getschedpolicy()
	    posix_spawnattr_getsigdefault()
	    posix_spawnattr_getsigmask()
	    posix_spawnattr_init()
	    posix_spawnattr_setflags()
	    posix_spawnattr_setpgroup()
	    posix_spawnattr_setschedparam()
	    posix_spawnattr_setschedpolicy()
	    posix_spawnattr_setsigdefault()
	    posix_spawnattr_setsigmask()
	    posix_spawn_file_actions_addclose()
	    posix_spawn_file_actions_adddup2()
	    posix_spawn_file_actions_addopen()
	    posix_spawn_file_actions_destroy()
	    posix_spawn_file_actions_init()
	    posix_spawn()
	    posix_spawnp()
	    posix_trace_attr_destroy()
	    posix_trace_attr_getclockres()
	    posix_trace_attr_getcreatetime()
	    posix_trace_attr_getgenversion()
	    posix_trace_attr_getinherited()
	    posix_trace_attr_getlogfullpolicy()
	    posix_trace_attr_getlogsize()
	    posix_trace_attr_getmaxdatasize()
	    posix_trace_attr_getmaxsystemeventsize()
	    posix_trace_attr_getmaxusereventsize()
	    posix_trace_attr_getname()
	    posix_trace_attr_getstreamfullpolicy()
	    posix_trace_attr_getstreamsize()
	    posix_trace_attr_init()
	    posix_trace_attr_setinherited()
	    posix_trace_attr_setlogfullpolicy()
	    posix_trace_attr_setlogsize()
	    posix_trace_attr_setmaxdatasize()
	    posix_trace_attr_setname()
	    posix_trace_attr_setstreamfullpolicy()
	    posix_trace_attr_setstreamsize()
	    posix_trace_clear()
	    posix_trace_close()
	    posix_trace_create()
	    posix_trace_create_withlog()
	    posix_trace_event()
	    posix_trace_eventid_equal()
	    posix_trace_eventid_get_name()
	    posix_trace_eventid_open()
	    posix_trace_eventset_add()
	    posix_trace_eventset_del()
	    posix_trace_eventset_empty()
	    posix_trace_eventset_fill()
	    posix_trace_eventset_ismember()
	    posix_trace_eventtypelist_getnext_id()
	    posix_trace_eventtypelist_rewind()
	    posix_trace_flush()
	    posix_trace_get_attr()
	    posix_trace_get_filter()
	    posix_trace_getnext_event()
	    posix_trace_get_status()
	    posix_trace_open()
	    posix_trace_rewind()
	    posix_trace_set_filter()
	    posix_trace_shutdown()
	    posix_trace_start()
	    posix_trace_stop()
	    posix_trace_timedgetnext_event()
	    posix_trace_trid_eventid_open()
	    posix_trace_trygetnext_event()
	    posix_typed_mem_get_info()
	    posix_typed_mem_open()
	    powf()
	    pow()
	    powl()
	    pread()
	    printf()
	    pselect()
	    psiginfo()
	    psignal()
	    pthread_atfork()
	    pthread_attr_destroy()
	    pthread_attr_getdetachstate()
	    pthread_attr_getguardsize()
	    pthread_attr_getinheritsched()
	    pthread_attr_getschedparam()
	    pthread_attr_getschedpolicy()
	    pthread_attr_getscope()
	    pthread_attr_getstack()
	    pthread_attr_getstacksize()
	    pthread_attr_init()
	    pthread_attr_setdetachstate()
	    pthread_attr_setguardsize()
	    pthread_attr_setinheritsched()
	    pthread_attr_setschedparam()
	    pthread_attr_setschedpolicy()
	    pthread_attr_setscope()
	    pthread_attr_setstack()
	    pthread_attr_setstacksize()
	    pthread_barrierattr_destroy()
	    pthread_barrierattr_getpshared()
	    pthread_barrierattr_init()
	    pthread_barrierattr_setpshared()
	    pthread_barrier_destroy()
	    pthread_barrier_init()
	    pthread_barrier_wait()
	    pthread_cancel()
	    pthread_cleanup_pop()
	    pthread_cleanup_push()
	    pthread_condattr_destroy()
	    pthread_condattr_getclock()
	    pthread_condattr_getpshared()
	    pthread_condattr_init()
	    pthread_condattr_setclock()
	    pthread_condattr_setpshared()
	    pthread_cond_broadcast()
	    pthread_cond_destroy()
	    pthread_cond_init()
	    pthread_cond_signal()
	    pthread_cond_timedwait()
	    pthread_cond_wait()
	    pthread_create()
	    pthread_detach()
	    pthread_equal()
	    pthread_exit()
	    pthread_getconcurrency()
	    pthread_getcpuclockid()
	    pthread_getschedparam()
	    pthread_getspecific()
	    pthread_join()
	    pthread_key_create()
	    pthread_key_delete()
	    pthread_kill()
	    pthread_mutexattr_destroy()
	    pthread_mutexattr_getprioceiling()
	    pthread_mutexattr_getprotocol()
	    pthread_mutexattr_getpshared()
	    pthread_mutexattr_getrobust()
	    pthread_mutexattr_gettype()
	    pthread_mutexattr_init()
	    pthread_mutexattr_setprioceiling()
	    pthread_mutexattr_setprotocol()
	    pthread_mutexattr_setpshared()
	    pthread_mutexattr_setrobust()
	    pthread_mutexattr_settype()
	    pthread_mutex_consistent()
	    pthread_mutex_destroy()
	    pthread_mutex_getprioceiling()
	    pthread_mutex_init()
	    pthread_mutex_lock()
	    pthread_mutex_setprioceiling()
	    pthread_mutex_timedlock()
	    pthread_mutex_trylock()
	    pthread_mutex_unlock()
	    pthread_once()
	    pthread_rwlockattr_destroy()
	    pthread_rwlockattr_getpshared()
	    pthread_rwlockattr_init()
	    pthread_rwlockattr_setpshared()
	    pthread_rwlock_destroy()
	    pthread_rwlock_init()
	    pthread_rwlock_rdlock()
	    pthread_rwlock_timedrdlock()
	    pthread_rwlock_timedwrlock()
	    pthread_rwlock_tryrdlock()
	    pthread_rwlock_trywrlock()
	    pthread_rwlock_unlock()
	    pthread_rwlock_wrlock()
	    pthread_self()
	    pthread_setcancelstate()
	    pthread_setcanceltype()
	    pthread_setconcurrency()
	    pthread_setschedparam()
	    pthread_setschedprio()
	    pthread_setspecific()
	    pthread_sigmask()
	    pthread_spin_destroy()
	    pthread_spin_init()
	    pthread_spin_lock()
	    pthread_spin_trylock()
	    pthread_spin_unlock()
	    pthread_testcancel()
	    ptsname()
	    putchar()
	    putchar_unlocked()
	    putc()
	    putc_unlocked()
	    putenv()
	    putmsg()
	    putpmsg()
	    puts()
	    pututxline()
	    putwchar()
	    putwc()
	    pwrite()
	    qsort()
	    raise()
	    rand()
	    random()
	    rand_r()
	    readdir()
	    readdir_r()
	    read()
	    readlinkat()
	    readlink()
	    readv()
	    realloc()
	    realpath()
	    recvfrom()
	    recv()
	    recvmsg()
	    regcomp()
	    regerror()
	    regexec()
	    regfree()
	    remainderf()
	    remainder()
	    remainderl()
	    remove()
	    remque()
	    remquof()
	    remquo()
	    remquol()
	    renameat()
	    rename()
	    rewinddir()
	    rewind()
	    rintf()
	    rint()
	    rintl()
	    rmdir()
	    roundf()
	    round()
	    roundl()
	    scalblnf()
	    scalbln()
	    scalblnl()
	    scalbnf()
	    scalbn()
	    scalbnl()
	    scandir()
	    scanf()
	    sched_getparam()
	    sched_get_priority_max()
	    sched_get_priority_min()
	    sched_getscheduler()
	    sched_rr_get_interval()
	    sched_setparam()
	    sched_setscheduler()
	    sched_yield()
	    seed48()
	    seekdir()
	    select()
	    sem_close()
	    semctl()
	    sem_destroy()
	    semget()
	    sem_getvalue()
	    sem_init()
	    sem_open()
	    semop()
	    sem_post()
	    sem_timedwait()
	    sem_trywait()
	    sem_unlink()
	    sem_wait()
	    send()
	    sendmsg()
	    sendto()
	    setbuf()
	    setegid()
	    setenv()
	    seteuid()
	    setgid()
	    setgrent()
	    sethostent()
	    setitimer()
	    setjmp()
	    setkey()
	    setlocale()
	    setlogmask()
	    setnetent()
	    setpgid()
	    setpgrp()
	    setpriority()
	    setprotoent()
	    setpwent()
	    setregid()
	    setreuid()
	    setrlimit()
	    setservent()
	    setsid()
	    setsockopt()
	    setstate()
	    setuid()
	    setutxent()
	    setvbuf()
	    shmat()
	    shmctl()
	    shmdt()
	    shmget()
	    shm_open()
	    shm_unlink()
	    shutdown()
	    sigaction()
	    sigaddset()
	    sigaltstack()
	    sigdelset()
	    sigemptyset()
	    sigfillset()
	    sighold()
	    sigignore()
	    siginterrupt()
	    sigismember()
	    siglongjmp()
	    signal()
	    signbit()
	    signgam
	    sigpause()
	    sigpending()
	    sigprocmask()
	    sigqueue()
	    sigrelse()
	    sigset()
	    sigsetjmp()
	    sigsuspend()
	    sigtimedwait()
	    sigwait()
	    sigwaitinfo()
	    sinf()
	    sinhf()
	    sinh()
	    sinhl()
	    sin()
	    sinl()
	    sleep()
	    snprintf()
	    sockatmark()
	    socket()
	    socketpair()
	    sprintf()
	    sqrtf()
	    sqrt()
	    sqrtl()
	    srand48()
	    srand()
	    srandom()
	    sscanf()
	    stat()
	    statvfs()
	    stderr
	    stdin
	    stdout
	    stpcpy()
	    stpncpy()
	    strcasecmp()
	    strcasecmp_l()
	    strcat()
	    strchr()
	    strcmp()
	    strcoll()
	    strcoll_l()
	    strcpy()
	    strcspn()
	    strdup()
	    strerror()
	    strerror_l()
	    strerror_r()
	    strfmon()
	    strfmon_l()
	    strftime()
	    strftime_l()
	    strlen()
	    strncasecmp()
	    strncasecmp_l()
	    strncat()
	    strncmp()
	    strncpy()
	    strndup()
	    strnlen()
	    strpbrk()
	    strptime()
	    strrchr()
	    strsignal()
	    strspn()
	    strstr()
	    strtod()
	    strtof()
	    strtoimax()
	    strtok()
	    strtok_r()
	    strtold()
	    strtol()
	    strtoll()
	    strtoul()
	    strtoull()
	    strtoumax()
	    strxfrm()
	    strxfrm_l()
	    swab()
	    swprintf()
	    swscanf()
	    symlinkat()
	    symlink()
	    sync()
	    sysconf()
	    syslog()
	    system()
	    tanf()
	    tanhf()
	    tanh()
	    tanhl()
	    tan()
	    tanl()
	    tcdrain()
	    tcflow()
	    tcflush()
	    tcgetattr()
	    tcgetpgrp()
	    tcgetsid()
	    tcsendbreak()
	    tcsetattr()
	    tcsetpgrp()
	    tdelete()
	    telldir()
	    tempnam()
	    tfind()
	    tgammaf()
	    tgamma()
	    tgammal()
	    time()
	    timer_create()
	    timer_delete()
	    timer_getoverrun()
	    timer_gettime()
	    timer_settime()
	    times()
	    timezone
	    tmpfile()
	    tmpnam()
	    toascii()
	    tolower()
	    tolower_l()
	    toupper()
	    toupper_l()
	    towctrans()
	    towctrans_l()
	    towlower()
	    towlower_l()
	    towupper()
	    towupper_l()
	    truncate()
	    truncf()
	    trunc()
	    truncl()
	    tsearch()
	    ttyname()
	    ttyname_r()
	    twalk()
	    tzname
	    tzset()
	    ulimit()
	    umask()
	    uname()
	    ungetc()
	    ungetwc()
	    unlinkat()
	    unlink()
	    unlockpt()
	    unsetenv()
	    uselocale()
	    utime()
	    utimensat()
	    utimes()
	    va_arg()
	    va_copy()
	    va_end()
	    va_start()
	    vdprintf()
	    vfprintf()
	    vfscanf()
	    vfwprintf()
	    vfwscanf()
	    vprintf()
	    vscanf()
	    vsnprintf()
	    vsprintf()
	    vsscanf()
	    vswprintf()
	    vswscanf()
	    vwprintf()
	    vwscanf()
	    wait()
	    waitid()
	    waitpid()
	    wcpcpy()
	    wcpncpy()
	    wcrtomb()
	    wcscasecmp()
	    wcscasecmp_l()
	    wcscat()
	    wcschr()
	    wcscmp()
	    wcscoll()
	    wcscoll_l()
	    wcscpy()
	    wcscspn()
	    wcsdup()
	    wcsftime()
	    wcslen()
	    wcsncasecmp()
	    wcsncasecmp_l()
	    wcsncat()
	    wcsncmp()
	    wcsncpy()
	    wcsnlen()
	    wcsnrtombs()
	    wcspbrk()
	    wcsrchr()
	    wcsrtombs()
	    wcsspn()
	    wcsstr()
	    wcstod()
	    wcstof()
	    wcstoimax()
	    wcstok()
	    wcstold()
	    wcstol()
	    wcstoll()
	    wcstombs()
	    wcstoul()
	    wcstoull()
	    wcstoumax()
	    wcswidth()
	    wcsxfrm()
	    wcsxfrm_l()
	    wctob()
	    wctomb()
	    wctrans()
	    wctrans_l()
	    wctype()
	    wctype_l()
	    wcwidth()
	    wmemchr()
	    wmemcmp()
	    wmemcpy()
	    wmemmove()
	    wmemset()
	    wordexp()
	    wordfree()
	    wprintf()
	    write()
	    writev()
	    wscanf()
	    y0()
	    y1()
	    yn()
Shell & Utilities
    Introduction
    Shell Command Language
	    Shell Introduction
	    Quoting
	        Escape Character (Backslash)
	        Single-Quotes
	        Double-Quotes
	    Token Recognition
	        Alias Substitution
	    Reserved Words
	    Parameters and Variables
	        Positional Parameters
	        Special Parameters
	        Shell Variables
	    Word Expansions
	        Tilde Expansion
	        Parameter Expansion
	        Command Substitution
	        Arithmetic Expansion
	        Field Splitting
	        Pathname Expansion
	        Quote Removal
	    Redirection
	        Redirecting Input
	        Redirecting Output
	        Appending Redirected Output
	        Here-Document
	        Duplicating an Input File Descriptor
	        Duplicating an Output File Descriptor
	        Open File Descriptors for Reading and Writing
	    Exit Status and Errors
	        Consequences of Shell Errors
	        Exit Status for Commands
	    Shell Commands
	        Simple Commands
	        Pipelines
	        Lists
	        Compound Commands
	        Function Definition Command
	    Shell Grammar
	        Shell Grammar Lexical Conventions
	        Shell Grammar Rules
	    Signals and Error Handling
	    Shell Execution Environment
	    Pattern Matching Notation
	        Patterns Matching a Single Character
	        Patterns Matching Multiple Characters
	        Patterns Used for Filename Expansion
	    Special Built-In Utilities
	        break
	        colon
	        continue
	        dot
	        eval
	        exec
	        exit
	        export
	        readonly
	        return
	        set
	        shift
	        times
	        trap
	        unset
    Batch Environment Services
    Utilities 
	    admin
	    alias
	    ar
	    asa
	    at
	    awk
	    basename
	    batch
	    bc
	    bg
	    c99
	    cal
	    cat
	    cd
	    cflow
	    chgrp
	    chmod
	    chown
	    cksum
	    cmp
	    comm
	    command
	    compress
	    cp
	    crontab
	    csplit
	    ctags
	    cut
	    cxref
	    date
	    dd
	    delta
	    df
	    diff
	    dirname
	    du
	    echo
	    ed
	    env
	    ex
	    expand
	    expr
	    false
	    fc
	    fg
	    file
	    find
	    fold
	    fort77
	    fuser
	    gencat
	    get
	    getconf
	    getopts
	    grep
	    hash
	    head
	    iconv
	    id
	    ipcrm
	    ipcs
	    jobs
	    join
	    kill
	    lex
	    link
	    ln
	    locale
	    localedef
	    logger
	    logname
	    lp
	    ls
	    m4
	    mailx
	    make
	    man
	    mesg
	    mkdir
	    mkfifo
	    more
	    mv
	    newgrp
	    nice
	    nl
	    nm
	    nohup
	    od
	    paste
	    patch
	    pathchk
	    pax
	    pr
	    printf
	    prs
	    ps
	    pwd
	    qalter
	    qdel
	    qhold
	    qmove
	    qmsg
	    qrerun
	    qrls
	    qselect
	    qsig
	    qstat
	    qsub
	    read
	    renice
	    rm
	    rmdel
	    rmdir
	    sact
	    sccs
	    sed
	    sh
	    sleep
	    sort
	    split
	    strings
	    strip
	    stty
	    tabs
	    tail
	    talk
	    tee
	    test
	    time
	    touch
	    tput
	    tr
	    true
	    tsort
	    tty
	    type
	    ulimit
	    umask
	    unalias
	    uname
	    uncompress
	    unexpand
	    unget
	    uniq
	    unlink
	    uucp
	    uudecode
	    uuencode
	    uustat
	    uux
	    val
	    vi
	    wait
	    wc
	    what
	    who
	    write
	    xargs
	    yacc
	    zcat
Rationale
    Rationale for Base Definitions
	    Introduction
	    Conformance
	    Definitions
	    General Concepts
	    File Format Notation
	    Character Set
	    Locale
	    Environment Variables
	    Regular Expressions
	    Directory Structure and Devices
	    General Terminal Interface
	    Utility Conventions
	    Headers
    Rationale for System Interfaces
	    Introduction
	    General Information
		    Use and Implementation of Interfaces
		    The Compilation Environment
		    Error Numbers
		    Signal Concepts
		    Standard I/O Streams
		    STREAMS
		    XSI Interprocess Communication
		    Realtime
		    Threads
		    Sockets
		    Tracing
		    Data Types
		    Status Information
		    File Descriptor Allocation
	    System Interfaces
    Rationale for Shell & Utilities
    Portability Considerations (Informative)
    Subprofiling Considerations (Informative)

*/