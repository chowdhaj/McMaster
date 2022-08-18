#include <stdio.h>    // Include Standard IO Library
#include <stdlib.h>   // Include Standard C Library
#include <pthread.h>  // Include pthread Library

#define COUNT_DONE  10 // Define max count of 10
#define COUNT_HALT1 3  // Define count halt of 3
#define COUNT_HALT2 6  // Define count halt of 6
#define TRUE        1  // Define true boolean

// Global variables
int counter = 0;

// Initialize MuTexes and condition
pthread_mutex_t count_mutex     = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  condition_cond  = PTHREAD_COND_INITIALIZER;

// Prototypes for thread functions
void * functionCount1();
void * functionCount2();

int main(void) {

    // Thread declaration
    pthread_t thread1, thread2;

    // Create and execute threads
    pthread_create(&thread1, NULL, &functionCount1, NULL);
    pthread_create(&thread2, NULL, &functionCount2, NULL);

    /*
     * The 'pthread_create()' function creates a thread, and executes 
     *   the designated function via the newly created thread
     * The arguments of the 'pthread_create()' function are:
     *   &thread1 (OR) &thread2
     *      - The thread object that is used to reference the newly 
     *        created thread
     *   NULL
     *      - The attributes of the thread
     *      - In this case, default attributes are used
     *   &functionCount1 (OR) &functionCount2
     *      - The function the thread must execute
     *   NULL
     *      - Arguments to the function above
     *      - In this case, neither functions take any argument
     */

    // Let threads finish executing before proceeding
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    /* 
     * The 'pthread_join()' function allows the corresponding thread
     *   to finish before proceeding with the next set of instructions
     *
     * The arguments of the 'pthread_join()' function are:
     *   &thread1 (OR) &thread2
     *      - The thread object to wait for
     *   NULL
     *      - Return type and value of the corresponding thread
     *      - In this case, the return type of the threaded function
     *        is NULL (nothing)
     *
     * The 'pthread_join()' function returns an int that represents
     *   whether it was successful or not. This value can be used for
     *   error checking/handling.
     * i.e.
     *    int status = pthread_join(thread1, NULL);
     *    if (status) { // check } 
     */

    // Terminate main thread and return 0
    return 0;
}

/**
 * Thread function that increments a counter based on a MuTeX
 *   condition.
 *
 * This threaded function increments a global counter based on a
 *   MuTex condition. If the counter is greater than or equal to
 *   'COUNT_HALT1', AND less than or equal to 'COUNT_HALT2', then
 *   signal the thread to wait. The waiting is enclosed in a wait
 *   condition MuTex. Once the wait has completed, the MuTex lock is 
 *   released, and another MuTex lock is acquired. Now, the function 
 *   increments the global counter, prints its value and then releases 
 *   the lock. Finally, it checks if the counter has reached its 
 *   specified maximum. If so, return to the calling function, and the 
 *   thread is exited. If not, the entire routine is looped until the 
 *   condition is satisfied.
 * The function does not accept parameters, and it does not
 *   return data.
 * 
 * @return NULL
 */
void *functionCount1() {

    // Start infinite loop
    while (TRUE) {

        // Acquire MuTex condition lock
        pthread_mutex_lock(&condition_mutex);

        // While this statement is true
        while (counter >= COUNT_HALT1 
            && counter <= COUNT_HALT2) {
            // Make the thread wait
            pthread_cond_wait(&condition_cond, 
                              &condition_mutex);
        }

        // Release MuTex condition lock
        pthread_mutex_unlock(&condition_mutex);

        // Acquire MuTex increment lock
        pthread_mutex_lock(&count_mutex);

        counter++;
        printf("Inside functionCount1 | Counter Value = %d\n", 
               counter);

        // Release MuTex increment lock
        pthread_mutex_unlock(&count_mutex);

        // If counter has exceeded or met the goal
        if (counter >= COUNT_DONE) { 
            // Return to caller
            return(NULL);
        }
    }
    // Terminate the thread, and return NULL (nothing)
    pthread_exit(0);
    // This line will never be reached, under normal situations
}

/**
 * Thread function that increments a counter based on a MuTeX
 *   condition.
 *
 * This threaded function increments a global counter based on a
 *   MuTex condition. If the counter is less than 'COUNT_HALT1' OR
 *   greater than 'COUNT_HALT2', then signal the thread to wait. Once 
 *   the wait has completed, the MuTex lock is released, and the
 *   thread acquires the 'increment MuTex lock'. Now, the function 
 *   increments the global counter, prints its value and then releases 
 *   the lock. Finally, it checks if the counter has reached its 
 *   specified maximum. If so, return to the calling function, and the
 *   thread is exited. If not, the entire routine is looped until the 
 *   condition is met.
 * The function does not accept parameters, and it does not
 *   return data.
 * 
 * @return NULL
 */
void *functionCount2() {
    
    // Start infinite loop
    while (TRUE) {
       
        // Acquire conditional lock
        pthread_mutex_lock(&condition_mutex);

        // If this condition is satisfied
        if (counter < COUNT_HALT1 || counter > COUNT_HALT2) {
            // Signal the thread to wait
            pthread_cond_signal(&condition_cond);
        }

        // Release conditional lock
        pthread_mutex_unlock(&condition_mutex);

        // Acquire lock to increment counter
        pthread_mutex_lock(&count_mutex);

        counter++;
        printf("Inside functionCount2 | Counter Value = %d\n", 
               counter);

        // Release lock
        pthread_mutex_unlock(&count_mutex);

        // If counter has reached maximum
        if (counter >= COUNT_DONE) {
            // Exit and return to caller
            return(NULL);
        }
    }
    // Terminate thread and return NULL (nothing)
    pthread_exit(0);
    // Under normal circumstances, this will never be reached
}

/*
 * C Compiler: cc cond1.c -o cond1 -lpthread
 *
 * Execute: ./cond1
 * Results: 
 *    Inside functionCount1 | Counter Value = 1
 *    Inside functionCount1 | Counter Value = 2
 *    Inside functionCount1 | Counter Value = 3
 *    Inside functionCount2 | Counter Value = 4
 *    Inside functionCount2 | Counter Value = 5
 *    Inside functionCount2 | Counter Value = 6
 *    Inside functionCount2 | Counter Value = 7
 *    Inside functionCount2 | Counter Value = 8
 *    Inside functionCount2 | Counter Value = 9
 *    Inside functionCount2 | Counter Value = 10
 *    Inside functionCount1 | Counter Value = 11
 * 
 *    Inside functionCount2 | Counter Value = 1
 *    Inside functionCount2 | Counter Value = 2
 *    Inside functionCount2 | Counter Value = 3
 *    Inside functionCount2 | Counter Value = 4
 *    Inside functionCount2 | Counter Value = 5
 *    Inside functionCount2 | Counter Value = 6
 *    Inside functionCount2 | Counter Value = 7
 *    Inside functionCount2 | Counter Value = 8
 *    Inside functionCount2 | Counter Value = 9
 *    Inside functionCount2 | Counter Value = 10
 *    Inside functionCount1 | Counter Value = 11
 */
