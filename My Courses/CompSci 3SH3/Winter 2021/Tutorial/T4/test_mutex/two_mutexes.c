#include <stdio.h>   // Include Standard IO Library
#include <stdlib.h>  // Include Standard Library
#include <pthread.h> // Include pthread Library

#define NUMBER_OF_THREADS 5 // Define number of (total) threads
#define TRUE 1              // Define the bool true

// Initialize global variable counter
int counter_1 = 0;
int counter_2 = 0;

// Initialize MuTex
pthread_mutex_t mutex_counter_1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_counter_2 = PTHREAD_MUTEX_INITIALIZER;

// Prototype for helper functions
int add_ints(int val1, int val2);

// Prototype for thread function
void *increment_counter(void *parameter);

int main(void) {

    // Declare thread array // Size is defined above
    pthread_t thread_id[NUMBER_OF_THREADS];

    // Array of strings that correspond to threads in 'thread_id'
    char *threadName[NUMBER_OF_THREADS] = {
        "Thread 1_Alpha", "Thread 2_Bravo", "Thread 3_Charlie", 
        "Thread 4_Delta", "Thread 5_Echo" 
    };

    int ret = -1;
    printf("\n");

    /* Loop through size of thread array, and create a thread for each
     *   index in the array using the 'pthread_create()' function.
     * For each 'pthread_t' object in the array, check the return
     *   value of 'pthread_create()' to ensure it did not fail. If it 
     *   did fail, then terminate the program and return -1.
     */
    for (int i = 0; i < NUMBER_OF_THREADS; i++) {
        ret = pthread_create(&thread_id[i], NULL, 
            increment_counter, threadName[i]);
        /*
         * The arguments for the 'pthread_create()' function are:
         *   &thread_id[i]
         *       - The 'pthread_t' object that corresponds to the new-
         *         ly created thread; this will be used to reference
         *         and manage the thread (i.e. suspend, terminate, 
         *         etc.)
         *   NULL
         *       - Sets the attributes of the thread.
         *       - In this case, default attributes are used because 
         *         NULL is the argument.
         *   increment_counter
         *       - The threaded function that the newly created thread
         *         will execute.
         *   threadName[i] 
         *       - The argument passed to the threaded function, 
         *         'increment_counter'.
         *       - In this case, this argument is a string, also known
         *         as character array.
         * 
         * The 'pthread_create()' function returns an int upon finsh-
         *   ing. This value can be used for error checking/handling. 
         *   It is checked below using an if-statement.
         */

        // Check (int) return value of 'pthread_create()'
        if (ret != 0) {
            // If thread creation failed then print error to 'stderr'
            fprintf(stderr, "Failed To Create Thread #%d\n", i);
            return -1; // Terminate main thread
        }
    }

    // Loop through 'pthread_t' array, and wait for each thread to
    // finish executing
    for (int j = 0; j < NUMBER_OF_THREADS; j++) {
        pthread_join(thread_id[j], NULL);
        /*
         * The arguments for the 'pthread_join()' function are:
         *   thread_id[j]
         *      - The 'pthread_t' object corresponding to a thread. 
         *      - This object is used to reference the thread.
         *   NULL
         *      - Specifies that the threaded funcion does not return 
         *        any information. Hence, the return value is NULL.
         *      - However, the 'pthread_join()' function returns an
         *        int, which can be used for error checking/handling.
         */
    }

    printf("\nFinal Counter = %d\n", 
        add_ints(counter_1, counter_2));
    printf("Main Thread Has Completed\n\n");

    // Terminate main thread and return 0
    return 0;
}

/**
 * Thread function that increments two counters
 * 
 * This threaded function increments two global counters using two
 *   mutexes wrapped in an infinite while loop. The threads will
 *   try to acquire one of two locks, increment the counter that
 *   correponds to the lock, and then break out of the loop. Since
 *   there are two mutexes, a thread will try to acquire the 1st
 *   mutex lock, and if it is unsuccessful, it will try to acquire
 *   the 2nd mutex lock. If both attempts are unsuccessful, it will
 *   loop back to the beginning, and keep trying until it can acquire
 *   a mutex lock.
 * 
 * @param *parameter A pointer to a string that corresponds to the 
 *                   user-defined name of the thread.
 * @return NULL
 */
void *increment_counter(void *parameter) {

    // Re-cast parameter to character array (string)
    const char *name = (char *) parameter;
    printf("%s Has Started!\n", name);

    while (TRUE) {
        // Try to acquire mutex lock #1
        if (pthread_mutex_trylock(&mutex_counter_1) == 0) {
            //pthread_mutex_lock(&mutex_counter_1); // Deadlock
            printf("%s Has Lock #1\n", name);
            for (int i = 0; i < 10000; i++) {
                counter_1++;
            }
            // Release mutex lock #1
            pthread_mutex_unlock(&mutex_counter_1);
            break;
        } 
        else {
            // Try to acquire mutex lock #2
            if (pthread_mutex_trylock(&mutex_counter_2) == 0) {
                //pthread_mutex_lock(&mutex_counter_2); // Deadlock
                printf("%s Has Lock #2\n", name);
                for (int i = 0; i < 10000; i++) {
                    counter_2++;
                }
                // Release mutex lock #2
                pthread_mutex_unlock(&mutex_counter_2);
                break;
            }
        }
        /* 
         * If a thread was unable to acquire either lock, it will 
         *   loop back to the beginning of the while loop.
         * Once a thread finishes incrementing a counter, it will
         *   release the lock it holds, break out of the while loop, 
         *   and terminate.
         */
    }
        
    printf("%s Has Completed!\n", name);

    // Terminate thread, and return NULL (nothing)
    pthread_exit(0);
}

/*
 * Adds two integers, and returns the sum
 *
 * @param val1 The first integer parameter
 * @param val2 The second integer parameter
 * @return The sum of the integers
 */
int add_ints(int val1, int val2) {
    return (val1 + val2);
}

/*
 * Q/A By Chen
 *
 * Q: How to stall threads without using a while loop, and make sure
 *    that they check each MuTex's status? All of this needs to be
 *    accomplished while maintaining an even distribution of load
 * A: This is not possible to do with a While Loop. This is because
 *    the 'pthread_mutex_trylock' function does not block the thread
 *    when the lock is not available. Only 'pthread_mutex_lock' does
 *    blocking. Thus, when using 'pthread_mutex_trylock' on multiple
 *    threads, you need to use a While Loop and continuously iterate
 *    over them, try to acquire their lock, and perform the correspon-
 *    ding set of instructions.
 * 
 * Q: Why does 'pthread_mutex_lock' cause deadlock after you use
 *    'pthread_mutex_trylock'? It also causes deadlock if you use it
 *    a second time.
 * A: The 'pthread_mutex_lock' function does NOT check if the thread
 *    that is trying to acquire the lock already has the lock. Thus,
 *    if a thread already has a lock, and it tries to get the lock for
 *    a second time, it will be blocked because the lock is already in
 *    use by a thread.
 * 
 * Q: Using 'pthread_mutex_trylock' as a 'pthread_mutex_lock', can 
 *    cause deadlock or other strange behavior. Why?
 * A: The 'pthread_mutex_trylock' function does NOT block. It tries to
 *    get the lock, and if it fails to acquire the lock, it will NOT
 *    block the thread from progressing. Instead, the thread will be
 *    allowed to execute the next set of instructions, and if the
 *    next set of instructions do not contain an attempt to retry the
 *    lock, then the thread won't execute instruction(s) in the 
 *    critical region (i.e. Increment counter)
 */