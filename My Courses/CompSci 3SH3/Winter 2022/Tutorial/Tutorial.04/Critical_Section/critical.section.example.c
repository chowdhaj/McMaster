/**
 * Introduces the idea of race conditions
 * 
 * @author Dr. Neerja Mhaskar
 * @author Jatin Chowdhary
 * @course CompSci 3SH3
 * @date February 15th, 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void * runner(void * param);

int counter = 0;

int main(int argc, char const *argv[]) {

    printf("The value of counter is: %d\n", counter);
    
    pthread_t jim;
    pthread_t bob;

    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_create(&jim, &attr, runner, NULL);
    pthread_create(&bob, &attr, runner, NULL);

    pthread_join(jim, NULL);
    pthread_join(bob, NULL);

    printf("The value of counter is: %d\n", counter);

    return 0;
}

void * runner (void * param) {

    for (int i = 0; i < 50000; i++) {
        counter++;
    }

    pthread_exit(0);
}
