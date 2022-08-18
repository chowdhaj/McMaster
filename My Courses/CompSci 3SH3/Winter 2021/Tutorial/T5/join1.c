#include <stdlib.h>  // Include Standard C Library
#include <stdio.h>   // Include Standard IO Library
#include <pthread.h> // Include pthread Library

// Define number of threads to be used in the process
#define NUMBER_OF_THREADS 10 

// Global variable declaration and initialization
int counter = 0;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

// Prototype for thread function
void *increment_counter(void *);

int main(void) {

    // Declare pthread array that will store pthread objects
    pthread_t thread_id[NUMBER_OF_THREADS];
    int i = 0;

    // Loop through size of the pthread array and create threads
    for (i = 0; i < NUMBER_OF_THREADS; i++) {
        pthread_create(&thread_id[i], NULL, 
                       increment_counter, NULL);
        /*
         * The 'pthread_create()' function creates the thread
         *   objects corresponding to the index in the array
         * Arguments for the 'pthread_create()' function are:
         *   &thread[i]
         *      - The thread object that corresponds to the 
         *        newly created thread object. The thread object
         *        is stored in an array, and can be accessed by
         *        thread[i], where `i` is the index of the
         *        thread object.
         *   NULL
         *      - Attributes of the thread.
         *      - In this case, default attributes are used.
         *   increment_counter
         *      - The function that is executed by the thread.
         *   NULL
         *      - The parameters supplied to the function above
         *      - In this case, no parameters are given to the
         *        function upon thread creation.
         */
    }

    /* Loop through the pthread array, and wait for each thread
     *   to finish by calling the 'pthread_join()' on it.
     *
     * In the 'pthread_join()' function, the arguments are:
     *   thread_id[i]
     *      - The thread object in the array at the `i` index
     *      - Each element in the 'thread_id' array corresponds
     *        to a thread object.
     *   NULL
     *      - The return value of the threaded function
     *      - In this case, the return value is NULL. In other words,
     *        there is no return value.
     *
     * Note: The 'pthread_join()' function does return an int upon
     *       completion, and this value can be used for error check-
     *       ing/handling. If '0' is returned, then 'pthread_join()'
     *       finished with no errors.
     */

    for (i = 0; i < NUMBER_OF_THREADS; i++) {
       pthread_join(thread_id[i], NULL); 
    }

    // Prints the final value of the counter
    printf("Final Counter Value: %d\n", counter);

    // Terminate main thread, and return 0 as exit code
    return 0;
}

/**
 * Thread function that increments a global counter
 * 
 * This threaded function increments a global counter (an int) using a 
 *   MuTex. Threads that execute this function must acquire the MuTex 
 *   lock before being able to access the critical section.
 * When this function is executed, the ID of the thread is printed to 
 *   the terminal, it tries to acquire the MuTex lock, and if it is 
 *   successful, it increments `counter`, releases the MuTex lock, and 
 *   terminates by returning 0. In the case that the thread is unable
 *   to acquire the MuTex lock, it will wait for it.
 *
 * @param dummy_pointer A dummy pointer that holds no
 *                      significance or information.
 * @return NULL
 */
void * increment_counter(void * dummy_pointer) {

    /* 
     * 'pthread_self()' returns the thread's ID, which is a (unsigned) 
     *    long integer
     * Each thread has a unique number/ID
     */
    printf("Thread ID: %li\n", (long)pthread_self());

    // Acquire MuTex lock
    pthread_mutex_lock(&mutex1);
    
    counter++;

    // Release MuTex lock
    pthread_mutex_unlock(&mutex1);

    // Terminate thread // Return NULL (nothing)
    pthread_exit(0);

    // Note: Not releasing the MuTex lock results in deadlock
}

/*
 * C Compiler: cc join1.c -o join1 -lpthread
 *
 * Execute: ./join1
 * Results: 
 *    Thread ID: 123145499824128
 *    Thread ID: 123145501970432
 *    Thread ID: 123145500360704
 *    Thread ID: 123145503043584
 *    Thread ID: 123145503580160
 *    Thread ID: 123145504116736
 *    Thread ID: 123145502507008
 *    Thread ID: 123145504653312
 *    Thread ID: 123145501433856
 *    Thread ID: 123145500897280
 *    Final Counter Value: 10
 */
