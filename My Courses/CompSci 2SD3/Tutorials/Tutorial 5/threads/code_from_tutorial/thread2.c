// Threads
// pthread library

#include <stdio.h>   // printf
#include <pthread.h> // pthread
#include <stdlib.h>  // atoi
#include <stdatomic.h>
//#include <stdatomic.h> // atomic types

atomic_int counter = 0;

void * runner (void * param);

int main(int argc, char * argv[]) {

    printf("We start here\n");

    // Basics parts to creating a thread:
    // 1. threadID (pthread_t)
    // 2. pthread_create()
    // 3. pthread_join()

    pthread_t bob; // This is the name
    // pid = process ID

    pthread_t jim; // Another thread ID

    pthread_create(&bob, NULL,
        runner, NULL);
    // How to pass int?

    pthread_create(&jim, NULL, runner, NULL);

    // Why need this? // To let thread finish
    // Why no ampersand? // Just need value
    pthread_join(bob, NULL);
    pthread_join(jim, NULL);

    printf("The value is:%d\n", counter);
    // this should be 100000 // 50K + 50K

    return 0;
}

// Why void *?
// to make the function definition more versatile
void * runner (void * param) {

    printf("I am a thread\n");

    int i;

    for (i = 0; i < 50000; i++) {
        counter++; // i see 1 line
    }

    //int * x = param; // param is void *

    //printf("The value is: %d\n", *x);

    // Kind of optional // but good practice
    pthread_exit(0);
}

// int * --> void * --> int * --> int









