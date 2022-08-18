/**
 * Solves race condition via mutex
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//
pthread_mutex_t green_card = PTHREAD_MUTEX_INITIALIZER;

//; // declare mutex lock
// mut_ex => mutual exclusion

void * runner(void * param);

int counter = 0;

int main(int argc, char const *argv[]) {

    printf("(1) The value of counter is: %d\n", counter); // prints 0
    
    // Declare pthreads
    pthread_t jim;
    pthread_t bob;

    // Initialize mutex
    //pthread_mutex_init(&green_card, NULL);

    // Create threads
    pthread_create(&jim, NULL, runner, NULL);
    pthread_create(&bob, NULL, runner, NULL);

    // Wait for threads to finish
    pthread_join(jim, NULL);
    pthread_join(bob, NULL);

    printf("(3) The value of counter is: %d\n", counter); // prints 100000

    return 0;
}

void * runner (void * param) {

    // acquire the mutex lock
    pthread_mutex_lock(&green_card);

    // Increment counter by 50000
    for (int i = 0; i < 50000; i++) {
        counter++; // CRITICAL SECTION
    }

    printf("(2) The value of counter is: %d\n", counter); // prints 100000

    // release the mutex lock
    pthread_mutex_unlock(&green_card);

    // IF YOU DON'T RELEASE THE LOCK, YOU GET DEADLOCK

    pthread_exit(0);
}
