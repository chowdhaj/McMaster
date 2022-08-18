#ifndef _log_h
#define _log_h

/* **************************************************************************
   **************************************************************************
All functions in this file comply with the same syntax and 
semantics for arguments as printf() function (i.e. variable 
number of standard arguments). The functions whose name start 
with a lower case (sys_exit(), sys__exit(), msg(), sys(), 
msg_exit(), msg__exit(), msg()) write their messages to stdout 
(i.e. under normal circumstances to the screen of the terminal), 
while the functions whose name start with an upper case 
(Sys_exit(), Sys__exit(), Sys(), Msg_exit(), Msg__exit(), Msg()) 
write into a log file.

The functions sys(), msg(), Sys(), and Msg() on entry save the 
current signal mask, block all signals, and than they write the
message. On return they re-instate the signal mask as it was on
entry. Thus the messages cannot be interrupted by signals.

The functions sys_exit(), sys__exit(), msg_exit(), msg__exit(),
Sys_exit(), Sys__exit(), Msg_exit(), Msg__exit() on entry block
all signals. They do not save the original signal mask, for these
functions do not return, they exit using the system call exit(1) 
or _exit(1). Functions sys_exit(), msg_exit(), Sys_exit(), and
Msg_exit() exit using exit(1) system call, while sys__exit(), 
msg_exit(), Sys__exit(), and Msg__exit() using _exit(1) system
call. 

The functions msg_exit(), msg__exit(), msg(), Msg_exit(), 
Msg__exit(), and Msg() just write the requested message and either
return (msg(), Msg()) or exit() (msg_exit(), Msg_exit()), or 
_exit() (msg__exit(), Msg__exit()).

The functions sys_exit(), sys__exit(), sys(), Sys_exit(),
Sys__exit(), and Sys() write a more elaborate system error 
message (together with the requested message) describing the error 
that happened using errno. Thus they should be used only after a 
system call failed. These functions either return (sys(), Sys()) 
or exit() (sys_exit(), Sys_exit()) or _exit() (sys_exit(), 
Sys__exit()).

The logging functions (Sys_exit(), Sys__exit(), Sys(), Msg_exit(),
Msg__exit(), Msg()) on entry lock the log file for writing (an
exclusive log) and on exit or return they unlock the log file 
(using functions writelock(), fileunlock()). They all use an integer
pointer logi  (defined in log.h file). It must point to a location
where the next message sequential number is stored. Each functions
uses that number for its message and increments its value by 1 so
the next logging function can use it.

All display and logging functions return a pointer to char. It is a
string with error message. If a function executes without an error,
a null pointer is returned (meaning no error message). If the pointer
returned to it is not null, the string it points to contains the 
error message what happened. It is up to the programmer using these
functions to decide what to do if an error occurs. 

 **************************************************************************
 ************************************************************************** */

extern int *logi;
#ifdef _multithread
 extern pthread_mutex_t tlock;
#endif

#ifdef __cplusplus
   extern "C" {
      #include <stdio.h>
      #include <string.h>
      #include <sys/types.h>
      #include <fcntl.h>
      #include <errno.h>
      #include <string.h>
      #include <stdarg.h>
      #include <stdlib.h>
      #include <unistd.h>
      #include <time.h>
      #include <signal.h>
      #include <sys/stat.h>
      #include <pthread.h>

      char* sys_exit(char *fmt, ...);
      char* sys__exit(char *fmt, ...);
      char* sys(char *fmt, ...);
      char* msg_exit(char *fmt, ...);
      char* msg__exit(char *fmt, ...);
      char* msg(char *fmt, ...);
      char* Sys_exit(char *fmt, ...);
      char* Sys__exit(char *fmt, ...);
      char* Msg_exit(char *fmt, ...);
      char* Msg__exit(char *fmt, ...);
      char* Sys(char *fmt, ...);
      char* Msg(char *fmt, ...);
      char* create_log(char*);
  }
#else
  #include <stdio.h>
  #include <string.h>
  #include <sys/types.h>
  #include <fcntl.h>
  #include <errno.h>
  #include <string.h>
  #include <stdarg.h>
  #include <stdlib.h>
  #include <unistd.h>
  #include <time.h>
  #include <signal.h>
  #include <sys/stat.h>
  #include <pthread.h>

  extern char* sys_exit(char *fmt, ...);
  extern char* sys__exit(char *fmt, ...);
  extern char* sys(char *fmt, ...);
  extern char* msg_exit(char *fmt, ...);
  extern char* msg__exit(char *fmt, ...);
  extern char* msg(char *fmt, ...);
  extern char* Sys_exit(char *fmt, ...);
  extern char* Sys__exit(char *fmt, ...);
  extern char* Msg_exit(char *fmt, ...);
  extern char* Msg__exit(char *fmt, ...);
  extern char* Sys(char *fmt, ...);
  extern char* Msg(char *fmt, ...);
  extern char* create_log(char*);
#endif


#endif /* _log_h */
