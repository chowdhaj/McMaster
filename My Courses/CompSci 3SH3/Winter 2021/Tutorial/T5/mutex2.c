#include <stdio.h>    // Standard IO Library
#include <stdlib.h>   // Standard C Library
#include <pthread.h>  // pthread Library

// Global counter for threads
int counter = 0;

// Mutual exclusion lock for critical regions
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

// Prototype for thread function
void * increment_counter();

int main(void) {

    // Declare ints; these will store return values
    int thread_status1, thread_status2;

    // Declare thread objects; used for referencing the thread
    pthread_t thread1, thread2;

    /* 
     * Creates a thread, stores the return value, and checks it to 
     *   determine if thread creation failed or succeeded
     * 
     * The 'pthread_create()' function in the 'pthread' library is 
     *   used to create the threads below
     * Arguments in the 'pthread_create()' function are:
     *   &thread1
     *       - The thread object assigned to the newly created thread
     *   NULL
     *       - Default attributes are applied to the thread
     *       - Custom attributes can be specified in a struct, and a 
     *         pointer to the struct is passed instead
     *   &increment_counter
     *       - The function that the thread will execute
     *   NULL
     *       - The parameter supplied to the function
     *       - In this case, no parameter is given
     * 
     * Since 'pthread_create()' returns an int, this value is stored 
     *   in 'thread_status1', and then an if-statement is used to 
     *   check the value of the returned int. If it is anything other 
     *   than 0 (i.e. Failed/Error), then an error message is printed 
     *   to the terminal.
     */ 
    if ((thread_status1 = pthread_create(&thread1, NULL, 
                                        &increment_counter, NULL))) {
        printf("%s\n%s%d\n", 
            "ERROR: Thread Creation Failed",
            "Exit Code = ",
            thread_status1);
    }

    if ((thread_status2 = pthread_create(&thread2, NULL, 
                                        &increment_counter, NULL))) {
        printf("%s\n%s%d\n", 
            "ERROR: Thread Creation Failed",
            "Exit Code = ",
            thread_status2);
    }

    /* 
     * The 'pthread_join()' function waits till the thread is
     *   completed before allowing the main function to continue.
     *   If the main function is allowed to terminate without waiting,
     *   then the child thread(s) will also terminate regardless of 
     *   whether or not they have completed.
     *
     * Arguments in the 'pthread_join()' function are:
     *   thread1 (OR) thread2
     *       - The thread object to wait for
     *       - Allows 'thread1' to finish executing before the parent 
     *         thread is allowed to terminate
     *   NULL
     *       - Specifies the return type of the threaded function
     *       - Default return type is NULL (nothing), but this can be
     *         changed to any data type (i.e. struct, strings,
     *         etc.)
     *       - Note: This has nothing to do with the return value of
     *               'pthread_join()'. This is purely for the thread-
     *               ed function that 'thread1' executes
     * 
     * The 'pthread_join()' function returns an int, which indicates 
     *   its success/status. This value can be used for checking/han-
     *   dling errors.
     */
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL); 

    // Terminate main process/function, and return 0
    return 0;
}

/**
 * Thread function that increments a global counter.
 * 
 * This function increments a global counter using a MuTex. Only one 
 *   thread can increment/write to the `counter` variable at a time; 
 *   it has exclusive rights to `counter`. After the value is incre-
 *   mented, it is printed to the terminal, the MuTex lock is released 
 *   and the thread terminates. Upon termination, it returns NULL 
 *   (nothing).
 *
 * @return NULL
 */
void * increment_counter() {

    // Acquire MuTex lock
    pthread_mutex_lock(&mutex1);
    
    counter++;
    printf("Counter value: %d\n", counter);

    // Release MuTex lock
    pthread_mutex_unlock(&mutex1);

    // Terminate thread // Return NULL (nothing)
    pthread_exit(0);

    // Note: Not releasing the MuTex lock will result in deadlock
}

/*
 * C Compiler: cc mutex2.c -o mutex2 -lpthread
 *
 * Execute: ./mutex2
 * Results: 
 *    Counter value: 1
 *    Counter value: 2
 */
