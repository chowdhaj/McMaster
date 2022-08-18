/**
 * Assume all header files have been imported, and disregard syntax.
 * Assume that the code compiles without warnings/errors.
 */

#define FORK 5

main(){

    pid_t pid;

    for (int i = 0; i < FORK; i ++) {
        pid = fork();
        if (pid) {
            pthread_create(...);
            pthread_join(...);
        } else {
            break;
        }
    }
}