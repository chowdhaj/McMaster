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

// defines a mutex for done
pthread_mutex_t <your mutex for done> = PTHREAD_MUTEX_INITIALIZER;

// initialize the thread function

// defining a structure to for a personality: index , the thread id
// tid , name of the personality, linecount ,
// and flag indicating when the personality's
// processing is completed.
typedef struct {
  int index;
  ...
  ...
} Personality;


Personality person[8];
// create the struct of personalities

int done = 0;
// a global variable int done=0;
// that serves as the indicator when the processing is done

// FILE* flog = NULL;


// function main --------------------------------------------------------
int main() {
  int i;
  int* value_ptr;

  // check if the make level is between 1 to 8, if not,
  // return 0 and give a warning
  // if there is a correct numbers, print out the persons
  // you can do it by using if to compare _level
  if (_level < 1 || _level > 8) {
    msg("give a waring");
    return 0;
    }

  // after checking, create a log file just like what you did in assgn1
  // with create_log()
  create_log("assgn2.log");

  // in here you would add people to the personality table with for loop
  // can give tid and done as -1
  // linecount set as 0
  for(i = 0; i < _level; i++) {
    ...;
    ...;
    ...;
    ...;
  }


  //loop for i = 0 .. _level-1
    //initialize the values on the table for for Person_i
  //endloop


  //do
    //loop for i = 0 .. _level-1
      //if Person_i not done yet, create a thread for it with pthread_create()
      //include a test if pthread_create() worked, if not,
      //display an error message and terminate the program with exit(1);
    //endloop

    //loop for i = 0 .. _level-1
      //if Person_i not done yet, join the thread with pthread_join()
      //include a test if pthread_join() worked, if not,
      //display an error message and terminate the program with exit(1);
    //endloop

  //while ! done
  //Since done starts with value 0, the testing of its value
  //must be at the bottom of the loop, not at the top of the loop


  do {
    LOOP for i = 0 to _level-1 {
      if (not done);
        //if Person_i not done yet, create a thread for it with pthread_create()
        pthread_create(&(xxx.tid), NULL, <thread function>,&person[i])
        //pthread_create(&tid, NULL, processfd, &fd)
        //The creating process (or thread) must provide a location for storage of the thread id.
        //For now, pass a null pointer to indicate the default attributes.
        //The third parameter is just the name of the function for the thread to run.
        //The last parameter is a pointer to the arguments.

        //if the pthread_create() failed,
        //display an error message and terminate the program with exit(1);
    } ENDLOOP

    LOOP for i = 0 .. _level-1
    {
      if (not done);
        pthread_join(xxx.tid,(void**) &value_ptr)
      // pthread_join(pthread_t thread, void **value_ptr)
      // if fails, display a warning
    ENDLOOP
  }

  while (done != 0));
    LOOP for i = 0 .. _level-1
      msg("Person %s processed %d lines",...);
    ENDLOOP
  return 0;
}// end function main



// function conversation ------------------------------------------
// thread functions
void* <thread function>(void* arg) {
  void* value_ptr;
  char line[100]; //the input line
  PERSON *p;

  // locks the mutex for done
  pthread_mutex_lock(&<your mutex for done>);
  // If the Person is just starting, it increments done by 1

   // Displays the prompt
   msg("[pid=%u,tid=%u,index=%u,name=%s] Enter Message:",......);

   // Gets the users response
   fgets(...);

   // Unlocks the mutex for done
   pthread_mutex_unlock(&<your mutex for done>);

   // If the response started with quit, then
      // locks the mutex for the global variable done
      // decrements done by 1
      // unlocks the mutex for done
      // displays and logs a message that the user quit
      // exits the thread, its return value is irrelevant


   if (input is "quit"):
     pthread_mutex_lock(&<your mutex for done>);
     //do decrements done by 1
     pthread_mutex_unlock(&<your mutex for done>);
     Msg("[pid=%u,tid=%u,index=%u,name=%s] Enter Message:\n user quit",...,line);
     pthread_exit(&value_ptr);
   }




   // If the response did not start with quit
      //increments by 1 the linecount for this conversation
      //writes the message consisting of the prompt and the response into the
        //log (for logging functions, you do not include the terminating
        //to the message, however, if the message is a multiple-line,
        //please follow any embedded with one space)
      //exits the thread, its return value is irrelevant



  if (not enter quit):
   Msg("[pid=%u,tid=%u,index=%u,name=%s] Enter Message:\n %s",...,line);
   //do increments by 1 the linecount for this conversation
   pthread_exit(&value_ptr);
}// end function conversation



// Testing the assgn2 with the log files:
// make assgn2 level=<#>
// ./assgn2
