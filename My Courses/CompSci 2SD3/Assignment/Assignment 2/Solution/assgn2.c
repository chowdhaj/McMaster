#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "log.h"

int logindex = 0;
int* logi = &logindex;
// mutex for log, required by logging functions for thread-safe code
pthread_mutex_t tlock = PTHREAD_MUTEX_INITIALIZER;

// mutex for person_count
pthread_mutex_t dlock = PTHREAD_MUTEX_INITIALIZER; 

void* conversation(void*); // this is the threads starting
                           // routine

typedef struct {
  int index;  
  pthread_t tid;  
  char name[10];
  int linecount;
  int done;
} PERSON;


PERSON person[8]; // at most 8 personalities
int person_count; // indicating if all persons are done


// function main -----------------------------------------
int main() {
  int i;
  int* ret;

  if (_level < 1 || _level > 8) {
    msg("the program was compiled with a wrong level");
    msg("permitted levels are 1 .. 8");
    return 0;
  }else{
    if (_level == 1)
      msg("There is 1 personality: Person0\n");
    else{
      msg("There are %d personalities: ",_level);
      for(i = 0; i < _level; i++)
        msg("Person%d ",i);
      msg("");
    }
  }
  create_log("assgn2.log");

  for(i = 0; i < _level; i++) {
    person[i].linecount=0;
    person[i].index=i;
    person[i].tid=-1;
    person[i].done=-1;
    sprintf(person[i].name,"Person%d",i);
  }

  person_count = 0;
  do {
    for(i = 0; i < _level; i++) {
      if (person[i].done==1) continue;
      if (pthread_create(&(person[i].tid), NULL, 
                         conversation,&person[i]) != 0)
        msg_exit("can't create thread for person \"%s\"\n",
                 person[i].name);
    }
    for(i = 0; i < _level; i++) {
      if (person[i].done==1) continue;
      if (pthread_join(person[i].tid,(void**) &ret) != 0)
        msg_exit("no thread with tid=%u [%s]\n",
                  person[i].tid,strerror(errno));
    }
  }while(person_count != 0);
  
  for(i = 0; i < _level; i++)
    msg("Person %s processed %d lines",
         person[i].name,person[i].linecount);
  
  return 0;
}// end function main




// function conversation ----------------------------------
void* conversation(void* arg) {
   char line[100];
   PERSON *p;
  
   p = (PERSON*) arg;

   pthread_mutex_lock(&dlock);
   if (p->done==-1) {
     p->done = 0;
     person_count++;
   }
  
   msg("[pid=%u,tid=%u,index=%u,name=%s] Enter Message:",
       getpid(),p->tid,p->index,p->name);
   fgets(line,100,stdin);
   line[strlen(line)-1]='\0';
   pthread_mutex_unlock(&dlock);
   
   if (strncmp(line,"quit",4)==0) {
     p->done=1;
     pthread_mutex_lock(&dlock);
     person_count--;
     pthread_mutex_unlock(&dlock);
     Msg("[pid=%u,tid=%u,index=%u,name=%s] Enter Message:\n"
         " user quit",
         getpid(),p->tid,p->index,p->name,line);
     pthread_exit(NULL);
   }
  
   // so we have a real line to log
   Msg("[pid=%u,tid=%u,index=%u,name=%s] Enter Message:\n"
       " %s",
       getpid(),p->tid,p->index,p->name,line);
   p->linecount = p->linecount+1;
   pthread_exit(NULL);
}// end function conversation
