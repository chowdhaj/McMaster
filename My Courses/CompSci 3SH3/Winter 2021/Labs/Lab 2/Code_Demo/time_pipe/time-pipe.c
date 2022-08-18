/**
 * time-pipe.c
 *
 * C program that creates a child process from a parent process
 * using fork(), and transfers information between both processes
 * using ordinary pipes. The child process executes a command,
 * and the time it takes to execute the command is measured. The
 * first time interval is taken when the child process is started,
 * and the final interval is taken when the child process is
 * terminated by the parent process. The difference is printed to
 * the terminal.
 * Note: Time is measured in microseconds (us).
 * Note: The execessive comments are for learning purposes.
 *
 * The makefile must be used to compile this program.
 *
 * Author: Jatin Chowdhary
 * Code borrowed from Operating System Concepts - 10th Edition
 *
 * License: GPL
 */

#include <stdio.h>       // Standard I/O Library
#include <unistd.h>      // Standard Symbolic Constants & Types
#include <string.h>      // String Library
#include <sys/wait.h>    // Library For Waiting
#include <sys/time.h>    // Time Types Library
#include <sys/types.h>   // Library For Data Types

#define BUFFER_SIZE 128  // Constant Buffer Size For Allocation
#define READ_END 0       // Constant To Represent Read
#define WRITE_END 1      // Constant To Represent Write
#define FALSE 0          // Constant For False
#define TRUE 1           // Constant For True
#define SECS 0           // Constant For Seconds (Sleep)

// Function Prototypes/Declarations
// These functions are defined below
int bad_argument(int size, char *arg_1);
int did_fail(int code, int print_err);

int main(int argc, char *argv[]) {

    // Checks number of arguments inputted
    if (bad_argument(argc, argv[0])) {
        return (1);
    }

    // Struct object that will get used to get Epoch time values
    struct timeval get_start_time;

    // Array file descriptor
    int fd[2];

    // Declaration for pid_t
    pid_t pid;

    // Create the pipe
    if (pipe(fd) == -1) {
        fprintf(stderr, "Pipe failed\n");
        return (1);
    }

    // Forks the parent and creates a child process
    pid = fork();

    /*
     * This if-else conditional checks the result of the fork()
     *   and determines if it was successful or not.
     * If the value of 'pid' is less than 0, then the fork()
     *   failed. It will return an exit code of (1), and print
     *   the error to a 'stderr' file.
     * If 'pid' is equal to 0, then the fork() was successful,
     *   the child process is carried out, and the parent
     *   process is also executed.
     */
    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return(1);
    } else if (pid == 0) { // The Child Process

        printf("Child created\n");

        /*
         * The child process does not contain information that
         *   is relevant to the parent process. Thus, the parent
         *   process does not need to read any of the child
         *   process' memory. This pipe is closed, because
         *   it is not used.
         */
        did_fail(close(fd[READ_END]), 3);

        // Alternative way to use 'did_fail' // Ignore for now
        //if(did_fail(close(fd[READ_END]), 3));

        // Returns the timeval struct with the Epoch values
        gettimeofday(&get_start_time, NULL);

        // Prints Epoch time in microseconds // Ignore for now
        // printf("ET(us): %lu\n", start.tv_usec);

        /*
         * The child process writes the pointer of the struct
         *   that contains the initial Epoch values to the
         *   pipe.
         * The child process writes the exact size of the
         *   structs' type.
         */
        did_fail(write(fd[WRITE_END], &get_start_time,
                              sizeof(get_start_time)),
                                                   2);

        /*
         * The child process no longer needs to write
         *   anything to the write end of the pipe. This
         *   closes the pipe.
         */
        did_fail(close(fd[WRITE_END]), 3);

        // Execute the command supplied in 'argv'
        // Checks if the command failed
        if (did_fail(execlp(argv[1], argv[1], argv[2], NULL),
                                                      FALSE)) {
            printf("\nERROR: The command failed to execute\n");
            printf("ERROR: This may not be a real command\n\n");
        }

    } else { // The Parent Process

        // Parent process waits for child process to finish
        wait(NULL);
        // The child process has now been terminated

        struct timeval finish_time;
        // This is the time that the child process finishes
        gettimeofday(&finish_time, NULL);

        printf("Child complete\n");

        /*
         * The child process does not need any data from
         *   the parent process. The write end of the pipe
         *   is unused and closed.
         */
        did_fail(close(fd[WRITE_END]), 3);

        /*
         * The parent process reads data from the childs
         *    process' write end of the pipe. It contains
         *    a pointer to a struct that holds the inital
         *    Epoch time.
         * The data is read, and written to a struct that is
         *   part of the parent's process
         */
        did_fail(read(fd[READ_END], &get_start_time,
                            sizeof(get_start_time)),
                                                 1);

        // Print data in the pipe // Ignore for now
        // printf("read %lu\n", get_start_time.tv_usec);

        /*
         * The data (initial Epoch time) has been read and
         *   stored from the read end of the pipe. It can
         *   now be closed.
         */
        did_fail(close(fd[READ_END]), 3);

        // Prints the elapsed time in microseconds
        printf("Time Elapsed(us): %lu\n",
            /*
             * The final time from the parent process subtracts
             *   the initial time from the child's process
             */
            finish_time.tv_usec - get_start_time.tv_usec);
    }
    return (0);
}

/*
 * Checks number of inputted arguments for the
 *   main function.
 * If there is only (1) argument, or less, then print
 *   warning messages to the terminal, and return (1).
 */
int bad_argument(int size, char *arg_1) {

    if (size <= 1) {
        printf("\nInvalid Number Of Arguments\n");
        printf("{%s} Is Not A Valid Argument\n", arg_1);
        printf("\nPlease Supply A Valid Argument Like:\n%s\n",
               "ls -la, ls, which ls, etc.\n");
        return (1);
    }
    return (0);
}

/*
 * Checks the exit code of functions that return an int,
 *   and determines if they failed to execute successfully.
 * If functions return a (-1), then they failed.
 * An optional error message can be printed.
 *
 * Special thanks to TD for their help with explaining
 *   the beauty of switch statements, and its superiority
 *   to 'if-else' ladders.
 */
int did_fail(int code, int print_err) {

    if (code == -1) {
        switch (print_err) {
            case 0:
                // No error message printed here
                // Developer handles this case
                break;
            case 1:    // Read Error
                printf("ERROR: Read File Exception\n");
                break;
            case 2:    // Write Error
                printf("ERROR: Write File Exception\n");
                break;
            case 3:    // Close Error
                printf("ERROR: Close File Exception\n");
                break;
            default:   // General Error
                printf("ERROR: Runtime Exception\n");
                break;
        }
        return (1);
    }
    return (0);
}
