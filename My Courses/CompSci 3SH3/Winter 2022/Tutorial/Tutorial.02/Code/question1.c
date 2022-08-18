/*
 * Demonstrates the idea that processes have their own stack, heap,
 * etc. that is different from their parent/child process(es).
 * Modifying a global/local variable that is specific to one process
 * will not affect the same variable in another process.
 *
 * @author Dr. Neerja Mhaskar
 * @author Jatin Chowdhary
 * @course CompSci 3SH3
 * @date February 1st, 2022
 */

#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int global = 5; // Global variable - accessible by all functions

int main() {
    
    int local = 55; // Local variable - only accessible by main

    pid_t pid = fork();

    if (pid == 0) { // Child Process
        global *= 10;
        local  *= 10;
    } else { // Parent Process
        wait(NULL);
        printf("Value1 = %d\n", global); // What is the output?
        printf("Value2 = %d\n", local);  // What is the output?
    }

    return 0;
}

/**
 * Question: What is the value (1) of the global variable?
 * Options:
 *      A) 5
 *      B) 55
 *      C) 50
 *      D) 0
 *      E) 550
 * Question: What is the value (2) of the local variable?
 * Options: 
 *      A) 5
 *      B) 55
 *      C) 50
 *      D) 0
 *      E) 550
 */
