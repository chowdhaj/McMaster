#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void * runner (void * param);

int main(int argc, char const *argv[]) {
    
    printf("Start here\n");

    pid_t f1 = fork();

    pthread_t tid;

    if (pthread_create(&tid, NULL, runner, NULL)) {
        printf("Error:ThreadCreationException\n");
        return -1;
    }

    if (pthread_join(tid, NULL)) {
        printf("Error:ThreadJoinException\n");
        //return 0;
    }

    printf("End Here\n");

    return 0;
}

void * runner (void * param) {
    printf("I am a thread\n");
    pthread_exit(0);
}