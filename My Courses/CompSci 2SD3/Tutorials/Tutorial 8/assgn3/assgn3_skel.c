/**
 * Skeleton file for assignment #3. Fill in all TODOs using the
 * description on the course website as a reference. The STEPS in
 * this file correspond to the description on the course website.
 * 
 * @author Dr. Franek
 * @author YOUR_NAME
 * @course CompSci 2SD3
 * @date March 22nd, 2022
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "log.h"

// -------------------- DO NOT TOUCH THIS -------------------- //
int logindex = 0;
int *logi = &logindex;
// mutex for logging functions required for thread-safe code
pthread_mutex_t tlock = PTHREAD_MUTEX_INITIALIZER;
// -------------------- DO NOT TOUCH THIS -------------------- //

#define ARRAYSIZE 1000000

int no_of_threads = 0;
int no_of_items = 0;

void init_arr();
void * doit(void * params);

// TODO : Declare your global variables here
//          1. Something to store the final sum
//          2. An array to store the values
// HINT : Both need to be of type 'unsigned long'

// TODO : Declare and initialize a (global) mutex here
//        (i.e. pthread_mutex_t ??? = ???;)

/**
 * Main function
 * 
 * What does it do ???
 * 
 * @param argc ???
 * @param argv ???
 * @return ???
 */
int main(int argc, char * argv[]) {

    // TODO : Declare local variables
    //int i;
    //for (i = 0,)

    // STEP 3 : Check the number of command line arguments and if it
    //          is not 2, then an error message and usage information
    //          is printed and program terminates.
    //          (i.e. usage - ./assgn3 <number of threads>)
    // TIP    : Use ``msg()`` and then ``msg_exit()``.

    // STEP 4 : Store the 1st argument (from the command line), which
    //          is <number of threads>. This argument determines the
    //          number of threads the program will use and store in a
    //          variable (defined above).

    // STEP 5 : Check if the number of threads is in the range
    //          [2..10]. If not, an error message and the usage are
    //          displayed and the program terminates.
    // TIP    : Use ``msg()`` and then ``msg_exit()``.

    // QUESTION : What is the difference between ``msg()`` and
    //            ``Msg()``?
    // Msg = log
    // msg = stdout (terminal)

    create_log("assgn3.log");

    // STEP 6 : Then the program initializes the global long array
    //          named arr with random values in the range [0..10]
    //          using the function ``init_arr()``.
    init_arr();

    // STEP 7 : The program determines how many items of the array
    //          ``arr[]`` each of the threads should process.
    /*
        if ((SIZE_OF_ARRAY % NUMBER_OF_THREADS) == 0) {
            // number of items = length of array / number of threads
        } else {
            // number of items = 1 + length of array / number of threads
        }
     */
    // QUESTION : What is the significance of STEP 7?
    // HINT     : Think of distribution, work load.

    // TODO : Create a dynamically allocated array called ``tindex``
    //        to hold the INDEX of each dispatched thread. This is
    //        part of STEP 9.
    // HINT : You will have to use ``malloc()`` and ``sizeof()``
    malloc(... sizeof(long))

    // TODO : Create a dynamically allocated array called ``tid``
    //        to hold the THREAD ID of each dispatched thread. This is
    //        part of STEP 9.
    // HINT : You will have to use ``malloc()`` and ``sizeof()``
    //no_of_threads * malloc(...sizeof(pthread_t))

    // QUESTION : When using ``malloc()`` what check do you need to
    //            perform?
    // HINT : What if ``malloc()`` failed? And no memory was allocated

    //if (tindex == NULL) {return;}

    // TODO : Using a for-loop, iterate from 0 to the number of
    //        threads, and create a thread on each iteration. The
    //        newly created thread will execute the ``doit()``
    //        threaded function. Inside the for-loop use ``msg()`` and
    //        ``Msg()`` to print the following:
    //        "dispatched thread XXX with tid = YYY"
    // HINT : pthread_create(thread_id, NULL, doit, thread_index);
    for (???) {
        pthread_create
        msg
        Msg
    }

    // TODO : Wait for all threads to complete (i.e. pthread_join();)

    // TODO : Using ``msg()``, display message: "Overall sum = XXX"
    // sum

    // TODO : Sum up the array ``arr[]``
    // TODO : Using ``msg()``, display the message: "Check sum = XXX"
    
    return 0;
}

/**
 * ???
 */
void init_arr() {
    srand(time(NULL));
    long i;
    for(i = 0; i < ARRAYSIZE; i++) {
      arr[i] = (long) (rand() % 10);
    }
}

/**
 * Thread function ... ???
 */
void * doit(void * params) {

    // STEP 8 : The processing of a thread is coded in this threaded
    //          function, ``doit()``. It consists of summing up the
    //          number of items of the global array arr[] and adding
    //          it to a global variable, so when all the threads are
    //          finished, the whole array had been summed up.

    // TODO : Declare local variables
    localsum = 0;

    // TODO : From the argument (i.e. ``params``), get the thread
    //        index (i.e. ``tindex``)

    // TODO : Find the 'slice' of the array; ``from`` and ``to``. This
    //        is related to STEP 9.
    // HINT : ``from`` and ``to`` are variables that must be declared
    //        locally.
    // HINT : Make sure that ``to`` is not bigger than ``ARRAYSIZE-1``
    //        If it is, then make ``to`` equal to ``ARRAYSIZE-1``.

    // TODO : Using ``msg()`` and ``Msg()``, print to standard output
    //        and the log file, respectively, which part of the array
    //        the current (executing) thread is processing.

    // TODO : Using a for-loop, sum up the portion of the array
    //        ``arr[]`` that the current (executing) thread has
    //        processed.
    // HINT : This is done locally and no global variable is involved.

    // TODO : Using ``msg()`` and ``Msg()``, print to standard output
    //        and the log file, respectively, which part of the array
    //        the current (executing) thread is processing.

    // TODO : Acquire the (global) mutex lock
    // TODO : Update global sum by adding local sum to it
    sum += localsum;
    // TODO : Release the (global) mutex lock
    // TODO : Exit thread (i.e. ``pthread_exit(???);``)
}
