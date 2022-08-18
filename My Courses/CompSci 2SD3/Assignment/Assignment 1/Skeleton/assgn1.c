#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#include "log.h"

// define priorities
#define high    0
#define medium  1
#define low     2

// define how many times in each queue
// in the high priority queue, a job can be twice
#define hpq_times   2
// in the medium priority queue, a job can be 4 times
#define mpq_times   4
// in the low priority quere, a job can be unlimited many times

int logindex = 0;
int* logi = &logindex;

pid_t create_job(int i);
void siga_handler();   // handler for signal SIGALRM
void sigc_handler();   // handler for signal SIGCHLD
sigset_t mymask1;      // normal signal process mask when all signals are free
                       // but SIGALRM and SIGCHLD are blocked
sigset_t mymask2;      // special signal process mask when all signals are free
sigset_t jobmask;      // job signal process mask blocking all signals, leaving
                       // only SIGUSR2 unblocked
struct sigaction sa_alarm;  // disposition for SIGALRM
struct sigaction sa_chld;   // disposition for SIGCHLD

int number_of_jobs;

// TO DO
// your own data structure(s) to handle jobs and the 3 queues
// your own auxialiary variables
// END TO DO

// # data structure for jobs:
typedef struct TASK_STRUCT {
    // members: PID, priority,
    // 3 other members: hpqtimes, B, C
} JOBS;

// # JOBS list_of_jobs[99];

// # data structure for queues:
// # members: first, entity, implement maximum of 6 jobs
// # a queue for each level of priority: high, medium, low
// # functions to: insert elements into a queue // Enqueue()
// #               remove stuff from queue      // Dequeue()
// #               ??? - make

// function main ------------------------------------------------- 
int main(int argc,char** argv) {
  int i, j;
  pid_t pid;
  
  // TO DO 
  // check the number of command line arguments, if not 2, terminate
  // the program with a proper error message on the screen.
  // check if the single command line argument (argv[1]) has value 3 to 6,
  // if not, treminate the program with a proper error message on the
  // screen.
  // set appropriately number_of_jobs
  // END TO DO

  // # if (argc != 2): terminate with error message
  // #  ("ERROR:IncorrectNumberArguments")
  // # check argv[1]
  // # convert to an integer: (search this up)
  // # set number_of_jobs to argv[1]
  
  create_log("assgn1.log");
  
  // TO DO
  // prepare mymask1 -- SIGCHLD and SIGALRM blocked, all other signals free 
  // using sigemptyset(), sigfillset(), sigaddset(), sigdelset() 
  // END TO DO
 
  if ((sigemptyset(&mymask1))    == 0 ||
      (sigaddset(???, SIGALRM))  == 0 ||
      (sigaddset(???, SIGCHILD)) == 0 ) {
    // printf ("success")
  } else {
    perror("Failed");
  }
  //sigaddset(???, SIGALRM);
  // sigaddset(???, SIGCHILD);
 
  // TO DO
  // instal mymask1 as the process signal mask using sigprocmask() 
  // END TO DO 

  // # sigprocmask(SIG_SETMASK, XXX, C); // # don't need old mask
  // # XXX = "which glasses are we changing to?"
  // # C = "do we want to save the old mask?"

  // TO DO
  // prepare mymask2 -- all signals free 
  // using sigemptyset(), sigfillset(), sigaddset(), sigdelset() 
  // END TO DO

  // # set all signals to free/unblocked/1 for mymask2 // use emptyset
  
  // TO DO
  // prepare jobmask -- all signals blocked except SIGUSR2 
  // using sigemptyset(), sigfillset(), sigaddset(), sigdelset() 
  // END TO DO

  // TO DO
  // prepare SIGALRM disposition sa_alarm
  // its handler (sa_handler) is siga_handler()
  // its signal mask (sa_mask) must block all signals
  // its flags (sa_flags) must be set to SA_RESTART 
  // END TO DO
  // # sa_alarm.sa_handler = ??? 
  
  // TO DO
  // instal SIGALRM disposition using sigaction() 
  // END TO DO
  sigaction(ACTION, NEW_STRUCT, NULL);
  
  // TO DO
  // prepare SIGCHLD disposition sa_chld
  // its handler (sa_handler) is sigc_handler()
  // its signal mask (sa_mask) must block all signals
  // its flags (sa_flags) must be set to SA_RESTART 
  // END TO DO

  // TO DO
  // instal SIGCHLD disposition using sigaction() 
  // END TO DO

  // TO DO
  // create empty high-priority queue
  // create empty medium-priority queue
  // create empty low-priority queue
  // END TO DO

  high_priority_queue = CALL_SOME_FUNCTION_TO_CREATE_IT();
  medium_priority_queue = CALL_SOME_FUNCTION_TO_CREATE_IT();
  // low
  
  // TO DO
  // create a data structure to keep information about jobs - PID, number of runs
  // for(i = 0; i < number_of_jobs; i++) {
  //   pid = create_job(i);
  //   save pid for job i in your data structure
  //   JOBS.pid = pid
  //   JOBS.priority = 2
  //   JOBS.A = ???
  //   JOBS.B = ??? 
  //   ... 
  //   Enqueue(high_prior, JOB);
  // }
  // put all jobs in the high-priority queue
  // END TO DO

  // TO DO
  // in a loop
  //    if all queues are empty
  //       record it in the log by Msg("All jobs done");
  //       and display it on the screen by msg("All jobs done");
  //       and terminate the loop
  //    "switch on" the first job from the highest-priority non-empty queue
  //    by sending it the SIGUSR1 signal (using sigsend())
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

  // # kill(JOB.PID, SIGUSR1);
    
  return 0;
}// end function main
  
// function create_job -------------------------------------------- 
pid_t create_job(int i) {

  pid_t pid;
  
  char argv0[10];
  char argv1[10];
  
  // TO DO
  // switch process signal mask from mymask1 to jobmask 
  // using sigprocmask()
  // END TO DO
  // # currently the mask is mymask1
  // # switch to jobmask using sigprocmask()

  sigprocmask(SIG_SETMASK, jobmask, C); // # don't need old mask
  
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

  // # sigprocmask(A,B,C);
  // # same as above, except for 'B'
 
  return pid;
}// end function create_job
  
// function siga_handler ------------------------------------------ 
void siga_handler() {

  // # THIS IS STEP 5
  // TO DO
  // "switch of" the currently executing job by sending it SIGUSR2 signal
  // (using sigsend())
  // either put the job back to the queue it came from (you must count
  // how many times it has been through the queue) or "demote it" to the
  // lower-prority queue.
  // record this in the log using 
  //     Msg("Switched off high-priority job %d",job number); or
  //     Msg("Switched off medium-priority job %d",job number); or
  //     Msg("Switched off low-priority job %d",job number);
  // announce it on the screen suing corresponding msg();
  // END TO DO 

  // # if (JOB.hpqtimes == 2) {
  // #  Enqueue(mpq, JOB)
  // }

  return;
}// end function siga_handler
  
// function sigc_handler ------------------------------------------ 
void sigc_handler() {
  // TO DO
  // disarm the alarm
  // record in the log that the currently executing job is done by
  // Msg("job %d done",job number);
  // END TO DO 
}// end function sigc_handler

// TO DO
// functions for handling your data structures
// END TO DO

// # Add to queue
void Enqueue(param1, param2) {
    // # add element to queue
}

// # Remove from queue
int Dequeue(param1, param2) {
    // # delete element from queue
}
