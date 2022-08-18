
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h> // This is for threads (pthread)

#define MAX 10

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void * runner(void * param);

int global = 0;

int main(int argc, char const *argv[]) {

    printf("## The counter is: %d\n", global); // 0

    pthread_t tid[MAX];
    // int numbers[10];

    for (int i = 0; i < MAX; i++) {
        pthread_create(&tid[i], NULL, runner, NULL);
    }

    for (int i = 0; i < MAX; i++) {
        pthread_join(tid[i], NULL);
    }

    printf("$$ The counter is: %d\n", global);

    return 0;
}

void * runner(void * param) {

    // TODO: Print thread ID of calling thread
    printf("I am thread %d\n", pthread_self());
    // HINT: Use `man pthread` to find it

    // HERE

    pthread_mutex_lock(&mutex);
    global++;
    pthread_mutex_unlock(&mutex);

    pthread_exit(0);
    // pthread_exit(0);
        // 0 != Numeric zero
    // TODO: What about `pthread_exit(0);` ?
}



