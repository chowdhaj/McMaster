/**
 * Demonstration of the `fork()` system call. The parent process
 * spawns a child process, and each process prints its `pid`.
 * 
 * @author Jatin Chowdhary
 * @date January 29th, 2022
 */

#include <stdio.h>    // Contains `printf()`
#include <unistd.h>   // Used for `pid_t`, `fork()`, etc.
#include <sys/wait.h> // Contains `wait()`

int main(int argc, char * argv[]) {

    printf("Parent Process (P1) Says Hello\n");

    pid_t exit_status = fork();

    if (exit_status == -1) {

        // Failed To Spawn Child Process
        fprintf(stderr, "%s\n", "Error:ChildFailed");

    } else if (exit_status == 0) {

        // Child Executes This Code:
        printf("Child Process (P2) Says Hello\n");
        printf("Child's PID Is: %d\n", getpid());

    } else {

        // Parent Executes This Code:
        wait(NULL);
        printf("Parent Process (P1) Says Hello\n");
        printf("Parent's PID Is: %d\n", getpid());

    }

    // Uncomment the following line to see what happens:
    //printf("Who Said This?\n");

    return 0;
}

/**
 * * * * *
 * NOTES *
 * * * * *
 * 
 * The PID of the child will (always) be greater than the PID of the
 * parent process (the process that spawned it).
 * 
 * The return value from `fork()` can be used to isolate what code
 * is executed by the child process and parent process. As shown in
 * this example, the parent and child process execute different code.
 * 
 * The `getpid()` function can be used to get the PID of the process.
 * The parent process obtains the PID of the child process via
 * `fork`(). The parent process can obtain the PID of its parent
 * process via `getppid()`.
 * 
 * Read the `man` pages to learn more about `fork()`.
 * [ i.e. man -s2 fork ]
 * 
 */
