/**
 * Assume all header files have been imported, and disregard syntax.
 * Assume that the code compiles without warnings/errors.
 */

main() {

    pid_t pid1, pid2;

    pid1 = fork();
    pid2 = fork();

    if (pid1 == 0) {
        pthread_create(...);
    }

    if (pid2 == 0) {
        pthread_create(...);
    }
}