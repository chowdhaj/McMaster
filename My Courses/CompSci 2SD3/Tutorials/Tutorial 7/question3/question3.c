#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define COUNT 5

void * runner (void * param);

int main(int argc, char const *argv[]) {

    pthread_t tid;

    if (pthread_create(&tid, NULL, runner, NULL)) {
        printf("Error:ThreadCreationException\n");
        return -1;
    }

    if (pthread_join(tid, NULL)) {
        printf("Error:ThreadJoinException\n");
    }

    return 0;
}

void * runner (void * param) {

    pthread_exit(NULL); // Same as pthread_exit(0);

    for (int i = 0; i < COUNT; i++)
        printf("I am a thread\n");
        printf("I am a thread too!\n");
}
