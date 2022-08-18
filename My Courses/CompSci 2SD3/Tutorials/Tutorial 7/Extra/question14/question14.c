/**
 * Assume all header files have been imported, and disregard syntax.
 * Assume that the code compiles without warnings/errors.
 */

#define FORK 5

main(){

    pid_t pid;
    pthread_t tid1, tid2;

    for (int i = 0; i < FORK; i ++) {
        pid = fork();
        if (pid) {
            pthread_create(tid1, ...);
            pthread_join(tid1, NULL);
        } else {
            break;
        }
    }

    if (pid) {
        pthread_create(...);
    }

    if (pthread_join(tid2, NULL)) {
        printf("Error:CouldNotJoinThread\n");
    }
}