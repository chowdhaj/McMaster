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
// mutex for log, required by logging functions for 
// thread-safe code
pthread_mutex_t tlock = PTHREAD_MUTEX_INITIALIZER;

//TODO define and initialize a mutex for person_counter

void* conversation(void*); // this is signature for the 
                           // threads starting routine

//TODO define a record for person
//TODO with fields: person index, tid, name, line counter,
//TODO and done indicating when the person is done with
//TODO the conversation

//TODO define an array of 8 person records
//TODO define a global variable person_counter indication 
//TODO when all threads are done

FILE* flog = NULL;

//TODO function main
//TODO check the value of _level being 1 .. 8, if not
//TODO display an error message using msg() and terminate
//TODO based on the value of _level display how many
//TODO personalities are involved. Use msg() for displaying
//TODO it.

int main() {

    //TODO function main
    //TODO check the value of _level being 1 .. 8, if not
    //TODO display an error message using msg() and terminate
    //TODO based on the value of _level display how many
    //TODO personalities are involved. Use msg() for displaying
    //TODO it.

    create_log("assgn2.log");

    //TODO inititalize your table of personalities
    //TODO set the value of done for each person to –1

    //TODO set person_counter to 0
    //TODO in a do-while loop while person_counter != 0
    //TODO   in a for loop i = 0 .. _level-1
    //TODO      if i-th person is done, continue
    //TODO      create a thread for 1 line of i-th person 
    //TODO      modify the info in the i-the person record
    //TODO   end of for loop
    //TODO   in a for loop i = 0 .. _level-1
    //TODO      if i-th person is done, continue
    //TODO      join thread for i-th person
    //TODO   end of for loop
    //TODO end of do-while loop 

    done = 0; //global variable done as person_counter indication  

    //TODO in a for loop i = 1 .. _level-1
    //TODO display how many lines i-th person processed
    //TODO end of for loop
    //TODO end of main

    return 0;

}// end function main

void* conversation(void* arg) {
  
    //TODO function conversation
    //TODO define void* variable ret and set it to NULL
    //TODO lock mutex dlock  
    //TODO get the argument (it is a pointer to person record)
    //TODO if done for this person is -1 (first run)
    //TODO    set done for this person to not done (i.e. 0)
    //TODO    increment the global person_counter
    //TODO prompt the user using msg() for the message
    //TODO read the response using fgets()
    //TODO unlock mutex dlock

    //TODO if the response was "quit"
    //TODO    lock mutex dlock
    //TODO    update done for this person to done (i.e. 1)
    //TODO    decrement the global person_counter
    //TODO    unlock mutex dlock
    //TODO    log a message that this person quit using Msg()
    //TODO    exit the thread with return value ret
    //TODO if the response was not "quit"
    //TODO    log the response using Msg()
    //TODO    update done for this person to not done (i.e. 0) 
    //TODO    increment line count for this person
    //TODO    exit the thread with return value ret
    //TODO end of function conversation

}// end function conversation
