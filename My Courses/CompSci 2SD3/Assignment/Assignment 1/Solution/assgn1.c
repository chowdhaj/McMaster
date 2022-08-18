#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#include "log.h"

#define high    0
#define medium  1
#define low     2

#define hpq_times   2
#define mpq_times   4

int logindex = 0;
int* logi = &logindex;

pid_t create_job(int i);
void siga_handler();   // handler for signal SIGALRM
void sigc_handler();   // handler for signal SIGCHLD
sigset_t mymask1;      // normal signal process mask when 
                       // all signals are free
                       // but SIGALRM and SIGCHLD are blocked
sigset_t mymask2;      // special signal process mask when 
                       // all signals are free
sigset_t jobmask;      // job signal process mask blocking 
                       // all signals, leavingonly SIGUSR2 
                       // unblocked
struct sigaction sa_alarm;  // disposition for SIGALRM
struct sigaction sa_chld;   // disposition for SIGCHLD

int number_of_jobs;

// TO DO
// your own data structure(s) to handle jobs and the 3 queues
// your own auxialiary variables
// END TO DO
typedef struct QUEUE_STRUCT {
  int queue[6];     // there are at most 6 jobs
  int first;
  int last;
} QUEUE;
QUEUE* CreateEmptyQueue();
void InsertIntoQueue(QUEUE* qu,int index);
int RemoveFromQueue(QUEUE* qu);

QUEUE *hp=NULL;  // pointer to high-priority queue
QUEUE *mp=NULL;  // pointer to midle-priority queue
QUEUE *lp=NULL;  // pointer to low-priority queue

typedef struct JOB_STRUCT {
  pid_t pid;
  int nof_runs_hp;
  int nof_runs_mp;
  int done;
  int priority;
} JOB;

JOB job_table[6]; // there are at most 6 jobs
int current=-1;    // index of current job


// function main -----------------------------------------
int main(int argc,char** argv) {
  int i, j;
  pid_t pid;
  
  // TO DO 
  // check the number of command line arguments, if not 2, 
  // terminate
  // the program with a proper error message on the screen.
  // check if the single command line argument (argv[1]) 
  // has value 3 to 6,
  // if not, treminate the program with a proper error 
  // message on the screen.
  // set appropriately number_of_jobs
  // END TO DO 
  if (argc!=2)
    msg_exit("usage --- %s <number-of-jobs>\n",argv[0]);
  number_of_jobs=atoi(argv[1]);
  if (number_of_jobs < 3 || number_of_jobs > 6)
    msg_exit("incorrect number of jobs\n");
  
  create_log("assgn1.log");
  
  // TO DO
  // prepare mymask1 -- SIGCHLD and SIGALRM blocked, all 
  // other signals free 
  // using sigemptyset(), sigfillset(), sigaddset(), 
  // sigdelset() 
  // END TO DO
  sigemptyset(&mymask1);   // mymask1 -- SIGCHLD and 
                           // SIGALRM blocked
  sigaddset(&mymask1,SIGCHLD);
  sigaddset(&mymask1,SIGALRM);
 
  // TO DO
  // instal mymask1 as the process signal mask using 
  // sigrpocmask() 
  // END TO DO 
  sigprocmask(SIG_SETMASK,&mymask1,NULL);
  
  // TO DO
  // prepare mymask2 -- all signals free 
  // using sigemptyset(), sigfillset(), sigaddset(), 
  // sigdelset() 
  // END TO DO
  sigemptyset(&mymask2); // mymask2 -- all signals free
  
  // TO DO
  // prepare jobmask -- all signals blocked except SIGUSR2 
  // using sigemptyset(), sigfillset(), sigaddset(), 
  // sigdelset() 
  // END TO DO
  sigfillset(&jobmask);
  sigdelset(&jobmask,SIGUSR2); // all signals but SIGUSR2 
                               // blocked

  // TO DO
  // prepare SIGALRM disposition sa_alarm
  // its handler (sa_handler) is siga_handler()
  // its signal mask (sa_mask) must block all signals
  // its flags (sa_flags) must be set to SA_RESTART 
  // END TO DO
  sa_alarm.sa_handler = siga_handler;
  sigfillset(&sa_alarm.sa_mask);
  sa_alarm.sa_flags = SA_RESTART;
  
  // TO DO
  // instal SIGALRM disposition using sigaction() 
  // END TO DO
  sigaction(SIGALRM,&sa_alarm,NULL);
  
  // TO DO
  // prepare SIGCHLD disposition sa_chld
  // its handler (sa_handler) is sigc_handler()
  // its signal mask (sa_mask) must block all signals
  // its flags (sa_flags) must be set to SA_RESTART 
  // END TO DO
  sa_chld.sa_handler = sigc_handler;
  sigfillset(&sa_chld.sa_mask);
  sa_chld.sa_flags = SA_RESTART;

  // TO DO
  // instal SIGCHLD disposition using sigaction() 
  // END TO DO
  sigaction(SIGCHLD,&sa_chld,NULL);

  // TO DO
  // create empty high-priority queue
  // create empty medium-priority queue
  // create empty low-priority queue
  // END TO DO
  hp=CreateEmptyQueue();
  mp=CreateEmptyQueue();
  lp=CreateEmptyQueue();
  
  // TO DO
  // create a data structure to keep information about 
  // jobs - PID, number of runs
  // for(i = 0; i < number_of_jobs; i++) {
  //   pid = create_job(i);
  //   save pid for job i in your data structure
  // }
  // put all jobs in the high-priority queue
  // END TO DO
  for(i = 0; i < number_of_jobs; i++) {
    pid = create_job(i);
    job_table[i].pid=pid;
    job_table[i].nof_runs_hp=0;
    job_table[i].nof_runs_mp=0;
    job_table[i].done=0;
    job_table[i].priority=high;
    InsertIntoQueue(hp,i);
  }

  // TO DO
  // in a loop
  //    if all queues are empty
  //       record it in the log by Msg("All jobs done");
  //       and 
  //       display it on the screen by msg("All jobs done");
  //       and terminate the loop
  //    "switch on" the first job from the highest-priority 
  //    non-empty queue by sending it the SIGUSR1 signal 
  //    (using kill())
  //    Record it in the log using 
  //        Msg("Switched on high-priority job %d",job number);  or
  //        Msg("Switched on medium-priority job %d",job number); or
  //        Msg("Switched on low-priority job %d",job number); 
  //    announce it on the screen using corresponding msg();
  //    set alarm for 1 second using alarm()
  //    switch the current signal process mask mymask1 to mymask2 while
  //    going to suspension using sigsuspend()
  //    (thus only SIGCHLD or SIGALRM will wake it up from suspension
  //    SIGCHLD indicates that the job that is currently executing just
  //    terminated, SIGALRM indicates that the time for the job currently
  //    executing is up and it must be "switched off")
  // end loop
  // END TO DO
  while(1) {
    if ((current = RemoveFromQueue(hp)) < 0) {
      if ((current = RemoveFromQueue(mp)) < 0) {
        if ((current = RemoveFromQueue(lp)) < 0) {
          Msg("All jobs done");
	  break;
	}
      }
    }
    // current is the job to be switched on
    if (job_table[current].priority==high) {
      Msg("Switched on high-priority job %d",current); 
      msg("Switched on high-priority job %d",current); 
    }else if (job_table[current].priority==medium) {
      Msg("Switched on medium-priority job %d",current); 
      msg("Switched on medium-priority job %d",current); 
    }else{
      Msg("Switched on low-priority job %d",current); 
      msg("Switched on low-priority job %d",current); 
    }
    kill(job_table[current].pid,SIGUSR1);
    // now we unblock SIGCHLD and SIGALRM and wait
    alarm(1);
    sigsuspend(&mymask2);
  }
    
  return 0;
}// end function main
  
  
// function create_job -----------------------------------
pid_t create_job(int i) {
  pid_t pid;
  char argv0[10];
  char argv1[10];
  
  // TO DO
  // switch process signal mask from mymask1 to jobmask 
  // using sigprocmask()
  // END TO DO
  sigprocmask(SIG_SETMASK,&jobmask,NULL);
  
  if ((pid = fork()) < 0) 
    Sys_exit("fork error\n");
  if (pid == 0) { // child process
    strcpy(argv0,"job");
    sprintf(argv1,"%d",i);
    execl("job",argv0,argv1,NULL);
  }
  
  // parent process
  // TO DO
  // switch process signal mask from jobmask back to mymask1 
  // using sigprocmask()
  // END TO DO 
  sigprocmask(SIG_SETMASK,&mymask1,NULL); 
  return pid;
}// end function create_job
  
  
  
  
// function siga_handler ----------------------------------
void siga_handler() {
  int i;
  // TO DO
  // "switch of" the currently executing job by sending it SIGUSR2 signal
  // (using kill())
  // either put the job back to the queue it came from (you must count
  // how many times it has been through the queue) or "demote it" to the
  // lower-prority queue.
  // record this in the log using 
  //     Msg("Switched off high-priority job %d\n",job number); or
  //     Msg("Switched off medium-priority job %d\n",job number);
  //     Msg("Switched off low-priority job %d\n",job number);
  // announce it on the screen suing corresponding msg();
  // END TO DO 
  i = current;
  current = -1;
  kill(job_table[i].pid,SIGUSR1);
  if (job_table[i].priority==high) {
    Msg("Switched off high-priority job %d",i);
    msg("Switched off high-priority job %d",i);
  }else if (job_table[i].priority==medium) {
    Msg("Switched off medium-priority job %d",i);
    msg("Switched off medium-priority job %d",i);
  }else{
    Msg("Switched off low-priority job %d",i);
    msg("Switched off low-priority job %d",i);
  }
  if (job_table[i].priority==high) {
    job_table[i].nof_runs_hp++;
    if (job_table[i].nof_runs_hp < hpq_times) {  // keep it high
      job_table[i].priority=high;
      InsertIntoQueue(hp,i);
    }else{                                       // demote it
      job_table[i].priority=medium;
      InsertIntoQueue(mp,i);
    }
  }else if (job_table[i].priority==medium) {    
    job_table[i].nof_runs_mp++;
    if (job_table[i].nof_runs_mp < mpq_times) {  // keep it medium
      job_table[i].priority=medium;
      InsertIntoQueue(mp,i);
    }else{                                       // demote it
      job_table[i].priority=low;
      InsertIntoQueue(lp,i);
    }
  }else
    InsertIntoQueue(lp,i);        // keep it low
  return;
}// end function siga_handler
  
  
// function sigc_handler ----------------------------------
void sigc_handler() {
  // TO DO
  // disarm the alarm
  // record in the log that the currently executing job is done by
  // Msg("job %d done",job number);
  // END TO DO 
  alarm(0); 
  if (current==-1) return;      // nothing to do

  // so current is done
  Msg("job %d done",current);
  job_table[current].done=1;
  current = -1; // no current
}// end function sigc_handler


// TO DO
// functions for handling your data structures
// END TO DO

// function CreateEmptyQueue -----------------------------
QUEUE* CreateEmptyQueue() {
  QUEUE* q;
  q=(QUEUE*)malloc(sizeof(QUEUE));
  if (q==NULL)
     Msg_exit("[CreateEmptyQueue] memory allocation error\n");
  q->first=q->last=-1;
  return q;
}// end function CreateEmpty Queue


// function InsertIntoQueue -------------------------------
void InsertIntoQueue(QUEUE* qu,int index) {
  if (qu->first == -1) {
    qu->queue[0]=index;
    qu->last=qu->first=0;
    return;
  }
  if (qu->last==5) 
    qu->queue[qu->last=0]=index; 
  else 
    qu->queue[++(qu->last)]=index;
}// end function InsertIntoQueue


// function RemoveFromQueue -------------------------------
int RemoveFromQueue(QUEUE* qu) {
  int index;

  if (qu->first==-1) return -1;
  if (qu->first==qu->last) {
    index = qu->queue[qu->last];
    qu->last=qu->first=-1;
    return index;
  }
  if (qu->first==5){  
     index=qu->queue[5]; 
     qu->first=0; 
     return index;
  }
  index=qu->queue[qu->first];
  (qu->first)++; 
  return index;
}// end function RemoveFromQueue
