/**
 * Solves race condition via atomic integer
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h> // atomic types

void * runner(void * param);

// THIS IS WHERE THE MAGIC HAPPENS
// THIS IS WHERE THE MAGIC HAPPENS
atomic_int counter = 0; // THIS IS WHERE THE MAGIC HAPPENS
// THIS IS WHERE THE MAGIC HAPPENS
// THIS IS WHERE THE MAGIC HAPPENS

int main(int argc, char const *argv[]) {

    printf("The value of counter is: %d\n", counter);
    
    // Declare pthreads
    pthread_t jim;
    pthread_t bob;

    // Create threads
    pthread_create(&jim, NULL, runner, NULL);
    pthread_create(&bob, NULL, runner, NULL);

    // Wait for threads to finish
    pthread_join(jim, NULL);
    pthread_join(bob, NULL);

    printf("The value of counter is: %d\n", counter); // 100000? NO

    return 0;
}

void * runner (void * param) {

    

    // Increment counter by 50000
    for (int i = 0; i < 50000; i++) {
        counter++;
    }

    

    pthread_exit(0);
}


// WHY DOES THIS WORK?

// BECAUSE ATOMIC MEANS: INDIVISIBLE

// IN OTHER WORDS, THE FOLLOWING CODE: `` counter++; `` NEEDS TO BE
// EXECUTED FROM START TO FINISH. SO ALL 3 ASSEMBLY INSTRUCTIONS NEED
// TO BE COMPLETED WITHOUT ANY INTERRUPTIONS
