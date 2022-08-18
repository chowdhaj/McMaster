/**
 * Contains basic information about the `fork()` system call.
 * Introduces preliminary stuff like `pid_t` type, spawning child
 * processes, checking exit status, separating parent and child
 * code, getting `pid` of the process, waiting, etc.
 *
 * @author Dr. Neerja Mhaskar
 * @author Jatin Chowdhary
 * @course CompSci 3SH3
 * @date January 28th, 2022
 */

// Header Files:
// TODO

int main() {

    // 1. Include the header files that correspond to `printf()` and
    //    `fork()`.
    // TODO

    // 2. Read the "man" pages for `fork()`, and answer the following
    //    questions. Type "man -s2 fork", without the quotations,
    //    to review the manual.

    // 2a. Upon success, what does `fork()` return to the parent
    //     process? What about the child process? Why are these 2
    //     values different?
    //     Hint: Think in terms of separation/distinction.
    // TODO

    // 2b. Explain what happens when `fork()` fails.
    // TODO

    // 3. Recall from the previous exercise, what is the return type
    //    of `fork()`?
    // TODO

    // 3a. Implore why the return type of `fork()` isn't a simple
    //     int, signed or unsigned.
    // TODO

    // 4. From the parent process, print out the following message:
    //    "Parent process says Hello".
    // TODO

    // 5. Run your code to make sure it compiles. Use the provided
    //    Makefile.

    // 6. Declare a variable of type `pid_t` called 'status'.
    // TODO

    // 7. Spawn a child process using `fork()` and store the exit
    //    status/value into 'status'.
    // TODO

    // 8. Print the value of 'status' to the terminal. For example:
    //    "The value of status is: %d".
    //    Note: `pid_t` is basically an int, so you can use the %d
    //    format specifier.
    // TODO

    // 9. Run your code to see the output of (8)

    // 10. What do you notice about the values from (8)? Which process
    //     is reponsible for which value?
    // TODO

    // 11. Run your compiled program a few more times to see if your
    //     answer from (10) holds.

    // 12. Create an 'if-else' structure that checks the following:
    //     1) Did the `fork()` fail?
    //     2) If the fork was successful, have the child process
    //        print "Hello", and the parent process print "World".
    // TODO

    // 13. Run your code and analyze the output of (12)

    // 14. Use the `getpid()` function to print the PID of each
    //     process, inside the 'if-else' statement. For example:
    //     printf("The PID of process ??? is: %d", getpid());
    // TODO

    // 15. Run your code and analyze the output of (14)

    // 16. Move the `printf()` statement that you created in (8),
    //     inside the 'if-else' structure.
    // TODO

    // 17. Run your code and analyze the output of the 4 print
    //     statements; 2 inside 'if' and 2 inside 'else'. What values
    //     are the same? Why?
    // TODO

    return 0;
}
