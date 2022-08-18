/**
 * Introduces basic information about the`fork()` system call such as
 * its prototype, return type, headers, etc. The "man" pages are
 * heavily referenced, and rudimentary terminologies are explained.
 *
 * @author Dr. Neerja Mhaskar
 * @author Jatin Chowdhary
 * @course CompSci 3SH3
 * @date January 28th, 2022
 */

// Header Files:
// TODO

int main() {

    // 1. Before we can use `fork()` and spawn a process, we need to
    //    read the "man" pages about `fork()` to learn how it works.
    //    Type the following command, without quotes, into the VM
    //    terminal: "man -s2 fork". Answer the following questions
    //    about `fork()`.

    // 1a. In order to use `fork()` what header file needs to be
    //     included?
    // TODO

    // 1b. The process that calls `fork()` is referred to as the
    //     _ _ _ _ _ _ process.
    // TODO

    // 1c. The new process that is spawned by `fork()` is called the
    //     _ _ _ _ _ process.
    // TODO

    // 1d. True/False: The child process and parent process run in
    //     separate memory spaces.
    //     Hint: Search the "man" pages.
    // TODO

    // 1e. Adding on to (1d), will changing a variable in the parent
    //     process affect the same variable in the child process?
    //     Explain why.
    // TODO

    // 1f. True/False: `fork()` is a system call.
    // TODO

    // 2. At the very top, add a line which includes (i.e. #include
    //    header.h) the header file mentioned in (1a).
    // TODO

    // 2a. Consult the "man" pages to figure out what is the function
    //     prototype of `fork()`
    // TODO

    // 2b. What (data) type does `fork()` return?
    // TODO

    // 2c. Does `fork()` take any parameters. If so, list them.
    // TODO

    // 3. Before spawning a child process, have the parent process
    //    print a simple message to the terminal (i.e. "I am the
    //    parent process").
    //    Tip: Don't forget to import the header file that contains
    //    the `printf()` function.
    // TODO

    // 4. Compile and run your code to make sure it works. Use the
    //    provided Makefile.

    // 5. It is time to use `fork()`. Spawn a child process by making
    //    a system call
    // TODO

    // 6. Uncomment the line below, compile the program and run it to
    //    see what happens.
    //printf("Test message\n");

    // 6a. How many times is "Test message" printed to the terminal?
    //     Explain why.
    // TODO 

    // 7. Done; this concludes Example1. The point of this was to
    //    spawn a child process.

    // 8. Draw a tree diagram which shows the relationship between
    //    parent and child processes.
    // TODO 

    return 0;
}
