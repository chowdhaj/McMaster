#include <stdio.h>    // Standard IO Library
#include <stdlib.h>   // Standard library
#include <pthread.h>  // pthread Library

// Prototype for thread function
void * print_msg_function(void * ptr);

int main(void){

     // Declare pthread object 
     pthread_t thread1, thread2;

     // Create messages for threads
     char *message1 = "Thread 1";
     char *message2 = "Thread 2";

     // Declare int return values for threads
     int  iret1, iret2;

    /* 
     * Create two threads that will execute their own set of
     *   instructions, from a thread function
     * Threads are created using the 'pthread_create' function
     *  from the <pthread.h> library
     * Arguments in the 'pthread_create' function are:
     *   &thread1
     *       - Thread object that will correspond to the newly 
     *         created thread. This variable will be used to 
     *         reference the newly created thread
     *   NULL
     *       - Use default thread attributes. The thread's
     *         attributes can be changed if an argument is
     *         provided here
     *   print_msg_function
     *       - Thread function to execute once thread creation is 
     *         complete. This function will be executed on the 
     *         newly created thread. It's data is separate from
     *         other threads and processes.
     *   (void *) message1
     *       - Argument for the thread function 'print_msg_function'.
     *         This data gets passed to the function, similar to how
     *         the 1 and 2 in `./prog 1 2` gets passed to the main
     *         function in `prog`
     * Upon completion, 'pthread_create' returns an int. This can
     *   be used for error checking
     */
     iret1 = pthread_create(&thread1, NULL, print_msg_function, 
          (void *) message1);
     iret2 = pthread_create(&thread2, NULL, print_msg_function, 
          (void *) message2);

     /*
      * The main thread, or the parent thread, waits for the 
      *   completion of the children thread(s). If there is no
      *   'pthread_join()', then the parent thread may exit before
      *   the child thread, causing it to terminate, even though
      *   it has not completed
      *
      * Arguments in the 'pthread_join' function are:
      *   thread1
      *       - The thread object to synchronize with the parent
      *         thread. The parent thread will wait for 'thread1'
      *         to finish executing before terminating itself
      *   NULL
      *       - The threaded function that corresponds to 'thread1'
      *         does not return any data. The return type of
      *         'print_msg_function' is NULL. This is what the '0' in
      *         'pthread_exit(0)' means; nothing is returned. Alter-
      *         natively, the threaded function can return data (i.e.
      *         struct, string, etc).
      * 
      * Note: You could also write:
      *   int status = pthread_join(thread1, NULL);
      *   // This can be used for error checking
      */
     pthread_join(thread1, NULL);
     pthread_join(thread2, NULL); 

     // Print out the exit code from 'pthread_create' of each thread
     printf("Thread 1 returns: %d\n", iret1);
     printf("Thread 2 returns: %d\n", iret2);

     // Terminate main thread and return 0
     return 0;
}

/**
 * Thread function that prints a message to the terminal
 * 
 * This function is used by threads to print a custom message to
 *   the terminal. The custom message is in the argument of the
 *   thread function.
 * 
 * @param (void * ptr) Void pointer to the character array object
 * @return NULL
 */
void * print_msg_function(void * ptr) {
     char * message;
     message = (char *) ptr;
     printf("%s \n", message);
     pthread_exit(0);
}

/*
 * C Compiler: cc pthread1.c -o pthread1 -lpthread
 *   OR
 * C++ Compiler: g++ -lpthread pthread1.c
 *
 * Execute: ./pthread1
 * Results: 
 *   Thread 1
 *   Thread 2
 *   Thread 1 returns: 0
 *   Thread 2 returns: 0
 */
