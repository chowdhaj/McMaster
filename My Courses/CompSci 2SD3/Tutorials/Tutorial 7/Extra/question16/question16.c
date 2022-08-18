/**
 * Assume all header files have been imported, and disregard syntax.
 * Assume that the code compiles without warnings/errors.
 */

int COUNT = 5;

main(){

    pid_t pid;
    pthread_t tid1;

    for (int i = 0; i < COUNT; i++) {
        fork();
    }

    fork();

    pthread_create(...);
    pthread_join(...);
}
