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

unsigned  long sum = 0.0, arr[ARRAYSIZE];
pthread_mutex_t sum_mutex = PTHREAD_MUTEX_INITIALIZER;

void init_arr() {
  srand(time(NULL));
  long i;
  for(i = 0; i < ARRAYSIZE; i++) {
    arr[i] = (long) (rand() % 10);
  }
}


// function doit ----------------------------------------
void* doit(void *params) {
  long i, from, to;
  long mysum = 0;
  long tindex = *((long *) params);

  // find your slice
  from = tindex * no_of_items;
  to = from + no_of_items-1;
  if (to > ARRAYSIZE-1)
    to = ARRAYSIZE-1;
  msg("Thread %d processing the array from %d to %d",
      tindex,from,to); 
  Msg("Thread %d processing the array from %d to %d",
      tindex,from,to); 
  for(i = from; i <= to; i++)
    mysum = mysum + arr[i];

  msg("Thread %d summation is %u",tindex,mysum);
  Msg("Thread %d summation is %u",tindex,mysum);
  
  pthread_mutex_lock(&sum_mutex);   // lock the mutex 
  sum = sum + mysum;                // update the global sum
  pthread_mutex_unlock(&sum_mutex); // unlock the mutex 
  pthread_exit(NULL);
}//end doit


// function main ----------------------------------------
int main(int argc,char *argv[]) {
  long i;
  long *tindex;
  pthread_t *tid;

  if (argc != 2) {
    msg("wrong number of command line arguments");
    msg_exit("usage - %s <number of threads>",argv[0]);
  }
  
  no_of_threads = atoi(argv[1]);
  if (no_of_threads < 2 || no_of_threads > 10) {
    msg("wrong number of threads, must be 2 - 10");
    msg_exit("usage - %s <number of threads>",argv[0]);
  }

  create_log("assgn3.log");

  init_arr();

  if ((ARRAYSIZE % no_of_threads) == 0)
    no_of_items = ARRAYSIZE / no_of_threads;
  else
    no_of_items = 1+(ARRAYSIZE / no_of_threads);

  tindex = (long *)malloc(no_of_threads*sizeof(long));
  if (tindex == NULL)
    msg_exit("tindex allocation failed");
  tid = (pthread_t *)malloc(no_of_threads*sizeof(pthread_t));
  if (tid == NULL)
    msg_exit("threads allocation failed");

  for (i = 0; i < no_of_threads; i++) {
    tindex[i]=i;
    pthread_create(&tid[i],NULL,doit,(void *)&tindex[i]);
    msg("dispatched thread %d with tid = %ld",tindex[i],tid[i]);
    Msg("dispatched thread %d with tid = %ld",tindex[i],tid[i]);
  }

  // wait for all threads to complete
  for (i = 0; i < no_of_threads; i++) 
    if (pthread_join(tid[i],NULL) != 0)
      sys_exit("no thread with tid = %u",tid[i]);

  msg("Overall sum = %u",sum); // display the overall sum

  sum = 0;
  for(i = 0; i < ARRAYSIZE; i++) { 
    sum = sum + arr[i]; 
  }
  msg("Check sum = %u",sum);

  return 0;
}//end main
