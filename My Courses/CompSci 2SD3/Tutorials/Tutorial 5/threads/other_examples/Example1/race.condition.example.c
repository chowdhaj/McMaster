/**
 * Introduces the idea of race conditions
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void * runner(void * param);

int counter = 0;

int main(int argc, char const *argv[]) {

    // MAIN THREAD IS RUNNING

    printf("(1) The value of counter is: %d\n", counter); // print 0
    
    pthread_t jim;
    pthread_t bob;

    // pthread_create(pthread_t, attr, function, arg);
    pthread_create(&jim, NULL, runner, NULL);
    pthread_create(&bob, NULL, runner, NULL);

    pthread_join(jim, NULL);
    pthread_join(bob, NULL);

    printf("(2) The value of counter is: %d\n", counter); // print 100000

    return 0;
}

void * runner (void * param) {

    printf("Start incrementing\n");

    for (int i = 0; i < 50000; i++) {
        counter++;
    }
    // jim: counter += 50000 // starts at 0     -> 50000
    // bob: counter += 50000 // starts at 50000 -> 100000

    pthread_exit(0);
}
