#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "log.h"

int logindex = 0;
int *logi = &logindex;
// mutex for logging functions required for thread-safe code
pthread_mutex_t tlock = PTHREAD_MUTEX_INITIALIZER;

int no_of_threads = 0;
#define ARRAYSIZE  1000000
int no_of_items = 0;

// TO DO: Here go your global variables, initializes the global long array
// TO DO: declare and initialize global mutex

void init_arr() {
  srand(time(NULL));
  long i;
  for(i = 0; i < ARRAYSIZE; i++) {
    arr[i] = (long) (rand() % 10);
  }
}

// function doit ----------------------------------------
void* doit(void *params) {
  // TO DO: here goes your local variables
  // TO DO: individual sum variable

  // TO DO: get from param your thread index from the doit arguments
  // an address of where the index is stored, params is ADDRESS!!!

  // TO DO: find your slice of the array -- from and to
  // from = index * number of items
  // to = from + no_of_items - 1

  // TO DO: if to exceeds the end of the array (for the very last
  // thread), it has to be trimmed.

  // TO DO: display the message about which part of the array this threads does
  // TO DO: log the message about which part of the array this threads does

  // TO DO: sum up your portion of the array arr[]

  // TO DO: display the message about your summation
  // TO DO: log the message about your summation

  // TO DO: lock your global mutex

  // TO DO: update the global sum

  // TO DO: unlock your global mutex

  // TO DO: exit the thread

}//end doit

// function main ----------------------------------------
int main(int argc,char *argv[]) {

  // TO DO: here go your locat variables

  // TO DO: check args, argv if error, display message and terminate
  // the program

  // TO DO: set the number of threats to be dispatched

  // TO DO: check it is between 2 and 10 inclusive, if not error and
  // terminate

  create_log("assgn3.log");

  init_arr();

  // TO DO: determine no_of_items each thread is supposed to sum up
  // if the length of the array is divisible by the number of threads,
  // each thread will process the same number of items = length of the
  // array / the number of threads

  // TO DO: if it is not divisible, then the number of items
  // is = 1+length of the array / the number of threads ,
  // and the last thread will process the leftover items (which will
  // be slightly less)

  // TO DO: create dynamically array to hold the index of each
  // dispatched thread
  // TO DO: display error if failed

  // TO DO: create dynamically array to hold thread id of each
  // dispatched thread
  // TO DO: display error if failed

  // TO DO: in a loop, dispatch each thread to execute doit()
  // (see pthread_create())
  // TO DO: and display and log message "dispatched thread XXX with
  // tid = YYY"

  // TO DO: wait for all threads to complete
  // TO DO: display message "Overall sum = XXX"

  // TO DO: sum up the array arr[]

  // TO DO: and display the message "Check sum = XXX"

}//end main
