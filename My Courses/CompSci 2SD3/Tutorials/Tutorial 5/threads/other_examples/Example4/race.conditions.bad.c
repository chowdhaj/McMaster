/**
 * Demonstrates why race conditions are nasty bugs due to their
 * inherent nature of randomly showing up.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define START_VALUE 25
#define MAXIMUM     1000
#define MINIMUM     990

pthread_mutex_t lock1;
pthread_mutex_t lock2;

void * agent_a (void * param);
void * agent_b (void * param);

int counter = START_VALUE;

int main(int argc, char const *argv[]) {

    printf("The value of counter is: %d\n", counter); // PRINT 25

    // Declare threads
    pthread_t thread_increment, thread_decrement;

    // Initialize mutex
    pthread_mutex_init(&lock1, NULL);
    pthread_mutex_init(&lock2, NULL);

    // Create first thread and execute increment function
    pthread_create(&thread_increment, NULL, agent_a, NULL);

    // Create second thread and execute decrement function
    pthread_create(&thread_decrement, NULL, agent_b, NULL);

    // Wait for both threads to finish
    pthread_join(thread_increment, NULL);
    pthread_join(thread_decrement, NULL);

    // Print final value; should be 10 greater than
    printf("The value of counter is: %d\n", counter); // PRINT 35

    // QUESTION: How many threads are present in total?

    return 0;
}

void * agent_a(void * param) {

    // Acquire mutex locks
    pthread_mutex_lock(&lock2); // AGENT-A GETS LOCK1
    // SCHEDULER PULLS OUT AGENT_A // NO LONGER RUNNING

    // AGENT-A TRIES TO GET LOCK2
    pthread_mutex_lock(&lock1); // CANNOT

    for (int i = 0; i < MAXIMUM; i++) {
        counter++; // Critical Section
    } // INCREMENT COUNTER BY 1000

    // Release mutex locks
    pthread_mutex_unlock(&lock1);
    pthread_mutex_unlock(&lock2);

    // Finish threaded function
    pthread_exit(0);
}

void * agent_b(void * param) {

    // Acquire mutex locks
    pthread_mutex_lock(&lock1); // AGENT-B: YO I GOT LOCK2

    // BLOCKED --> FLOW OF EXECUTION GOES TO AGENT-A
    pthread_mutex_lock(&lock2); // AGENT-B: CANNOT GET LOCK1

    for (int i = 0; i < MINIMUM; i++) {
        counter--; // Critical Section
    } // DECREASE COUNTER BY 990

    // Release mutex locks
    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);

    // Finish threaded function
    pthread_exit(0);
}
