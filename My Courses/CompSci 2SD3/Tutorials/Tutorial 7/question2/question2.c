#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void * runner (void * param);

int main(int argc, char const *argv[]) {

    pthread_t tid1, tidl;

    if (pthread_create(&tid1, NULL, runner, NULL)) {
        printf("Error:ThreadCreationException\n");
        return -1;
    }

    pthread_join(tidl, NULL);

    return 0;
}

void * runner (void * param) {
    printf("I am a thread\n");
    pthread_exit(0);
}
