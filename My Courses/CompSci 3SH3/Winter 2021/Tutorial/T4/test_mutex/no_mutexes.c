#include <stdio.h>   // Include Standard IO Library
#include <stdlib.h>  // Include Standard Library
#include <pthread.h> // Include pthread Library
#include <stdint.h>  // Include Additional Integer Types

#define NUMBER_OF_THREADS 5 // Define number of (total) threads

// Thread function prototype
void *increment_counter(void *parameter);

int main(void) {

    // Declare thread array // Size is defined above
    pthread_t thread_id[NUMBER_OF_THREADS];

    // Array of strings that will correspond to newly created threads
    char *threadName[NUMBER_OF_THREADS] = {
        "Thread 1_Alpha", "Thread 2_Bravo", "Thread 3_Charlie", 
        "Thread 4_Delta", "Thread 5_Echo" 
    };

    /*
     * Declare void counter; this will be used to store return values
     *   from threads once their execution is complete.
     * The type of the variable is void because threaded functions can
     *   only return void variables, and the programmer must (re)cast
     *   them to to appropriate type. Furthermore, threaded functions
     *   can only accept one argument that is also of type void.
     */
    void *get_thread_counter;

    // Initialize ints
    int sum_counter = 0;
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

    // Loop through the 'pthread_t' array, manage each thread, and
    // the data returned (from each thread)
    for (int i = 0; i < NUMBER_OF_THREADS; i++) {
        pthread_join(thread_id[i], &get_thread_counter);
        /*
         * The arguments for the 'pthread_join()' function are:
         *   thread_id[i]
         *      - The 'pthread_t' object corresponding to a thread in 
         *        the 'pthread_t' array. This object is used to 
         *        reference the thread, which allows us to manage it 
         *        (i.e. Suspend, Terminate, Etc).
         *   &get_thread_counter
         *      - The return value of the threaded function is stored
         *        in this variable. It is a pointer to a memory ad-
         *        dress. The type of the variable is void, and must be 
         *        casted to the correct data type.
         * 
         * Note: The 'pthread_join()' function does return an int, and
         *       this can be used for error checking/handling. It al-
         *       ways returns an int which represents the exit code. 
         *       This return value is completely different from 
         *       '&get_thread_counter'.
         */

        // Cast thread counter to int, and add it to 'sum_counter'
        sum_counter += (int) get_thread_counter;
        printf("%s Has Terminated\n", threadName[i]);
    }

    printf("\nFinal Counter = %d\n", sum_counter);
    printf("Main Thread Has Completed\n\n");

    // Terminate main thread and return 0
    return 0;
}

/**
 * Thread function that increments a local counter, and returns it
 *
 * This threaded function increments a local counter to 10.000, and 
 *   returns it to the caller. Since the counter is local to each 
 *   thread, mutexes are not required because each thread is accessing 
 *   its own data, and not sharing global data. The final value of the 
 *   counter is returned when the function terminates.
 * This is an example of a thread-safe function.
 *
 * @param *parameter A pointer to a string that corresponds to the 
 *                   user-defined name of the thread.
 * @return counter The thread's local (private) counter
 */
void *increment_counter(void *parameter) {

    // Re-cast parameter to character array (string)
    const char *name = (char *) parameter;
    printf("%s Has Started!\n", name);
    
    /*
     * The type of the counter is an unsigned integer that is capable
     *   of storing a data pointer.
     * This type is used because it holds the same amount of infor-
     *   mation as a pointer. Thus, when we cast from to 'void', we 
     *   can be sure that information is not lost.
     */
    uintptr_t counter = 0;

    // Increment local `counter` to 10,000
    for (int i = 0; i < 10000; i++) {
        counter++;
    }
    
    printf("%s Has Completed!\n", name);

    // Terminate thread and return `counter`
    pthread_exit((void *) counter);
}
