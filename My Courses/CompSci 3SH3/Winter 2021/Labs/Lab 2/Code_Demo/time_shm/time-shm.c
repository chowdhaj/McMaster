/**
 * time-shm.c
 *
 * C program that creates a child process from a parent process
 * using fork(), and transfers information between both processes
 * using a shared memory buffer. The child process executes a
 * command, and the time it takes to execute the command is
 * measured. The first time interval is taken when the child
 * process is started, and the final interval is taken when
 * the child process is terminated by the parent process. The
 * difference is printed to the terminal.
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

#include <stdio.h>        // Standard I/O Library
#include <stdlib.h>       // Standard Library Definitions
#include <string.h>       // String Library
#include <sys/shm.h>      // Shared Memory Library
#include <sys/mman.h>     // Memory Management Library
#include <sys/wait.h>     // Library For Waiting
#include <sys/time.h>     // Time Types Library
#include <fcntl.h>        // Library For File Descripter
#include <unistd.h>       // Standard Symbolic Constants & Types

#define MEM_NAME "SH_MEM" // Constant Literal Name For Memory
#define BUFFER_SIZE 1024  // Constant Buffer Size For Allocation
#define RW_PERMS 0666     // Constant For Read/Write Permissions
#define RO_PERMS 0444     // Constant For Read Permissions
#define FALSE 0           // Constant For False
#define TRUE 1            // Constant For True
#define SECS 0            // Constant For Seconds (Sleep)

// Function Prototypes/Declarations
// These are all defined below
int bad_argument(int size, char *arg_1);
int did_fail(int code, int print_err);
int is_null(char * ptr, int print_err);
int convert_str(char * ptr, long unsigned int * start_time);
long unsigned int get_epoch_time_us(struct timeval *current_time);

int main(int argc, char *argv[]) {

    // Checks number of arguments inputted
    if (bad_argument(argc, argv[0])) {
        return (1);
    }

    // Struct object that contains Epoch time values
    struct timeval current_time;

    // Long unsigned int for storing Epoch time
    long unsigned int start_time = 0;

    // Shared memory file descriptor
    int file_desc;

    // Pointer to shared memory object
    char *ptr;

    /*
     * Create the shared memory object
     *
     * MEM_NAME  :: Path name of the file object
     * O_CREAT   :: The mode (i.e. Create)
     * O_RDWR    :: Opens file as read/write
     * RW_PERMS  :: Sets permissions on file as read/write
     */
    file_desc = shm_open(MEM_NAME, O_CREAT |
                         O_RDWR, RW_PERMS);

    // Checks to see if file descriptor failed
    if (did_fail(file_desc, TRUE)) {
         return (1);
    }

    // Configure the size of the shared memory object
    if (did_fail(ftruncate(file_desc, BUFFER_SIZE), TRUE)) {
        return (1);
    }

    // Declaration for pid_t
    pid_t pid;

    // Forks the parent process and creates a child process
    // Result (exit code) is stored in 'pid'
    pid = fork();

    /*
     * This if-else conditional checks the result of the fork()
     *   and determines if it was successful or not.
     * If the value of 'pid' is less than 0, then the fork()
     *   failed. Return to caller with exit code 1, and print
     *   the error to a 'stderr' file.
     * If 'pid' is equal to 0, then the fork() was successful,
     *   the child process is carried out, and the parent
     *   process is also executed.
     */
    if (pid < 0) {
        fprintf(stderr, "%s\n%s\n", "Fork Failed",
                                    "Please Try Again!");
        return (1);
    } else if (pid == 0) { // The Child Process

        printf("Child Created\n");

        /*
         * Maps the memory to the shared memory object
         *
         * 0            :: Determines starting address of the mapping
         * BUFFER_SIZE  :: Sets the size of the memory space
         * PROT_READ    :: Enables read permission
         * PROT_WRITE   :: Enables write permission
         * MAP_SHARED   :: Sets the memory to shared
         * file_desc    :: File descriptor argument
         * 0            :: Specifies the offset
         */
        ptr = (char *)mmap(0, BUFFER_SIZE, PROT_READ |
                              PROT_WRITE, MAP_SHARED,
                              file_desc, 0);

        /*
         * Performs a null check on the pointer to the
         *   shared memory object
         */
        if (is_null(ptr, TRUE)) {
             return (1);
        }

        // Gets the current epoch time; starts the timer
        start_time = get_epoch_time_us(&current_time);

        // Prints Epoch time, in microseconds, to shared memory
        // 'sprintf' takes a buffer, a value, and writes to it
        sprintf(ptr, "%lu\n", start_time);

        /* 
         * Updates the size of the pointer by adding the
         *   'sizeof' the start_time.
         */
        ptr += sizeof(start_time);

        // Execute the command supplied in 'argv'
        // Checks if the command failed
        if (did_fail(execlp(argv[1], argv[1], argv[2], NULL),
                                                      FALSE)) {
            printf("\nERROR: The command failed to execute\n");
            printf("ERROR: This may not be a real command\n\n");
        }

    } else { // The Parent process

        // Parent process waits/sleeps for seconds
        // sleep(SECS); // Ignore for now

        // Parent process waits for child process to finish
        wait(NULL);
        // The child process is now terminated

        // Gets the current Epoch time in microseconds
        long unsigned int finish_time =
            get_epoch_time_us(&current_time);

        printf("Child Complete\n");

        /*
         * Opens the shared memory object
         *
         * MEM_NAME  :: Path name of the file object
         * O_RDONLY  :: Opens file as read-only
         * RO_PERMS  :: Sets permissions on file as read-only
         */
        file_desc = shm_open(MEM_NAME, O_RDONLY, RO_PERMS);

        // Checks to see if file descripter failed
        if (did_fail(file_desc, TRUE)) {
            return (1);
        }

        /*
         * Maps the memory to the shared memory object.
         *
         * 0            :: Determine the starting address of mapping
         * BUFFER_SIZE  :: Sets the size of the memory space
         * PROT_READ    :: Enables read permission
         * MAP_SHARED   :: Sets the memory to shared
         * file_desc    :: File descriptor argument
         * 0            :: Specifies the offset
         */
        ptr = (char *)mmap(0, BUFFER_SIZE, PROT_READ,
                              MAP_SHARED, file_desc, 0);

        /*
         * Performs a null check on the pointer to the
         *   shared memory object
         */
        if (is_null(ptr, TRUE)) {
             return (1);
        }

        // Reads from the shared memory object
        // printf("%s", (char *)ptr); // Ignore for now

        /*
         * Converts the String, start_time, from shared
         *   memory into a long unsigned int.
         * The process is checked to make sure that the
         *   String was parsed properly.
         */
        if (did_fail(convert_str((char *) ptr, &start_time),
                                                    FALSE)) {
            return (1);
        }

       /*
        * Gets the current epoch time and subtracts it
        *   from start_time.
        * Results are printed to the terminal.
        */
        printf("Time Elapsed(us): %lu\n",
            finish_time - start_time);

        // Remove the shared memory object
        shm_unlink(MEM_NAME);
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
 * Checks the exit code of functions (i.e. shm_open,
 *   ftruncate, shm_unlink, execlp, etc.) and determines
 *   if they failed to execute successfully.
 * If functions return a (-1), then they failed.
 * An optional error message can be printed.
 */
int did_fail(int code, int print_err) {

    if (code == -1) {
        if (print_err) {
            printf("Unexpected Error Encountered\n%s\n",
                   "Please Try Again!");
        }
        return (1);
    }

    return (0);
}

/*
 * Checks if a pointer is NULL, and returns
 *   (1) if it is, and (0) otherwise.
 * An optional error message can be printed.
 */
int is_null(char * ptr, int print_err) {

    if (ptr == NULL) {
        if (print_err) {
            printf("ERROR: Null_Pointer_Exception\n");
        }
        return (1);
    }
    return (0);
}

/*
 * Converts a String into a long unsigned integer
 *   and returns the result in the argument.
 * If the conversion fails, then an error message is
 *   printed to the terminal, and an error code of
 *   (-1) is returned.
 */
int convert_str(char * ptr, long unsigned int * start_time) {

    char * end_ptr;

    // Convert string into long unsigned int
    *start_time = strtol((char *)ptr, &end_ptr, 0);

    // If start pointer and end pointer are the same:
    if (end_ptr == ptr) {
        // Then, parsing failed
        printf("ERROR: String_Parse_Exception\n");
        return (-1);
    } else {
        return (0);
    }
}

/*
 * Returns the current epoch time in microseconds.
 * The NULL is for specifying no timezone, which has
 *   been deprecated; it is obsolete.
 */
long unsigned int get_epoch_time_us(struct timeval *current_time) {

    gettimeofday(current_time, NULL);
    return current_time->tv_usec;
}

// END
