#include <stdio.h>   // Include Standard IO Library
#include <stdlib.h>  // Include Standard Library
#include <pthread.h> // Include pthread Library

#define NUMBER_OF_THREADS 5 // Define number of (total) threads

// Initialize global variable counter
int counter = 0;

// Initialize MuTex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Thread function prototype
void *increment_counter(void *parameter);

int main(void) {

    // Declare thread array // Size is defined above
    pthread_t thread_id[NUMBER_OF_THREADS];

    // Array of strings that correspond to threads in 'pthread_t'
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
         *       - The 'pthread_t' object that corresponds to the
         *         newly created thread; this will be used to manage
         *         the thread. 
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
         * The 'pthread_create()' function returns an int upon comple- 
         *   tion. This value can be used for error checking/handling. 
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
    // finish/terminate
    for (int j = 0; j < NUMBER_OF_THREADS; j++) {
        pthread_join(thread_id[j], NULL);
        /*
         * The arguments for the 'pthread_join()' function are:
         *   thread_id[j]
         *      - The 'pthread_t' object corresponding to a thread. 
         *      - This object is used to reference, and manage the 
         *        thread (i.e. Suspend, Terminate, Etc). 
         *   NULL
         *      - Specifies that the threaded function does not return 
         *        anything, or any data. The return type of the
         *        threaded function is (basically) NULL.
         *      - However, the 'pthread_join()' function returns an
         *        int, which can be used for error checking/handling.
         *        This value is completely different from the return
         *        value of the threaded function.
         */
    }

    printf("\nFinal Counter = %d\n", counter);
    printf("Main Thread Has Completed\n\n");

    // Terminate main thread and return 0
    return 0;
}

/**
 * Thread function that increments a counter
 * 
 * This threaded function increments a global counter using a MuTex
 *   lock. The thread that executes this function must acquire the
 *   lock in order to access the global variable, aka critical 
 *   region. After `counter` has been incremented, the MuTex lock
 *   is released, and other threads can acquire it.
 * 
 * @param *parameter A pointer to a string that corresponds to the 
 *                   user-defined name of the thread.
 * @return NULL
 */
void *increment_counter(void *parameter) {

    // Re-cast parameter to character array (string)
    const char *name = (char *) parameter;
    printf("%s Has Started!\n", name);

    // Acquire MuTex lock
    pthread_mutex_lock(&mutex);
    
    // Increment global `counter` by 10,000
    for (int i = 0; i < 10000; i++) {

        counter++;

        /*
         * The entire critical section is this for loop, and every-
         *   thing inside the for loop
         * The operation `counter++` is not an atomic operation. It
         *   does NOT execute in a single instruction/step. There are 
         *   3 steps to `counter++`, and they are:
         *      1. Read from memory
         *      2. Increment counter by 1
         *      3. Write back to memory
         */
    }

    // Release MuTex lock
    pthread_mutex_unlock(&mutex);
    
    printf("%s Has Completed!\n", name);

    // Terminate thread
    // No data is returned
    pthread_exit(0);
}
