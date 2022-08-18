/**
 * Write a C program that corresponds to the process tree diagram
 * found below. Use the `fork()` system call to create child
 * processes. Each parent process must wait for their child process,
 * or processes, to finish - use the `wait()` system call; you can
 * read more about it in the 'man' pages (i.e. "man -s2 wait").
 * Additionally, each process must print their `pid` to the screen;
 * use the `getpid()` function to get the `pid` of the process.
 *
 * @author Dr. Neerja Mhaskar
 * @author Jatin Chowdhary
 * @course CompSci 3SH3
 * @date January 28th, 2022
 */

#include <unistd.h>    // Contains the `pid_t` type
#include <stdio.h>     // Used for the `print_f()` function
#include <sys/wait.h>  // Required for the `wait()` system call

/**
 * * * * * * * * *
 * Instructions  *
 * * * * * * * * *
 *
 * 0. Include the header files for `printf()`, `wait()`, and `pid_t`.
 *    Refer to the 'man' pages (i.e. "Synopsis" section) for more
 *    information.
 * 1. Print the `pid` of the parent process, P1. You can use the
 *    `getpid()` function; the format specifier is '%d'.
 * 2. Use fork to spawn a child process (P2).
 * 3. Have the child process (P2) print its (real) `pid`, while the parent
 *    waits for the child process (P2) to finish.
 * 4. So far, the process tree diagram looks like the following:
 *
 *       P_1
 *        |
 *        |
 *        V
 *       P_2
 *
 * 5. Use `fork()` and `wait()` to create the following process tree:
 *
 *                      P_1
 *                       |
 *                       |
 *                      P_2
 *                    /  |  \
 *                   /   |   \
 *                 P_9   |    P_5
 *                       |      \
 *                      P_3      \
 *                     / |       P_8
 *                    /  |
 *                   /  P_4
 *                  /    |
 *                P_7    |
 *                      P_6
 *
 * 6. Ensure each (child) process prints its `pid`.
 * 7. Ensure each (parent) process waits for its child process to
 *    finish before proceeding.
 * 8. Remember to comment your code!
 *
 * * * * * * * * *
 * Sample Output *
 * * * * * * * * *
 *
 * PID (P1) is: 7615
 * PID (P2) is: 7616
 * PID (P3) is: 7618
 * PID is: 7619
 * PID is: 7620
 * PID is: 7621
 * PID is: 7622
 * PID is: 7623
 *
 */

int main() {

    printf("PID (P1) is: %d\n", getpid());

    // Create the process tree diagram shown above
    // TODO

    return 0;
}
