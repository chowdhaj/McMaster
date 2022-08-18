/**
 * Introduces the concept of process trees. Requires students to
 * create a process tree after analyzing the result of the `fork()`
 * system call.
 *
 * @author Dr. Neerja Mhaskar
 * @author Jatin Chowdhary
 * @course CompSci 3SH3
 * @date January 28th, 2022
 */

#include <unistd.h> // Contains the `pid_t` type
#include <stdio.h>  // Used for the `print_f` function

int main() {

    // 1. Compile and run this program. Analyze the output before
    //    moving to Question #2.

    printf("Hello From Parent\n");

    pid_t f1 = fork();
    printf("Hello After 1 Fork\n");

    pid_t f2 = fork();
    printf("Hello After 2 Forks\n");

    pid_t f3 = fork();
    printf("Hello After 3 Forks\n");


    // 2. After analyzing the output of the code above, answer the
    //    following questions. Feel free to comment and uncomment
    //    any line that is not a `fork()`.

    // 2a. How many times is "Hello After 1 Fork" printed?
    // TODO:

    // 2b. How many times is "Hello After 2 Forks" printed?
    // TODO:

    // 2c. How many times is "Hello After 3 Forks" printed?
    // TODO:

    // 3. Add a newline before the first print statement, "Hello
    //    From Parent".
    // TODO:

    // 4. Compile the program and run it 5 times, and save the output
    //    to the same text file each time.
    //    Tip: Use `>>` to redirect and append output to a file.
    // TODO: 

    // 5. Open the newly created text file and answer the following
    //    questions:

    // 5a. Is "Hello After 1 Fork" printed the same number of times
    //     across all 5 runs? What about "Hello After 2 Forks"? And
    //     "Hello After 3 Forks"?
    // TODO:

    // 5b. What do you notice about the order of the printed
    //     statements? Explain why the output is not the same across
    //     all 5 runs.
    // TODO:

    // 6. Create a tree diagram to model the structure of the created
    //    processes. Indicate what message is printed by each process?
    //    See below for an example of a process tree diagram.
    // TODO:

    // 6a. Is there a process that prints every message?
    // TODO:

    // Done.

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
