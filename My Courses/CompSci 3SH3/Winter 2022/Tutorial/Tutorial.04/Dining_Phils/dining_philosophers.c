/**
 * dining_philosophers.c
 *
 * C program that simulates the classic concurrency problem: Dining
 * Philosophers. The philosophers are simulated via threads, and the
 * forks are simulated with an int-array. The number of philosophers,
 * and forks, can be changed by modifying global variables. 
 * Philosophers alternate between thinking and eating. Eating is 
 * further divided into 'picking up forks' (start eating), and 'return
 * forks' (stop eating). The int-array which represents the forks is
 * a critical section, and is protected from race conditions via
 * mutexes. After each action (thinking/eating) relevant information
 * about the philosophers and forks is printed to the terminal.
 * 
 * Note: There is a special function that prints out a visual
 *       representation of the dining philosophers in ASCII art. This
 *       is very useful for learning purposes.
 * Note: The pre-processor directives are very important for under-
 *       standing this program, and how it works.
 * Note: The execessive comments are for learning purposes.
 * Note: This program uses POSIX threads to simulate philosophers
 *       More information on POSIX threads can be found at: 
 *         https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/
 *         www/pthreads.html#SYNCHRONIZATION
 *
 * The makefile must be used to compile this program.
 *
 * Author: Jatin Chowdhary
 * Code borrowed from: Operating System Concepts - 10th Edition
 *
 * License: GPL
 */

#include <stdlib.h>   // Include Standard Library
#include <stdio.h>    // Include Standard I/O
#include <pthread.h>  // Include pthread Library
#include <stdint.h>   // Include More Data Types
#include <unistd.h>   // Include Sleep Function

#define SIZE      5  // Define Size Of Array
#define TRUE      1  // Define True Boole
#define FALSE     0  // Define False Boole
#define FAIL      1  // Define Int Constant For Failure
#define SUCCESS   0  // Define Int Constant For Successful
#define MAX_SLEEP 3  // Define Int Constant For Maximum Sleeping Time
#define MIN_SLEEP 0  // Define Int Constant For Minimum Sleeping Time

#define TEXT_NOTHING   0 // Define Int Constant For No Text
#define TEXT_VISUAL    1 // Define Int Constant For ASCII Art
#define TEXT_PICKUP    2 // Define Int Constant For Pick Up Forks Text
#define TEXT_RETURN    3 // Define Int Constant For Return Forks Text
#define TEXT_THINKING  4 // Define Int Constant For Thinking Text

#define EAT       '*'  // Define Character For Eating Philosopher
#define THINK     '_'  // Define Character For Thinking Philosopher
#define YES_FORK  'Y'  // Define Character To Represent A Fork
#define NO_FORK   ' '  // Define Character To Represent No Fork

// Prototypes for additional/helper functions
int pickup_forks(int philosopher_number, int left_fork,
                 int right_fork);
int return_forks(int philosopher_number, int left_fork, 
                 int right_fork);
int think(int philosopher_number, int min, int max);
int print_information(int format_specifier, int philosopher_number);
int add_forks(void);
int check_variables(void);
int print_array(int print_extra_newline);
int print_special_array(int stall_enabled);
int print_greeting_message(void);
int print_farewell_message(void);

// Prototype for threaded functions
void *run_philosopher(void * number);

// Initializing condition variables & mutexes
pthread_cond_t  fork_signal = PTHREAD_COND_INITIALIZER;
pthread_mutex_t fork_mutex = PTHREAD_MUTEX_INITIALIZER;   

// Global variable declarations/initializations
const char FORK_PRESENT = YES_FORK;
const char FORK_ABSENT = NO_FORK;
const int NUMBER_OF_PHILOSOPHERS = SIZE;
const int MAX_NUMBER_OF_THREADS = 20;
const int TOTAL_ITERATIONS = NUMBER_OF_PHILOSOPHERS;

int FORK_ARRAY[NUMBER_OF_PHILOSOPHERS];
int NUMBER_OF_FORKS = NUMBER_OF_PHILOSOPHERS;

int main(int argc, char * argv[]) {

    // Checks variables to ensure they are not out-of-bounds
    if (check_variables()) {
        return FAIL;
    }

    // Populate the fork-array based on the philosopher count
    if (add_forks()) {
        return FAIL;
    }

    // Print greeting message
    print_greeting_message();

    // Declare arrays for threads and ints
    pthread_t philosopher_threads[NUMBER_OF_PHILOSOPHERS];
    int exit_status_code[NUMBER_OF_PHILOSOPHERS];

    /*
     * Iterate from 0 to total number of philosophers, and create a
     * thread on each iteration to represent the philosopher. The
     * 'pthread_create()' function is used to create each thread.
     *
     * The arguments for the 'pthread_create()' are:
     *   &philosopher_threads[i] :: Stores the ID of the thread
     *   NULL                    :: Use default thread attributes
     *   *run_philosopher        :: The threaded function to run
     *   (void *) (size_t) i     :: Argument passed to the function
     *
     * Upon creation of each thread, the exit status code of
     * 'pthread_create()' is stored, and checked to see if the thread
     * was successfully created or not. If thread creation failed,
     * an error message is printed and the 'main()' thread terminates.
     */
    for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; i++) {
        // Store and check exit status code of 'pthread_create()'
        if (((exit_status_code[i]) = 
            // Create philosopher thread #i
            pthread_create(&philosopher_threads[i], NULL, 
                *run_philosopher, (void *) (size_t) i))) {

            // Print error message if thread creation fails
            printf("ERROR: Failed To Create Philosopher Thread #%d\n",
                i);
            printf("       The Simulator Will Now Terminate\n");
            return FAIL;
        }
    }

    /*
     * Iterate from 0 to total number of philosophers, and join each
     * thread at index `i` from the 'pthread' array with the 'main()'
     * thread/function. This ensures that the thread isn't prematurely
     * terminated. The 'pthread_join()' function is used to join
     * threads with the main function. 
     *
     * The arguments for the 'pthread_join()' function are:
     *   philosopher_threads[i] :: The thread to join with 'main()'
     *   NULL                   :: The thread does not return a value
     * 
     * The exit status code of 'pthread_join()' is stored and checked
     * to see if the corresponding thread was successfully joined with
     * the 'main()' thread. If this operation failed, then an error
     * message is printed to the screen.
     */
    for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; i++) {
        // Store and check exit status code of 'pthread_join()'
        if (((exit_status_code[i]) = 
            // Join philosopher thread at index `i` with 'main()'
            (pthread_join(philosopher_threads[i], NULL)))) {

            // Print error message if thread fails to join
            printf("ERROR: Failed To Join Philosopher Thread #%d\n", 
                i);
            printf("       With Main Thread\n");
        }
    }

    // Print final message
    print_farewell_message();

    return SUCCESS;
}

/**
 * Threaded function that simulates a dining philosopher
 *
 * Calculates the index of each philosopher's left and right fork in
 * the fork-array. Then, a for-loop iterates from 0 to a constant
 * global int (initialized above), executes functions that simulate
 * actions a dining philosopher would do, such as eat and think. 
 * 
 * @param *number The unique integer that identifies a philosopher
 * @return NULL
 */
void *run_philosopher(void * number) {

    // Convert void argument into an integer
    int philosopher_number = (int) number;

    // Calculate left and right forks indexes for the philosopher
    int left_fork = philosopher_number;
    int right_fork = (philosopher_number + 
        (NUMBER_OF_PHILOSOPHERS - 1)) % NUMBER_OF_PHILOSOPHERS;

    // Iterates from 0 to a global constant integer
    for (int i = 0; i < TOTAL_ITERATIONS; i++) {
        // Philosopher simulates picking up forks (start eating)
        pickup_forks(philosopher_number, left_fork, right_fork);
        // Philosopher simulates returning forks (finished eating)
        return_forks(philosopher_number, left_fork, right_fork);
        // Philosopher simulates thinking
        think(philosopher_number, MIN_SLEEP, MAX_SLEEP);
        // Note: Comment out 'think(...)' to speed-up execution
    }

    // Terminate philosopher thread
    pthread_exit(0);
}

/**
 * Simulates the action of picking up forks at the dining table
 * 
 * Checks if a philosopher's corresponding forks are available, and
 * if they are the philosopher picks them up and starts eating. The
 * respective forks in the fork-array are marked as unavailable, and
 * information about the fork-array is printed to the terminal. On
 * the other hand, if the forks are unavailable, the corresponding
 * philosopher thread is put to sleep. Mutexes are used to preserve
 * exclusionary rights. The fork-array is a critical section, and
 * should not be accessed by more than one philosopher at a time.
 * After the philosopher acquires his forks, the mutex lock is
 * released and the function returns an exit status code. 
 * 
 * @param philosopher_number The philosopher's unique number, which
 *        represents his location at the table
 * @param left_fork The index of the fork in the fork-array that is
 *        on the left-side of the dining philosopher
 * @param right_fork The index of the fork in the fork-array that is
 *        on the right-side of the dining philosopher
 * @return exit_status_code The exit code of the function; indicates
 *         if the function finished with, or without, errors
 */
int pickup_forks(int philosopher_number, int left_fork, 
                                         int right_fork) {

    // Set exit status code to fail
    int exit_status_code = FAIL;

    // Acquire mutex lock
    pthread_mutex_lock(&fork_mutex);

    // If philosopher's left OR right fork is unavailable:
    while ((FORK_ARRAY[left_fork]  == 0) || 
           (FORK_ARRAY[right_fork] == 0)) {
        // Put philosopher thread to sleep
        pthread_cond_wait(&fork_signal, &fork_mutex);
    }

    // Update status of philosopher's corresponding forks
    FORK_ARRAY[left_fork]  = 0;
    FORK_ARRAY[right_fork] = 0;

    // Print relevant information to the terminal
    print_information(TEXT_VISUAL, philosopher_number);
    
    // If philosopher's forks are unavailable:
    if ((FORK_ARRAY[left_fork]  == 0) && 
        (FORK_ARRAY[right_fork] == 0)) {
        // Set exit status code to success
        exit_status_code = SUCCESS;
    }

    // Release mutex lock
    pthread_mutex_unlock(&fork_mutex);

    return exit_status_code;
}

/**
 * Simulates the action of returning forks; philosopher is done eating
 * 
 * Before any action takes place, a mutex lock is acquired. Then, the
 * philosopher returns forks and updates the status of his forks in
 * the fork-array to available. Relevant information about this
 * transaction is printed to the terminal. If the corresponding forks
 * are back in the fork-array, the exit status code is updated to
 * success. Finally, the other philosopher threads are woken up, the
 * mutex lock is released, and the function terminates. A mutex is
 * used in this function because it accesses the fork-array, which is
 * a critical section. 
 *
 * @param philosopher_number The philosopher's unique number, which
 *        represents his location at the table
 * @param left_fork The index of the fork in the fork-array that is
 *        on the left-side of the dining philosopher
 * @param right_fork The index of the fork in the fork-array that is
 *        on the right-side of the dining philosopher
 * @return exit_status_code The exit code of the function; indicates
 *         if the function finished with, or without, errors
 */
int return_forks(int philosopher_number, int left_fork, 
                                         int right_fork) {

    // Set exit status code to fail
    int exit_status_code = FAIL;

    // Acquire mutex lock
    pthread_mutex_lock(&fork_mutex);

    // Update availability of philosopher's left and right fork
    FORK_ARRAY[left_fork]  = 1;
    FORK_ARRAY[right_fork] = 1;

    // Print relevant information to the terminal
    print_information(TEXT_RETURN, philosopher_number);

    // If both forks are available:
    if (FORK_ARRAY[left_fork] && FORK_ARRAY[right_fork]) {
        // Set exit status code to success
        exit_status_code = SUCCESS;
    }

    // Wake-up other philosopher threads that are sleeping
    pthread_cond_signal(&fork_signal);

    // Release mutex lock
    pthread_mutex_unlock(&fork_mutex);

    return exit_status_code;
}

/**
 * Simulates a thinking philosopher, by putting the thread to sleep
 * 
 * Philosopher threads are put to sleep, which simulates the action
 * of a thinking philosopher. The minimum amount of time a philosopher
 * can sleep for must be greater than or equal to 0. Plus, the
 * the minimum sleep time needs to be less than the maximum sleep
 * time. If these condition(s) are incorrect, the corresponding error
 * message is printed to the terminal. If all conditions are 
 * satisfied, the philosopher thread is put to sleep, relevant
 * information is printed, and the function returns. 
 * 
 * @param philosopher_number The philosopher's unique number, which
 *        represents his location at the table
 * @param min The minimum amount of time the thread needs to sleep for
 * @param max The maximum amount of time a thread can sleep for
 * @return Integer corresponding to the success of the function
 *         '0' = SUCCESS
 *         '1' = FAIL
 */
int think(int philosopher_number, int min, int max) {

    // If minimum time is greater than or equal to 0:
    if (min >= 0) {
        // Print relevant information to the terminal
        print_information(TEXT_THINKING, philosopher_number);
        // Corresponding philosopher thread is put to sleep
        sleep((rand() % max) + min);
        return SUCCESS;
    }

    // If minimum time is greater than maximum time:
    if (max < min) {
        // Print error message to the terminal
        printf("ERROR: Minimum sleep time needs to be less than\n");
        printf("       maximum sleep time\n");
        printf("\n");
        return FAIL;
    }

    // If minimum time is less than 0, print error message:
    printf("ERROR: Minimum sleep time needs to be greater than or\n");
    printf("       or equal to 0\n");
    printf("\n");
    return FAIL;
}

/**
 * Prints information about the status of the philosophers and forks
 * 
 * Based on the argument, information about a philosopher and his
 * forks are printed to the terminal. The options are:
 *   TEXT_NOTHING  = 0 
 *     - Prints nothing to the terminal
 *   TEXT_VISUAL   = 1 
 *     - Prints an ASCII art drawing of the dining table,
 *       philosophers, and forks. Each element is updated according
 *       to the forks array
 *   TEXT_PICKUP   = 2
 *     - Prints information about a philosopher acquiring his
 *       corresponding forks. The philosopher is eating.
 *   TEXT_RETURN   = 3
 *     - Prints information about philosopher returning his
 *       corresponding forks. The philosopher has finished eating.
 *   TEXT_THINKING = 4
 *     - Prints that a philosopher has started thinking
 * All other options are invalid; an error message is printed
 *
 * @param format_specifier 
 * @param philosopher_number The philosopher's unique number, which
 *        represents his location at the table
 * @return Integer corresponding to the success of the function
 *         '0' = SUCCESS
 *         '1' = FAIL
 */
int print_information(int format_specifier, int philosopher_number) {

    if (format_specifier == TEXT_NOTHING) {
        // Prints nothing and returns
        return SUCCESS;
    } else if (format_specifier == TEXT_VISUAL) {
        // Prints a visual representation of the dining philosophers
        //   in ASCII art
        print_special_array(TRUE);
    } else if (format_specifier == TEXT_PICKUP) {
        // Prints information about philosopher acquiring forks
        printf("Philosopher #%d Got His Forks %s\n", 
            philosopher_number,
            "& Has Started Eating");
        print_array(TRUE);
    } else if (format_specifier == TEXT_RETURN) {
        // Prints information about philosopher releasing forks
        printf("Philosopher #%d Is Done Eating %s\n", 
            philosopher_number,
            "& Puts His Forks Back");
        print_array(TRUE);
    } else if (format_specifier == TEXT_THINKING) {
        // Prints information about philosopher thinking
        printf("\tPhilosopher #%d Is Now Thinking\n", 
            philosopher_number);
        printf("\n");
        //print_array(TRUE);
    } else {
        // All invalid options fall here; an error message is printed
        printf("ERROR: This is not a valid printing option\n");
        return FAIL;
    }

    return SUCCESS;
}

/**
 * Checks the starting variables to ensure consistency
 * 
 * If in an invalid number of philosophers is specified, this function
 * will detect it, print the corresponding error message, and then
 * return an integer indicating failure. For the function to succeed,
 * the number of philosophers needs to be between 2 and 20, inclusive.
 * Note: 20 is the allowed maximum number of threads. This can easily
 * be changed 
 * 
 * @return Integer corresponding to the success of the function
 *         '0' = SUCCESS
 *         '1' = FAIL
 */
int check_variables(void) {

    // If total number of philosophers is negative
    if (NUMBER_OF_PHILOSOPHERS < 0) {
        printf("\n");
        printf("ERROR: Number of Philosophers set to (%d)\n", 
            NUMBER_OF_PHILOSOPHERS);
        printf("       This is not physically possible!\n");
        printf("\n");
        return FAIL;
    }

    // If total number of philosophers is 0
    if (NUMBER_OF_PHILOSOPHERS == 0) {
        printf("\n");
        printf("This is some big brain thinking. You can't have\n");
        printf("any concurrency problems if you don't have any\n");
        printf("philosophers. Nice try, but this is not valid!\n");
        printf("\n");
        return FAIL;
    }

    // If total number of philosophers is 1
    if (NUMBER_OF_PHILOSOPHERS == 1) {
        printf("\n");
        printf("ERROR: There are no concurrency problems with\n");
        printf("       one philosopher. This is because he does\n");
        printf("       not need to share forks/food with anyone!\n");
        printf("\n");
        return FAIL;
    }

    /*
     * Even though many threads can be created, this check was
     * added because the creation of too many threads can result in
     * blocked system calls.
     */

    // If total number of philosophers is greater than the allowed max
    if (NUMBER_OF_PHILOSOPHERS > MAX_NUMBER_OF_THREADS) {
        printf("\n");
        printf("ERROR: There are way too many philosophers\n");
        printf("       Please lower the number of philosophers,\n");
        printf("       and try again!");
        printf("\n");
        return FAIL;
    }

    // If total number of philosophers is between 2 and 20, inclusive:
    return SUCCESS;
}

/**
 * Populates the fork-array based on the total number of forks
 * 
 * All elements in the fork-array are changed to '1' via a for-loop.
 * The number of elements in the fork-array depends on the total
 * number of philosophers. At the end of the for-loop, the iterations
 * are checked to ensure that the fork-array was properly populated.
 * If this check fails, an error message is printed to the terminal.
 * 
 * @return Integer corresponding to the success of the function
 *         '0' = SUCCESS
 *         '1' = FAIL
 */
int add_forks(void) {

    int i = 0;

    // Iterate from 0 to total number of forks
    for (; i < NUMBER_OF_FORKS; i++) {
        // The `i'th` index is changed to '1'
        FORK_ARRAY[i] = 1;
    }

    // If total number of iterations equals total number of forks:
    if (i == NUMBER_OF_FORKS) {
        return SUCCESS;
    }

    // If the fork-array wasn't properly populated, print message:
    printf("\n");
    printf("ERROR: There was a problem adding forks to the array\n");
    printf("       Please re-run the program/simulator!\n");

    return FAIL;
}

/**
 * Prints the fork-array to the terminal
 *
 * The fork-array, which represents the availability of forks on the
 * dining table, is printed to the terminal in the format: [x,x,x]
 * A for-loop is used to iterate through the fork-array, and print
 * each element. An if-statement is used to not print an extra comma
 * at the end of the array. An extra newline can be printed at the
 * end. 
 *
 * @param print_extra_newline Integer flag to indicate if an extra
 *        newline should be printed at the end of the array
 * @return 0
 */
int print_array(int print_extra_newline) {

    // Iterate through number of forks, which is the size of the array
    printf("[");
    for (int i = 0; i < NUMBER_OF_FORKS; i++) {
        // Print element at `i'th` index
        printf("%d", FORK_ARRAY[i]);
        if (i < (NUMBER_OF_FORKS - 1)) {
            // Only print a comma and space if `i` is not last element
            printf(", ");
        }
    }
    printf("]\n");

    // Print extra newline if specified in the argument
    if (print_extra_newline) {
        printf("\n");
    }

    return SUCCESS;
}

/**
 * Prints an ASCII art representation of the dining philosophers
 * 
 * Using only ASCII symbols/characters, the dining table with
 * philosophers and their corresponding forks are printed to the
 * terminal. The forks are present or absent based on which
 * philosopher(s) is eating. This information is inferred from the
 * fork-array, and evaluation takes place via the ternary operator.
 * Note: This only works if there is a total number of 5 philosophers.
 * Anything else will result in an error. This function can prompt the
 * user to press <ENTER> to continue execution. 
 *
 * Philosophers are represented as:
 *    =====     =====     =====
 *    =P_0=     =P_2=     =P_4=
 *    =====     =====     =====
 *
 * Forks are represented as:
 *    |---|     |---|
 *    | 1 |     | 0 |
 *    |---|     |---|
 *
 * 
 * @param stall_enabled Integer to specify if user input is needed
 *        to continue execution
 * @return Integer corresponding to the success of the function
 *         '0' = SUCCESS
 *         '1' = FAIL
 */
int print_special_array(int stall_enabled) {

    // If the total number of philosophers is not 5:
    if (NUMBER_OF_PHILOSOPHERS != 5) {
        // Print error message and return to caller
        printf("ERROR: This printing function only works if there\n");
        printf("       are %d philosophers in total!\n", 
            NUMBER_OF_PHILOSOPHERS);
        return FAIL;
    }
 
    // The ASCII art representation of the dining philosophers    
    printf("   =====    |---|    =====   \n");
    printf("   =P_0=    | %c |    =P_1=   \n",
                  // Fork #0
        FORK_ARRAY[0] == 1 ? FORK_PRESENT : FORK_ABSENT);
    printf("   =====    |---|    =====   \n");
    printf("                             \n");
    printf("|---|                   |---|\n");
    printf("| %c |                   | %c |\n", 
      // Fork #4                  Fork #1
        FORK_ARRAY[4] == 1 ? FORK_PRESENT : FORK_ABSENT,
        FORK_ARRAY[1] == 1 ? FORK_PRESENT : FORK_ABSENT);
    printf("|---|                   |---|\n");
    printf("                             \n");
    printf("=====                   =====\n");
    printf("=P_4=                   =P_2=\n");
    printf("=====                   =====\n");
    printf("                             \n");
    printf("     |---|         |---|     \n");
    printf("     | %c |         | %c |     \n",
        //    Fork #3        Fork #2
        FORK_ARRAY[3] == 1 ? FORK_PRESENT : FORK_ABSENT,
        FORK_ARRAY[2] == 1 ? FORK_PRESENT : FORK_ABSENT);
    printf("     |---|         |---|     \n");
    printf("                             \n");
    printf("            =====            \n");
    printf("            =P_3=            \n");
    printf("            =====            \n");
    printf("                             \n");

    if (stall_enabled) {
        // Prompt user to press a key to continue
        printf("Press <ENTER> To Continue\n");  
        getchar(); 
    } else {
        // Print divider to separate each step
        printf("-----------------------------\n\n");
    }

    return SUCCESS;
}

/*
 * Print greeting message when 'main()' is executed
 *
 * @return 0
 */
int print_greeting_message(void) {

    printf("\n");
    printf("##################\n");
    printf("##  Welcome To  ##\n");
    printf("##  The Dining  ##\n");
    printf("## Philosophers ##\n");
    printf("##  Simulator!  ##\n");
    printf("##################\n");
    printf("\n");

    return SUCCESS;
}

/*
 * Print farewell message just before 'main()' is terminated
 *
 * @return 0
 */
int print_farewell_message(void) {

    //printf("\n");
    printf("##################\n");
    printf("## End Of Code; ##\n");
    printf("##  Thanks For  ##\n");
    printf("##   Using The  ##\n");
    printf("##  Simulator!  ##\n");
    printf("##################\n");
    printf("\n");

    return SUCCESS;
}

/*

 |-----------------|
 | DEPRECATED CODE |
 |-----------------|
 | Ignore Every-   |
 | thing below     |
 |-----------------|
 
int print_array(void) {

    printf("[1");
    for (int i = 1; i < NUMBER_OF_FORKS; i++) {
        printf(", %d", FORK_ARRAY[i]);
    }
    printf("]\n");

    return 0;
}

void print_special_array(void) {

    // condition ? value_if_true : value_if_false

    FORK_ARRAY[0] = 0;
    FORK_ARRAY[1] = 0;
    FORK_ARRAY[2] = 1;
    FORK_ARRAY[3] = 0;
    FORK_ARRAY[4] = 0;

    printf("=====   |---|   =====\n");
    printf("=P_0=   | %s |   =P_1=\n", 
        FORK_ARRAY[0] == 1 ? FORK_PRESENT : FORK_ABSENT);
    printf("=====   |---|   =====\n");
    printf("                     \n");
    printf("|---|           |---|\n");
    printf("| %s |           | %s |\n", FORK_PRESENT, FORK_PRESENT);
    printf("|---|           |---|\n");
    printf("                     \n");
    printf("=====           =====\n");
    printf("=P_5=           =P_2=\n");
    printf("=====           =====\n");
    printf("                     \n");
    printf("|---|           |---|\n");
    printf("| %s |           | %s |\n", FORK_PRESENT, FORK_PRESENT);
    printf("|---|           |---|\n");
    printf("                     \n");
    printf("=====   |---|   =====\n");
    printf("=P_4=   | %s |   =P_3=\n", FORK_PRESENT);
    printf("=====   |---|   =====\n");

    // press any key to continue

    printf("   =====    |---|    =====   \n");
    printf("   =P%c0=    | %c |    =P%c1=   \n", 
        (FORK_ARRAY[4] == 0 && FORK_ARRAY[0] == 0) ? EAT : THINK,
        FORK_ARRAY[0] == 1 ? FORK_PRESENT : FORK_ABSENT,
        (FORK_ARRAY[0] == 0 && FORK_ARRAY[1] == 0) ? EAT : THINK);
    printf("   =====    |---|    =====   \n");
    printf("                             \n");
    printf("|---|                   |---|\n");
    printf("| %c |                   | %c |\n", 
        FORK_ARRAY[4] == 1 ? FORK_PRESENT : FORK_ABSENT,
        FORK_ARRAY[1] == 1 ? FORK_PRESENT : FORK_ABSENT);
    printf("|---|                   |---|\n");
    printf("                             \n");
    printf("=====                   =====\n");
    printf("=P%c4=                   =P%c2=\n",
        (FORK_ARRAY[3] == 0 && FORK_ARRAY[4] == 0) ? EAT : THINK,
        (FORK_ARRAY[2] == 0 && FORK_ARRAY[3] == 0) ? EAT : THINK);
    printf("=====                   =====\n");
    printf("                             \n");
    printf("     |---|         |---|     \n");
    printf("     | %c |         | %c |     \n",
        FORK_ARRAY[3] == 1 ? FORK_PRESENT : FORK_ABSENT,
        FORK_ARRAY[2] == 1 ? FORK_PRESENT : FORK_ABSENT);
    printf("     |---|         |---|     \n");
    printf("                             \n");
    printf("            =====            \n");
    printf("            =P%c3=            \n",
        (FORK_ARRAY[2] == 0 && FORK_ARRAY[3] == 0) ? EAT : THINK);
    printf("            =====            \n");
    printf("                             \n");

    return;
}

int print_information(int format_specifier, int text_specifier,
                      int philosopher_number) {

    if (format_specifier == 0) {
        if (text_specifier == 0) {
            printf("Philosopher #%d Got His Forks%s \n", 
                philosopher_number,
                "& Has Started Eating");
        } else if (text_specifier == 1) {
            printf("Philosopher #%d Is Done Eating%s \n", 
                philosopher_number,
                "& Puts His Forks Back");
        } else if (text_specifier == 2) {
            printf("\tPhilosopher #%d Is Now Thinking\n", 
                philosopher_number);
            printf("\n");
        } else {
            printf("ERROR: Not a valid print-option!\n");
            return 1;
        }
        return 0;
    } else if (format_specifier == 1) {
        print_special_array(TRUE);
        return 0;
    } else if (format_specifier == 2) {
        print_array(TRUE);
        return 0;
    }

    printf("ERROR: Not a valid print-option!\n");
    return 1;
}

    printf("\tPhilosopher #%d Tried To Get His Forks\n",
        philosopher_number);
    printf("\n");

 */