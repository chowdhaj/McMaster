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


#include "log.h"
      
static char* print_msg(char *fmt,va_list ap,int fd);
static int writelock(int fd);
static int fileunlock(int fd);
static int readlock(int fd);
static char* open_log();
static char* close_log();


static int logfd;
static char logpath[500] = "";
static int futil_errno;
static char buf[500];
/* mask for unblocking all catchable signals */
static sigset_t zeromask = {0x0,0x0};
/* mask for blocking all catchable signals */
static sigset_t allmask = {0xffffffff,0xffffffff};
static char* ss;




#undef install_masks
#ifdef _multithread
 #define install_masks(mask1,mask2) \
   if (sigprocmask(SIG_SETMASK,mask1,mask2) < 0) {\
     sprintf(buf,"[system error: %s]\n sigprocmask SIG_SETMASK error\n",  \
             strerror(errno)); \
     pthread_mutex_unlock(&tlock); \
     return buf;\
   }
#else
 #define install_masks(mask1,mask2) \
   if (sigprocmask(SIG_SETMASK,mask1,mask2) < 0) {\
     sprintf(buf,"[system error: %s]\n sigprocmask SIG_SETMASK error\n",  \
             strerror(errno)); \
     return buf;\
   }
#endif

#undef install_mask
#ifdef _multithread
 #define install_mask(mask) \
   if (sigprocmask(SIG_SETMASK,mask,NULL) < 0) {\
     sprintf(buf,"[system error: %s]\n sigprocmask SIG_SETMASK error\n",  \
             strerror(errno)); \
     pthread_mutex_unlock(&tlock); \
     return buf;\
   }
#else
 #define install_mask(mask) \
   if (sigprocmask(SIG_SETMASK,mask,NULL) < 0) {\
     sprintf(buf,"[system error: %s]\n sigprocmask SIG_SETMASK error\n",  \
             strerror(errno)); \
     return buf;\
   }
#endif




/* function sys_exit ------------------------------------------- */
char* sys_exit(char *fmt, ...)
{
 va_list ap;
 int errno_save;

 #ifdef _multithread
   pthread_mutex_lock(&tlock);
 #endif
 install_mask(&allmask);

 errno_save = errno;

 printf(" [system error: %s]\n ",strerror(errno_save));
 fflush(stdout);
 va_start(ap,fmt);
 if ((ss = print_msg(fmt,ap,fileno(stdout))) != NULL) {
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return ss;
 }
 va_end(ap);

 #ifdef _multithread
  pthread_mutex_unlock(&tlock);
 #endif
 exit(1);
}/* end sys_exit */




/* function sys__exit ------------------------------------------- */
char* sys__exit(char *fmt, ...)
{
 va_list ap;
 int errno_save;

 #ifdef _multithread
   pthread_mutex_lock(&tlock);
 #endif
 install_mask(&allmask);

 errno_save = errno;
 
 printf(" [system error: %s]\n ",strerror(errno_save));
 fflush(stdout);
 va_start(ap,fmt);
 if ((ss = print_msg(fmt,ap,fileno(stdout))) != NULL) {
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return ss;
 }
 va_end(ap);

 #ifdef _multithread
   pthread_mutex_unlock(&tlock);
 #endif
 
 _exit(1);
 
}/* end sys_exit */




/* function sys ------------------------------------------- */
char* sys(char *fmt, ...)
{
 va_list ap;
 int errno_save;
 sigset_t oldmask;
 
 #ifdef _multithread
   pthread_mutex_lock(&tlock);
 #endif
 install_masks(&allmask,&oldmask);
 
 errno_save = errno;
 
 printf(" [system error: %s]\n ",strerror(errno_save));
 fflush(stdout);
 va_start(ap,fmt);
 if ((ss = print_msg(fmt,ap,fileno(stdout))) != NULL) {
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return ss;
 }
 va_end(ap);

 install_mask(&oldmask);

 #ifdef _multithread
   pthread_mutex_unlock(&tlock);
 #endif
 return NULL;
}/* end sys */






/* function msg_exit ------------------------------------------- */
char* msg_exit(char *fmt, ...)
{
 va_list ap;
 
 #ifdef _multithread
   pthread_mutex_lock(&tlock);
 #endif
 install_mask(&allmask);
 
 va_start(ap,fmt);
 if ((ss = print_msg(fmt,ap,fileno(stdout))) != NULL) {
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return ss;
 }
 va_end(ap);
 
 #ifdef _multithread
   pthread_mutex_unlock(&tlock);
 #endif

 exit(1);
}/* end msg_exit */






/* function msg__exit ------------------------------------------- */
char* msg__exit(char *fmt, ...)
{
 va_list ap;

 #ifdef _multithread
   pthread_mutex_lock(&tlock);
 #endif
 install_mask(&allmask);
 
 va_start(ap,fmt);
 if ((ss = print_msg(fmt,ap,fileno(stdout))) != NULL) {
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return ss;
 }
 va_end(ap);
 
 #ifdef _multithread
  pthread_mutex_unlock(&tlock);
 #endif
 _exit(1);
}/* end msg_exit */




/* function msg ------------------------------------------- */
char* msg(char *fmt, ...)
{
 va_list ap;
 sigset_t oldmask;
 
 #ifdef _multithread
   pthread_mutex_lock(&tlock);
 #endif
 install_masks(&allmask,&oldmask);
 
 va_start(ap,fmt);
 if ((ss = print_msg(fmt,ap,fileno(stdout))) != NULL) {
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return ss;
 }
 va_end(ap);
 
 install_mask(&oldmask);

 #ifdef _multithread
  pthread_mutex_unlock(&tlock);
 #endif
 return NULL;
}/* end msg */






/* function Sys_exit ------------------------------------------- */
char* Sys_exit(char *fmt, ...)
{
 va_list ap;
 time_t t;
 struct tm *stm;
 int errno_save, i;
 char tbuf[40];

 #ifdef _multithread
   pthread_mutex_lock(&tlock);
 #endif
 errno_save = errno;

 install_mask(&allmask);
 
 if ((ss = open_log()) != NULL) {
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return ss;
 }
 
 if (writelock(logfd) < 0) {
   sprintf(buf," [system error %s]\n Sys_exit writelock error\n",
           strerror(futil_errno));
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return buf;
 }
 
 if (lseek(logfd,0,SEEK_END) == -1) {
   sprintf(buf," [system error %s]\n Sys_exit lseek error\n",
           strerror(futil_errno));
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return buf;
 }
 
 t = time(NULL);
 stm = localtime(&t);
 strftime(tbuf,9,"%X",stm);
 strcat(tbuf," ");
 strftime(&tbuf[9],9,"%x",stm);
 
 sprintf(buf,"message number = %d, process id = %d, time and date = %s\n"
             " [system error: %s]\n ",
        (*logi)++,getpid(),tbuf,strerror(errno_save));
 
 i = strlen(buf);
 if (i != write(logfd,(void *)&buf[0],i)) {
   sprintf(buf," [system error: %s]\n Sys_exit write error\n",strerror(errno));
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return buf;
 }
 
 va_start(ap,fmt);
 if ((ss = print_msg(fmt,ap,logfd)) != NULL) {
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return ss;
 }
 va_end(ap);
 if (fileunlock(logfd) < 0) {
   sprintf(buf," [system error: %s]\n Sys_exit fileunlock error\n",
           strerror(futil_errno));
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return buf;
 }

 #ifdef _multithread
  pthread_mutex_unlock(&tlock);
 #endif
 exit(1);
}/* end Sys_exit */





/* function Sys__exit ------------------------------------------- */
char* Sys__exit(char *fmt, ...)
{
 va_list ap;
 time_t t;
 struct tm *stm;
 int errno_save, i;
 char tbuf[40];
 
 #ifdef _multithread
   pthread_mutex_lock(&tlock);
 #endif
 errno_save = errno;
 
 install_mask(&allmask);
 
 if ((ss = open_log()) != NULL) {
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return ss;
 }
 
 if (writelock(logfd) < 0) {
   sprintf(buf," [system error %s]\n Sys__exit writelock error\n",
          strerror(futil_errno));
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return buf;
 }
 if (lseek(logfd,0,SEEK_END) == -1) {
   sprintf(buf," [system error %s]\n Sys__exit lseek error\n",
           strerror(futil_errno));
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return buf;
 }
 t = time(NULL);
 stm = localtime(&t);
 strftime(tbuf,9,"%X",stm);
 strcat(tbuf," ");
 strftime(&tbuf[9],9,"%x",stm);
 
 sprintf(buf,"message number = %d, process id = %d, time and date = %s\n"
             " [system error: %s]\n ",
         (*logi)++,getpid(),tbuf,strerror(errno_save));
 
 i = strlen(buf);
 if (i != write(logfd,(void *)&buf[0],i)) {
   sprintf(buf," [system error: %s]\n Sys__exit write error\n",strerror(errno));
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return buf;
 }
 
 va_start(ap,fmt);
 if ((ss = print_msg(fmt,ap,logfd)) != NULL) {
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return ss;
 }
 va_end(ap);
 if (fileunlock(logfd) < 0) {
   sprintf(buf," [system error: %s]\n Sys__exit fileunlock error\n",
           strerror(futil_errno));
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return buf;
 }
 
 if ((ss = close_log()) != NULL) {
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return ss;
 }
 
 #ifdef _multithread
  pthread_mutex_unlock(&tlock);
 #endif
 _exit(1);
}/* end Sys__exit */
 




/* function Msg_exit ------------------------------------------- */
char* Msg_exit(char *fmt, ...)
{
 va_list ap;
 time_t t;
 struct tm *stm;
 char tbuf[40];
 int i;
 
 #ifdef _multithread
   pthread_mutex_lock(&tlock);
 #endif
 install_mask(&allmask);

 if ((ss = open_log()) != NULL) {
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return ss;
 } 
 
 if (writelock(logfd) < 0) {
   sprintf(buf," [system error: %s]\n Msg_exit writelock error\n",
           strerror(futil_errno));
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return buf;
 }
 if (lseek(logfd,0,SEEK_END) == -1) {
   sprintf(buf," [system error %s]\n Msg_exit lseek error\n",
           strerror(futil_errno));
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return buf;
 }
 t = time(NULL);
 stm = localtime(&t);
 strftime(tbuf,9,"%X",stm);
 strcat(tbuf," ");
 strftime(&tbuf[9],9,"%x",stm);
 
 sprintf(buf,"message number = %d, process id = %d, time and date = %s\n ",
         (*logi)++,getpid(),tbuf);  
 i = strlen(buf);
 
 if (i != write(logfd,(void *)&buf[0],i)) {
   sprintf(buf," [system error: %s]\n Msg_exit write error\n",strerror(errno));
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return buf;
 }
 va_start(ap,fmt);
 if ((ss = print_msg(fmt,ap,logfd)) != NULL) {
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return ss;
 }
 va_end(ap);
 if (fileunlock(logfd) < 0) {
   sprintf(buf," [system error: %s]\n Msg_exit fileunlock error\n",
          strerror(futil_errno));
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return buf;
 }
 
 exit(1);
}/* end Msg_exit */




/* function Msg__exit ------------------------------------------- */
char* Msg__exit(char *fmt, ...)
{
 va_list ap;
 time_t t;
 struct tm *stm;
 char tbuf[40];
 int i;

 #ifdef _multithread
   pthread_mutex_lock(&tlock);
 #endif
 install_mask(&allmask);

 if ((ss = open_log()) != NULL) {
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return ss;
 }
 
 if (writelock(logfd) < 0) {
   sprintf(buf," [system error: %s]\n Msg__exit writelock error\n",
          strerror(futil_errno));
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return buf;
 }
 if (lseek(logfd,0,SEEK_END) == -1) {
   sprintf(buf," [system error %s]\n Msg__exit lseek error\n",
          strerror(futil_errno));
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return buf;
 }
 t = time(NULL);
 stm = localtime(&t);
 strftime(tbuf,9,"%X",stm);
 strcat(tbuf," ");
 strftime(&tbuf[9],9,"%x",stm);
 
 sprintf(buf,"message number = %d, process id = %d, time and date = %s\n ",
         (*logi)++,getpid(),tbuf);  
 i = strlen(buf);
 
 if (i != write(logfd,(void *)&buf[0],i)) {
   sprintf(buf," [system error: %s]\n Msg__exit write error\n",strerror(errno));
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return buf;
 }
 va_start(ap,fmt);
 if ((ss = print_msg(fmt,ap,logfd)) != NULL) {
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return ss;
 }
 va_end(ap);
 if (fileunlock(logfd) < 0) {
   sprintf(buf," [system error: %s]\n Msg__exit fileunlock error\n",
          strerror(futil_errno));
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return buf;
 }
 
 if ((ss = close_log()) != NULL) {
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return ss;
 }
 
 _exit(1);
}/* end Msg__exit */




/* function Sys ------------------------------------------- */
char* Sys(char *fmt, ...)
{
 va_list ap;
 time_t t;
 struct tm *stm;
 int errno_save, i;
 char tbuf[40];

 #ifdef _multithread
   pthread_mutex_lock(&tlock);
 #endif
 errno_save = errno;

 install_mask(&allmask);

 if ((ss = open_log()) != NULL) {
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return ss;
 }
 
 if (writelock(logfd) < 0) {
   sprintf(buf," [system error %s]\n Sys writelock error\n",
          strerror(futil_errno));
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return buf;
 }
 if (lseek(logfd,0,SEEK_END) == -1) {
   sprintf(buf," [system error %s]\n Sys lseek error\n",strerror(futil_errno));
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return buf;
 }
 t = time(NULL);
 stm = localtime(&t);
 strftime(tbuf,9,"%X",stm);
 strcat(tbuf," ");
 strftime(&tbuf[9],9,"%x",stm);
 
 sprintf(buf,"message number = %d, process id = %d, time and date = %s\n"
             " [system error: %s]\n ",
         (*logi)++,getpid(),tbuf,strerror(errno_save));
 i = strlen(buf);
 if (i != write(logfd,(void *)&buf[0],i)) {
   sprintf(buf," [system error: %s]\n Sys write error\n",strerror(errno));
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return buf;
 }
 
 va_start(ap,fmt);
 if ((ss = print_msg(fmt,ap,logfd)) != NULL) {
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return ss;
 }
 va_end(ap);
 if (fileunlock(logfd) < 0) {
   sprintf(buf," [system error: %s]\n Sys fileunlock error\n",
          strerror(futil_errno));
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return buf;
 }
 
 if ((ss = close_log()) != NULL) {
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return ss;
 }
 
 #ifdef _multithread
  pthread_mutex_unlock(&tlock);
 #endif
 return NULL;
}/* end Sys */
 





/* function Msg ------------------------------------------- */
char* Msg(char *fmt, ...)
{
 va_list ap;
 time_t t;
 struct tm *stm;
 char tbuf[40];
 int i;
 sigset_t oldmask;

 #ifdef _multithread
   pthread_mutex_lock(&tlock);
 #endif
 install_masks(&allmask,&oldmask);

 if ((ss = open_log()) != NULL) {
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return ss;
 }
 
 if (writelock(logfd) < 0) {
   sprintf(buf," [system error: %s]\n Msg writelock error\n",strerror(errno));
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return buf;
 }
 if (lseek(logfd,0,SEEK_END) == -1) {
   sprintf(buf," [system error %s]\n Msg lseek error\n",strerror(futil_errno));
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return buf;
 }
 
 t = time(NULL);
 stm = localtime(&t);
 strftime(tbuf,9,"%X",stm);
 strcat(tbuf," ");
 strftime(&tbuf[9],9,"%x",stm);
 
 sprintf(buf,"message number = %d, process id = %d, time and date = %s\n ",
         (*logi)++,getpid(),tbuf);  
 i = strlen(buf);
 
 if (i != write(logfd,(void *)&buf[0],i)) {
   sprintf(buf," [system error: %s]\n Msg write error\n",strerror(errno));
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return buf;
 }
 va_start(ap,fmt);
 if ((ss = print_msg(fmt,ap,logfd)) != NULL) {
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return ss;
 }
 va_end(ap);
 if (fileunlock(logfd) < 0) {
   sprintf(buf," [system error: %s]\n Msg fileunlock error\n",
          strerror(futil_errno));
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return buf;
 }
 
 install_mask(&oldmask);
 
 if ((ss = close_log()) != NULL) {
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return ss;
 }
 
 #ifdef _multithread
  pthread_mutex_unlock(&tlock);
 #endif
 return NULL;
}/* end Msg */
 







/* function create_log ------------------------------------------ */
char* create_log(char* pathname)
{
 mode_t filemask;

 #ifdef _multithread
   pthread_mutex_lock(&tlock);
 #endif

 if (strlen(pathname) > 500) {
   sprintf(buf,"log pathname too long\n");
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return buf;
 }

 filemask = umask(0);
 logfd = open(pathname,(O_WRONLY|O_CREAT|O_TRUNC),
              (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH));
 umask(filemask);
 if (logfd < 0) {
   sprintf(buf,"[system error: %s]\n can't create log file \'%s\'\n",
           strerror(errno),pathname);
   #ifdef _multithread
     pthread_mutex_unlock(&tlock);
   #endif
   return buf;
 }
 
 strcpy(logpath,pathname);
 
 /* creation OK */
 #ifdef _multithread
  pthread_mutex_unlock(&tlock);
 #endif
 return NULL;
}/* end create_log */




/* these are "private functions -------------------------------- */


/* function print_msg ------------------------------------------- */
static char* print_msg(char *fmt,va_list ap,int fd)
{
 int i;

 vsprintf(buf,fmt,ap);
 strcat(buf,"\n");
 i = strlen(buf);
 if (i != write(fd,(void *)&buf[0],i)) {
   sprintf(buf," [system error %s]\n print_msg error\n",strerror(errno));
   return buf;
 }

 return NULL;
}/* end print_msg */






/* function open_log ------------------------------------------ */
static char* open_log()
{
 mode_t filemask;
 
 filemask = umask(0);
 logfd = open(logpath,(O_WRONLY|O_CREAT),
                 (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH));
 umask(filemask);
 if (logfd < 0) {
   sprintf(buf,"[system error: %s]\n can't append %s\n",strerror(errno),
           logpath);
   return buf;
 }
 
 return NULL;
}/* end open_log */





/* function close_log ------------------------------------------ */
static char* close_log()
{
 if (logfd < 0)
   return NULL;

 if (close(logfd) < 0) {
   sprintf(buf,"[system error: %s]\n can't close log\n",strerror(errno));
   return buf;
 }

 return NULL;
}/* end close_log */





/* lock a whole file for writing.  Returns 0 if lock set,
   -1 if the file is already locked and so lock could not
   be set. */

/* function writelock ------------------------------------- */
static int writelock(int fd)
{
 struct flock lock;

 lock.l_type = F_WRLCK;
 lock.l_start = 0;
 lock.l_whence = SEEK_SET;
 lock.l_len = 0;
 lock.l_pid = getpid();

 while(1) {
  if (fcntl(fd,F_SETLK,&lock) < 0)
    if (errno == EACCES || errno == EAGAIN)
        continue;
    else{
      futil_errno = errno;
      return(-1);
    }
  else
    return(0);
 }/*endwhile*/
}/* end writelock */




/* unlock  a file locked by writelock */

/* function fileunlock ------------------------------------- */
static int fileunlock(int fd)
{
 struct flock lock;
 int i;

 lock.l_type = F_UNLCK;
 lock.l_start = 0;
 lock.l_whence = SEEK_SET;
 lock.l_len = 0;
 lock.l_pid = getpid();
 
 if ((i = fcntl(fd,F_SETLK,&lock)) < 0)
   futil_errno = errno;
 return(i);
}/* end fileunlock */
 



/* lock a whole file for reading.  Returns 0 if lock set,
   -1 if the file is already locked and so lock could not
   be set. */

/* function readlock ------------------------------------- */
static int readlock(int fd)
{
 struct flock lock;

 lock.l_type = F_RDLCK;
 lock.l_start = 0;
 lock.l_whence = SEEK_SET;
 lock.l_len = 0;
 lock.l_pid = getpid();

 while(1) {
  if (fcntl(fd,F_SETLK,&lock) < 0)
    if (errno == EACCES || errno == EAGAIN)
        continue;
    else{
      futil_errno = errno;
      return(-1);
    }
  else
    return(0);
 }/*endwhile*/
}/* end readlock */
