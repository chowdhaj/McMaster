// Threads
// pthread library

#include <stdio.h>   // printf
#include <pthread.h> // pthread
#include <stdlib.h>  // atoi

void * runner (void * param);

int main(int argc, char * argv[]) {

    printf("We start here\n");

    // Basics parts to creating a thread:
    // 1. threadID (pthread_t)
    // 2. pthread_create()
    // 3. pthread_join()

    pthread_t threadID; // This is the name
    // pid = process ID

    pthread_t tid; // Another thread ID

    int x = 5;
    int x1 = 9.0;
    // double 
    // int *   // points to int
    // char *  // points to char
    // float * // 
    // void *  //

    // struct y ... ;

    pthread_create(&threadID, NULL,
        runner, NULL);
    // How to pass int?

    pthread_create(&tid, NULL, runner, NULL);

    // Why need this? // To let thread finish
    // Why no ampersand? // Just need value
    pthread_join(threadID, NULL);
    pthread_join(tid, NULL);

    return 0;
}

// Why void *?
// to make the function definition more versatile
void * runner (void * param) {

    printf("I am a thread\n");

    //int * x = param; // param is void *

    //printf("The value is: %d\n", *x);

    // Kind of optional // but good practice
    pthread_exit(0);
}

// int * --> void * --> int * --> int









