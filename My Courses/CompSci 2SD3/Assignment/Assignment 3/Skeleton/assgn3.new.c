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

// TO DO: Here go your global variables, initializes the global long
// array
unsigned long sum = 0.0, arr[ARRAYSIZE];

// TO DO: declare and initialize global mutex
pthread_mutex_t ...

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
    long i, from, to;
    // individual sum variable
    long local sum = 0;

  // TO DO: get from param your thread index from the doit arguments
  // an address of where the index is stored, params is ADDRESS!!!
    long index = *((long *) params);

  // TO DO: find your slice of the array -- from and to
  // from = index * number of items
  from =
  // to = from + no_of_items - 1
  to =
  // if to exceeds the end of the array (for the very last thread), it has to be trimmed.
  if ("to" larger than the Array Size)
    to = Array Size;


  // TO DO: display the message about which part of the array this threads does
  // TO DO: log the message about which part of the array this threads does
  msg("Thread %d processing the array from %d to %d",
     ...);
  Msg("Thread %d processing the array from %d to %d",
     ...);

  // TO DO: sum up your portion of the array arr[]
  for (from "from" to "to" )
  summing up arr elements and give it to local sum;

  // TO DO: display the message about your summation
  // TO DO: log the message about your summation
  msg("Thread %d summation is %u",...);
  Msg("Thread %d summation is %u",...);

  // TO DO: lock your global mutex
  pthread_mutex_lock(&...);

  // TO DO: update the global sum
  summing up local sum and update the global sum

  // TO DO: unlock your global mutex
  pthread_mutex_unlock(&...);

  // TO DO: exit the thread
  pthread_exit(NULL);
}//end doit


// function main ----------------------------------------
int main(int argc,char *argv[]) {
  // TO DO: here go your locat variables
  long i;
  long *tindex;
  pthread_t *tid;

  //TO DO:  check args, argv if error, display message and terminate the program
  if (argc != 2) {
    msg("wrong number of command line arguments");
    msg_exit("usage - %s <number of threads>",argv[0]);
  }

  //TO DO:  set the number of threats to be dispatched
  no_of_threads = atoi(argv[1]);

  //TO DO:  check it is between 2 and 10 inclusive, if not error and terminate
  if (no_of_threads < 2 || no_of_threads > 10) {
    msg("wrong number of threads, must be 2 - 10");
    msg_exit("usage - %s <number of threads>",argv[0]);
  }

  create_log("assgn3.log");

  init_arr();

  //TO DO: determine no_of_items each thread is supposed to sum up
  //if the length of the array is divisible by the number of threads,
    if (the length of the array is divisible by the number of threads)
  //each thread will process the same number of items = length of the array / the number of threads
      no_of_items = ...;
  //if it is not divisible,
  //then the number of items is = 1+length of the array / the number of threads ,
  //and the last thread will process the leftover items (which will be slightly less);
    else
      no_of_items = ...;

  //TO DO: create dynamically array to hold the index of each dispatched thread
    tindex = (data type *)malloc(no_of_xxx*sizeof(data type));
    // display error if failed
    if (lead to a NULL)
      msg_exit("tindex allocation failed");

  //TO DO: create dynamically array to hold thread id of each dispatched thread
    tid =
    // display error if failed

  //TO DO: in a loop, dispatch each thread to execute doit() (see pthread_create())
  for (no_of_threads) {
      pthread_create(&tid, NULL, processfd, &fd)

      //TO DO: and display and log message "dispatched thread XXX with tid = YYY"
      msg("dispatched thread %d with tid = %ld",...);
      Msg("dispatched thread %d with tid = %ld",...);
    }

  //TO DO:  wait for all threads to complete
  for (no_of_threads)
    if (pthread_join(tid, NULL) != 0)
      sys_exit("no thread with tid = %u",...);

  //TO DO:  display message "Overall sum = XXX"
  msg("Overall sum = %u",...);

  //TO DO: sum up the array arr[]
  sum = 0;
  sum up the array arr[] in a for loop;

  //TO DO: and display the message "Check sum = XXX"
  msg("Check sum = %u",...);

  return 0;
}//end main
