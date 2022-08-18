/**
 * Executes a 'mystery' program from the child process. The 'mystery'
 * programs accepts a character array of pointers as input. It is
 * executed via the `execvp` function - type "man execvp", without
 * the quotations, to learn more about it.
 *
 * @author Dr. Neerja Mhaskar
 * @author Jatin Chowdhary
 * @course CompSci 3SH3
 * @date January 28th, 2022
 */

#include <stdio.h>     // TODO
#include <unistd.h>    // TODO
#include <sys/wait.h>  // TODO

int main() {

    // 0. Specify why each header file is used
    // TODO

    // 1. Print the PID of the parent/root process
    // TODO

    // 2. Use `fork()` to create a child process. Store the return
    //    value in a variable called 'pid' of type 'pid_t'.
    // TODO

    // 3. Complete the following 'if-else' structure, and answer all
    //    questions:

    if (pid == 0) { // Child Process:

        // 3a. Print the PID of the child process
        // TODO

        // 3b. Declare and initialize a character pointer array; call
        //     it 'argv'. It should contain "Hello" and "World".
        //     Note: The last element in the array should be `NULL`.
        //     Hint: char * argv[]
        // TODO

        // 3c. Use `execvp` to execute the 'mystery' program, and pass
        //     the character pointer array from (3b) as an argument.
        //     Store the return value of `execvp` in an integer.
        //     Hint: execvp("./executable", argument);
        // TODO

        // 3d. Check the return value from (3c) to ensure that
        //     `execvp` did not fail. If it did, print out an
        //     appropriate error message to the terminal.
        //     Tip: In *nix systems, '0' means success and anything
        //     else means fail.
        // TODO

        // 3e. Use the provided Makefile to compile your program.
        //     However, do not execute anything.

    } else { // Parent Process:

        // 3f. Use the `wait()` system call to allow the child process
        //     to finish.
        // TODO

        // 3g. Print a message to the terminal, stating that the child
        //     process has finished.
        // TODO

        // 3h. Use the provided makefile to compile the program.
    }

    // 4. Run the program a few times and observe the output.

    // 5. Answer the following questions:

    // 5a. What do you think the 'mystery' function does? Modify the
    //     character pointer array from (3b) to verify this.
    // TODO

    // 5b. Provide an example of when the `execvp` function might
    //     return an error.
    // TODO

    // 6. (Homework) Find a way to print the PID of the parent
    //    process from the child process.
    //    Hint: Use the man pages for `getpid()`

    return 0;
}
