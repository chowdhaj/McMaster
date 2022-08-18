/*
 * Demonstrates different `pid` values across the parent and child
 * process. The `getpid()` and `getppid()` functions return different
 * values based on which process is calling them. For more information
 * about these functions, please refer to the "man" pages.
 * 
 * Note: Students are expected to fill in the "TODO" themselves.
 *
 * @author Dr. Neerja Mhaskar
 * @author Jatin Chowdhary
 * @course CompSci 3SH3
 * @date February 1st, 2022
 */

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    
    // Declare `pid_t` variables
    pid_t pid, pid1;

    // Spawn a child process
    pid = fork();

    if (pid == -1) {

        // If `fork()` failed:
        fprintf(stderr, "ERROR:ForkFailedException\n");

    } else if (pid == 0) {

        // Child Process
        pid1 = getpid();
        printf("[Child] `pid` = %d\n", pid);    // What is `pid`?
        printf("[Child] `pid1` = %d\n", pid1);  // What is `pid1`?

    } else {

        // Parent Process
        wait(NULL);
        pid1 = getpid();
        printf("[Parent] `pid` = %d\n", pid);   // What is `pid`?
        printf("[Parent] `pid1` = %d\n", pid1); // What is `pid1`?

    }

    // Question: What PIDs are printed to the screen by the child
    //           process and the parent process?
    // TODO:

    return 0;
}
