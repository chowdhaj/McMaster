/*
 * Introduces the concept of process trees. Requires students to
 * create a process tree after analyzing the result of the `fork()`
 * system call.
 *
 * Note: Students are expected to fill in the "TODO" themselves.
 *
 * @author Dr. Neerja Mhaskar
 * @author Jatin Chowdhary
 * @course CompSci 3SH3
 * @date February 1st, 2022
 */

#include <unistd.h> // Contains the `pid_t` type
#include <stdio.h>  // Used for the `print_f` function

int main() {

    printf("Hello From Parent Process (P1)\n");

    pid_t fork1 = fork();
    printf("One Fork\n");

    // Question: At this point, how many processes are running and
    //           what are their names? (i.e. P1, P3, etc.)
    // TODO:

    // Question: How many times is "One Fork" printed out?
    // TODO:

    pid_t fork2 = fork();
    printf("Two Forks\n");

    // Question: At this point, how many processes are running and
    //           what are their names? (i.e. P2, P4, etc.)
    // TODO:

    // Question: How many times is "Two Forks" printed out?
    // TODO:

    pid_t fork3 = fork();
    printf("Three Forks\n");

    // Question: At this point, how many processes are running and
    //           what are their names? (i.e. P5, P6, etc.)
    // TODO:

    // Question: How many times is "Three Forks" printed out?
    // TODO:

    return 0;
}

/**
 * Example Of A Process Tree Diagram
 *
 *              P1
 *              |
 *              |
 *              P2
 *             /  \
 *            P3  P4
 *           /
 *          P5
 *
 * P1 prints the following: ...
 * P2 prints the following: ...
 * P3 ...
 * P4 ...
 * ...
 */
