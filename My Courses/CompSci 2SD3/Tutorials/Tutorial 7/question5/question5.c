#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void * runner (void * param);

int main(int argc, char const *argv[]) {
    
    printf("Start here\n");

    pid_t f1 = fork();

    pthread_t tid1, tid2;

    if (pthread_create(&tid1, NULL, runner, NULL)) {
        printf("Error:ThreadCreationException\n");
        return -1;
    }

    if (pthread_join(tid1, NULL)) {
        printf("Error:ThreadJoinException\n");
        //return -1;
    }

    //////////////
    /* NEW CODE */
    //////////////
    if (f1 == 0) {

        // QUESTION : Is the parent or child process executing this?
        // ANSWER   : ???

        if (pthread_create(&tid2, NULL, runner, NULL)) {
            printf("Error:ThreadCreationException\n");
            return -1;
        }

        if (pthread_join(tid2, NULL)) {
            printf("Error:ThreadJoinException\n");
            //return -1;
        }
    }
    //////////////
    /* NEW CODE */
    //////////////

    printf("End Here\n");

    return 0;
}

void * runner (void * param) {
    printf("I am a thread with ID: %lu | My parents ID is: %d\n",
        pthread_self(), getpid());
    pthread_exit(0);
}
