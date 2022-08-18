/**
 * Assignment 2 Skeleton File
 * 
 * This file contains partial code for assignment #2; also known as a
 * skeleton file. Follow the "Steps" and fill in each part. The steps
 * correspond to the high-level overview given on the course website.
 * Some steps may not match the description on the course website, but
 * the description is the same. So if you are confused as to what
 * part/piece corresponds to what on the course website, use CTRL-F
 * to search and match a subset of the description(s) (i.e. A few
 * words).
 * 
 * @author Dr. Franek
 * @author Jatin Chowdhary
 * @course CompSci 2SD3
 * @date March 8th, 2022 
 */

/* Standard header files that need to be included */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "log.h"

#define MAX_PERSONS 8
#define MIN_PERSONS 1
#define INPUT_SIZE  100

// ## STEP 1: Define global variables for logging functions:
int logindex = 0;
int * logi = &logindex;
pthread_mutex_t tlock = PTHREAD_MUTEX_INITIALIZER;
// ## NOTE: DO NOT MODIFY THESE LINES!!!

// STEP 2: Declare and initialize a mutex. This will be used to
//         protect a critical section that indicates if all persons
//         are done.
pthread_mutex_t done_lock = PTHREAD_MUTEX_INITIALIZER;

// STEP 3: Create the function prototype for the threaded function.
//         Hint: This is a threaded function, so the return type and
//         argument type are void pointers. You can call the function
//         whatever you want.
void * personality (void * param);

// STEP 4: Define a structure to hold all relevant information for a
//         personality. The members are: index, tid, name, linecount,
//         done.
typedef struct {
    // index;
    pthread_t tid;
    char name[10];
    // linecount
    // done;
} PERSON;

// STEP 5: Define a table (i.e. An array) with as many entries as
//         personalities, where each item is a PERSON struct, as
//         defined in STEP 4.
PERSON persons[MAX_PERSONS];

// STEP 6: Define an int that will be used to indicate if all persons
//         are done or not. Note: This is what the 2nd mutex, in STEP
//         2 will 'protect'.
int done = 0;

/**
 * Main function
 */
int main(int argc, char const *argv[]) {

    int i;

    // for (int i = 0; i < something; i++) { // code }
    // THIS ^^ DOES NOT WORK ON MILLS ^^

    // STEP 7: Checks the `_level` and if it is not in the range
    //         1..8, an error message is displayed and the program
    //         terminates.
    if (_level < 1 || _level > 8) { // incorrect level
        // STEP 7A: Print an appropriate error message via `msg()`
        // msg("this does not work");
        // msg_exit("");
        return 42; // What number is 'X'?
        //exit();
    } else if (_level == 1) {
        // STEP 7B: Indicate that there is only 1 personality. Print
        //          this via `msg()`
        msg("There is only 1 personality: Person 0\n");
    } else {
        // STEP 7C: Iterate from 0 to `_level` and print each
        //          personality (i.e. "Person_%d") via `msg()`
        /*
        for (???) {
            msg("Person_%d" is present);
        }
        */
        msg(""); // Adds a newline (\n) at the very end // Makes it pretty
    }

    // STEP 8: Open the log file. Use `create_log()`. The name of the
    //         log file should be 'assgn2.log'


    // STEP 9: Loop from 0 to `_level`. On each iteration, initialize
    //         the values on the table for `person_i`.
    /*
    for (???) {
        person[i].index = i;
        // tid;
        sprintf(person[i].name,"Person%d",i); // char name[10];
        // linecount 
        // done; = -1;
    }
     */

    // STEP 10: Set the variable/int from STEP 6 to `0` here
    // int ZZZ = 0; // Used in the condition portion in the do-while

    // STEP 11/12: Create a do-while loop. Fill in the following
    //             blanks:
    /*
    do {
        // STEP 11A: In a for-loop, iterate from 0 to `_level`:
        for (???) {
            // STEP 11B: Check if `person[i]` is done. If so move on
            //           to the next person (i.e. Use `continue`)
            // STEP 11C: If (11B) is false, then create a thread
            //           for `person[i]`. Use `pthread_create()`.
            //           Check the return value of `pthread_create()`
            if (pthread_create(tid, attr, personality, arg) != 0) {
                msg_exit(???); // Use `person[i]` to specify which
                               // person cannot create a thread
            }
            // A = TID of person[i];
            // B = Attributes (Default)
            // C = Which function to execute? personality
            // D = Argument // Maybe hard... 
        }
        // STEP 12A: In a for-loop, iterate from 0 to `_level`:
        for (???) {
            // STEP 12B: Check if `person[i]` is done. If so move on
            //           to the next person (i.e. Use `continue`)
            // STEP 12C: If (12B) is false, then use `pthread_join()`
            //           to ensure that the corresponding thread
            //           created in (11C) terminates BEFORE the 'main'
            //           thread. Check the return value to make sure
            //           nothing goes awry.
            if (pthread_join(tid, arg) != 0) {
                msg_exit("Thread[%d] failed to join")
                // Indicate which thread caused the error.
                // Hint: Use `errno`.
            }
        }
    } while (ZZZ != 0);

    // TIP: Since ZZZ starts with value 0, the testing of its value
    //      must be at the bottom of the loop, not at the top of the
    //      loop
    */

    // STEP 13: Display how many lines each conversation had by
    //          traversing the table and using the linecount for each
    //          personality.
    /*
    for (???) {
        msg("%s (name) processed %d lines of messages", ???, ???);
    }
    */

    return 0;
}

void * personality (void * param) {

    char user_input[INPUT_SIZE];
    PERSON * persons;

    // STEP 14: Cast `param` to `persons`
    // HINT: Recall that void pointer is 'bigger'
    // Generic -> Specific

    // STEP 15: Acquire mutex lock (from STEP 2) via
    //          `pthread_mutex_lock()`

    // STEP 16: If `person[i]` is just starting, increment `done` by
    //          1. In other words, `done` is now 0, previously it was
    //          -1. Next, increment the variable/int from STEP 6 by 1.
    /*
    if (???) {
        // person[i].done... 
        // ZZZ++;   
    }
    */

    // STEP 17: Print information that corresponds to the person that
    //          is 'talking'
    // msg("[pid=%u,tid=%u,index=%u,name=%s] Enter Message:",
    // ???, ??? , ???, ???);

    // STEP 18: Display a prompt to get user input. Store this
    //          information into `user_input`; defined above. Use
    //          `fgets()` for this
    // fgets(???, INPUT_SIZE, stdin);

    // STEP 19: Set the last character in `user_input` to '\0'. Why
    //          are we doing this? Hint: Safety.

    // STEP 20: Release the mutex lock from STEP 15. Use
    //          `pthread_mutex_unlock()`

    // STEP 21: If the response started with 'quit', then:
    if (strncmp(???, "quit", ???) == 0) {
        // STEP 21A: Set `done` corresponding to `person[i]` to 1
        //           Acquire mutex lock (from STEP 2)
        // STEP 21B: Decrement global variable from STEP 6 by 1
        // STEP 21C: Release mutex lock from (21A)
        // STEP 21D: Displays and logs a message that the user quit
        // STEP 21E: Exit the thread; return value is irrelevant
    }

    // STEP 22: If the response did not start with quit, then:
    //          A) Increment `linecount` for `person[i]` by 1
    //          B) Writes the message consisting of the prompt and
    //             the response into the log
    //          C) Exits the thread, its return value is irrelevant
}
