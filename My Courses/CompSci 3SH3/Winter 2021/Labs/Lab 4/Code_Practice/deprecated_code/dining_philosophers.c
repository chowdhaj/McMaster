/*
 * Assumptions:
 * Philosophers (strictly) operate in the following manner:
 *    1) Get forks
 *    2) Eat stuff
 *    3) Release forks
 *    4) Think
 *    5) Repeat
 */

#include <stdlib.h>   // Include Standard Library
#include <stdio.h>    // Include Standard I/O
#include <pthread.h>  // Include pthread Library
#include <stdint.h>   // Include More Data Types
#include <unistd.h>   // Include Sleep Function

#define GLOBAL_SIZE 5 // Defines Size Of Array
#define TRUE        1 // Define True Boole
#define FALSE       0 // Define False Boole

// Declaration For Global Variables & Function Prototypes

// Sleep Flag
int SLEEP_TRUE = 1;

// Array to represent forks
int fork_position[GLOBAL_SIZE];

// Prototypes For Helper Functions
int array_sum_equals_size(int sum_array[], int size);
int spawn_forks(int all_forks[], int size);
int get_left_fork(int philosopher_number);
int get_random_interval(int min, int max);
void return_forks(int philosopher_number);
void pickup_forks(int philosopher_number);
void print_forks(int arr[], int size);

// Prototype For Threaded Function
void *run_philosopher(void *number);

// Initialize Mutexes
pthread_mutex_t fork_mutex      = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  condition_cond  = PTHREAD_COND_INITIALIZER;

int main(void) {

    // Declare and initialize preliminary stuff
    pthread_t philosophers[5];
    uintptr_t philosopher_number[GLOBAL_SIZE] = {0, 1, 2, 3, 4};
    int status[GLOBAL_SIZE];
    srand(time(0));

    // Print fork array
    //print_forks(fork_position, GLOBAL_SIZE); 

    // Populate fork array with 1's in all fields
    if (spawn_forks(fork_position, GLOBAL_SIZE) == 0) {
        printf("%s\n", "Forks are on the table");
        print_forks(fork_position, GLOBAL_SIZE);
    }

    /* 
     * Iterate through size of 'pthread_t' array and create the
     *   corresponding threads. 
     * The result of the exit code is stored in the 'status' array,
     *   and checked to determine if the creation was successful
     *   or unsuccessful.
     */ 
    for (int i = 0; i < GLOBAL_SIZE; i++) {
        if ((status[i] = pthread_create(&philosophers[i], NULL,
            run_philosopher, (void *) philosopher_number[i]))) {
                printf("Failed To Create Philosopher #%lu\n",
                    philosopher_number[i]);
        } 
        // Optional else-block
        //else {
        //    printf("Philosopher #%lu Is Created\n", 
        //        philosopher_number[i]);
        //}
    }

    /*
     * Iterate through size of 'pthread_t' array and wait for them
     *   to finish executing before proceeding to the next statements.
     * The result of the 'pthread_join' function is stored in the
     *   'status' array, and checked to determine if the operation
     *    was successful or not.
     */
    for (int i = 0; i < GLOBAL_SIZE; i++) {
        if ((status[i] = pthread_join(philosophers[i], NULL))) {
            printf("Philosopher #%lu Failed To Finish\n", 
                philosopher_number[i]);
        }
    }

    // End of 'main'
    printf("END\n");
    return 0;
}

// Prints the elements in an array, while being mindful of whitespaces
void print_forks(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
        if (i == (size - 1)) {
            printf("\n");
        }
    }
}

/*
 * Checks to see if the size of the array equals the sum of 
 *   elements in the array. This is useful to determine if the
 *  'forks' array was properly formulated.
 */
int array_sum_equals_size(int sum_array[], int size) {

    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += sum_array[i];
    }

    if (sum == size) {
        return 0;
    }

    return -1;
}

/*
 * Populates the fields of an array with all 1's. This represents
 *   the forks/chopsticks in the Dining Philosophers algorithm
 */
int spawn_forks(int all_forks[], int size) {

    for (int i = 0; i < size; i++) {
        all_forks[i] = 1;
    }
    
    if (array_sum_equals_size(all_forks, size)) {
        return -1;
    }

    return 0;
}

// Calculates the index of the left fork used by a philosopher
int get_left_fork(int philosopher_number) {
    return ((philosopher_number + 1) % GLOBAL_SIZE);
}

// Calculates a random integer between two ints
int get_random_interval(int min, int max) {
    return ((rand() % max) + min);
}

/*
 * Instructs the philosopher - the thread that pertains to him - to
 *   pickup his corresponding forks. A mutex lock is used to ensure
 *   that no other philosopher can use the same forks. 
 */
void pickup_forks(int philosopher_number) {

    int right_fork = philosopher_number;
    int left_fork = get_left_fork(philosopher_number);

    pthread_mutex_lock(&fork_mutex);

    // While the left and right fork of the philosopher is not
    // available, then stall/wait for it
    while ((fork_position[left_fork] &&
            fork_position[right_fork]) == 0) {
        pthread_cond_wait(&condition_cond, &fork_mutex);
    }

    // Indicate in the 'fork' array that the forks are in use
    fork_position[left_fork] = 0;
    fork_position[right_fork] = 0;

    printf("Philosopher #%d is eating with forks %d & %d\n", 
        philosopher_number, right_fork, left_fork);
    print_forks(fork_position, GLOBAL_SIZE);

    // Thread sleeps if debugging is enabled
    if (SLEEP_TRUE) {
        sleep(get_random_interval(1, 2));
    }

    pthread_mutex_unlock(&fork_mutex);
    return;
}

/*
 * Instructs the philosopher - the thread that corresponds to him -
 *   to release the forks that he holds. A mutex lock is used to
 *   protect the critical regions of this function; it is undesirable
 *   to allow other threads to simultaneously access this block.
 */
void return_forks(int philosopher_number) {

    int right_fork = philosopher_number;
    int left_fork = get_left_fork(philosopher_number);

    pthread_mutex_lock(&fork_mutex);

    // Update the 'fork' array because forks have been returned
    fork_position[left_fork] = 1;
    fork_position[right_fork] = 1;
    
    printf("Philosopher #%d has returned forks %d & %d\n", 
        philosopher_number, right_fork, left_fork);

    print_forks(fork_position, GLOBAL_SIZE);

    // If the forks are back in the array, then signal the other
    // threads/philosophers to try and obtain their respective forks
    if (fork_position[right_fork] && fork_position[left_fork]) {
        pthread_cond_signal(&condition_cond);
    }

    pthread_mutex_unlock(&fork_mutex);
    return;
}

// Instructs the philosopher/thread to initiate thinking
void think(int philosopher_number) {

    printf("Philosopher #%d is now thinking\n", philosopher_number);

    // If debugging is enabled then sleep for 1 to 3 seconds
    if (SLEEP_TRUE) {
        sleep(get_random_interval(1, 3));
    }

    return;
}

/*
 * Threaded function that runs the helper functions used by threads
 *   to obtain forks, return forks, think, and decide whether it is
 *   alright to perform these operations.
 * A for-loop is used to repeat the operations 'i' number of times
 */
void *run_philosopher(void *number) {

    // Re-cast philosopher number to int
    int philosopher_number = (int) number;

    for (int i = 0; i < 6; i++) {
        // Dining philosophers operate in the following manner:
        //   Acquire 2 forks/chopsticks, eat food, release the forks,
        //   think for a bit, and repeat.
        pickup_forks(philosopher_number);
        return_forks(philosopher_number);
        think(philosopher_number);
    }

    // Exit the thread and return NULL
    pthread_exit(0);
}
