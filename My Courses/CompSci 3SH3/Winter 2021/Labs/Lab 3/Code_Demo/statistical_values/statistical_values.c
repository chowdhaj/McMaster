/**
 * statistical_values.c
 *
 * C program that computes statistical values (i.e. Average, Maximum,
 * Minimum) for a series of numbers that are provided as arguments to
 * 'main()'. Each value is computed on its own thread. The program
 * is designed to be easily extendable, allowing developers to easily
 * implement more functions to compute other statistical values. The
 * program checks and sanitizes the input. If an error does occur, it
 * will indicate where and why. More information is found below via
 * comments; single-line and multi-line.
 * 
 * Note: The execessive comments are for learning purposes.
 *
 * The makefile must be used to compile this program.
 *
 * Author: Jatin Chowdhary
 * Code borrowed from Operating System Concepts - 10th Edition
 *
 * License: GPL
 */

#include <stdlib.h>  // Include Standard C Library
#include <stdio.h>   // Include Standard I/O Library
#include <pthread.h> // Include 'pthread' Library For Threading

#define NUM_OF_THREADS  3 // Define constant 3 for thread array size
#define BASE_TEN       10 // Define constant 10 to represent base
#define TRUE            1 // Define constant 1, to represent true
#define FALSE           0 // Define constant 0, to represent false

// Prototypes for helper functions
// All functions are defined below the 'main()' function
int check_input_size(int argc);
int print_greeting_message(void);
int calculate_array_size(int argc);
int print_preliminary_information(int size);
int print_array(int arr[], int size);
int print_farewell_message(void);
int convert_to_int_array(char *argv[], int argc, 
    int int_array[], int size);

// Prototypes for threaded functions
void *calculate_average(void *arr);
void *calculate_maximum(void *arr);
void *calculate_minimum(void *arr);

// Global variable
// This is the size of the input array
int SIZE = 0;

int main(int argc, char * argv[]) {

    // Checks if size of input is valid, and if it is:
    if (check_input_size(argc)) {
        // Print message
        print_greeting_message(); 
        // Calculate size of array
        calculate_array_size(argc);
        // Print information
        print_preliminary_information(SIZE);
    } else {
        // If size of input is not valid, then exit
        return 1;
    }

    // Declare int-array to store char-array 'argv'
    int int_array[SIZE];

    // Copies elements from the char-array into the int-array
    if (convert_to_int_array(argv, argc, int_array, SIZE)) {
        // If the operation is not successful, due to bad input, exit
        return 1;
    }

    // Declare 'pthread_t' array
    pthread_t threads_stats[NUM_OF_THREADS];

    // Declare int-array
    int exit_status_code[NUM_OF_THREADS];

    /*
     * Initialize void pointer array, and store address of the
     *   threaded functions
     * Index #1 corresponds to the 'average' thread
     * Index #2 corresponds to the 'maximum' thread
     * Index #3 corresponds to the 'minimum' thread
     */
    void *func_ptr[NUM_OF_THREADS] = {
        &calculate_average, &calculate_maximum, &calculate_minimum
    };

    /*
     * Iterate over 'NUM_OF_THREADS' via for-loop.
     * For each iteration, create a thread, via 'pthread_create()' and
     *   run its respective threaded function.
     * The exit status code of 'pthread_create()' is checked for each
     *   threaded function that is created in the for-loop. If the
     *   exit code is not zero, then an error has occurred.
     * The arguments supplied to 'pthread_create()' are: 
     *   &threads_stats[i]  :: Stores the ID of the thread
     *   NULL               :: Thread uses default attributes
     *   func_ptr[i]        :: Pointer to the function to execute
     *   (void *) int_array :: Argument supplied to the function
     */
    for (int i = 0; i < NUM_OF_THREADS; i++) {

        // Create thread
        exit_status_code[i] = 
            pthread_create(&threads_stats[i], NULL,
                func_ptr[i], (void *) int_array);

        // Check exit code
        if (exit_status_code[i] != 0) {
            printf("ERROR: Failed To Create Thread #%d\n", i);
        }
    } 

    /*
     * Iterate over 'NUM_OF_THREADS' via for-loop.
     * For each iteration, join the corresponding thread in the
     *   'pthread_t' array with the 'main()' thread. This ensures
     *   that 'main()' will wait for the thread to finish before 
     *   terminating. The function 'pthread_join()' is used to 
     *   prevent the premature termination of threads. 
     * The exit status code for 'pthread_join()' is checked for each
     *   threaded function in the 'pthread_t' array. 
     */
    for (int i = 0; i < NUM_OF_THREADS; i++) {

        // Join thread
        exit_status_code[i] = pthread_join(threads_stats[i], NULL);

        // Check exit code
        if (exit_status_code[i] != 0) {
            printf("ERROR: Failed To Join Thread #%d\n", i);
        }
    }

    // Print final message to indicate end of execution
    print_farewell_message();

    // Main thread terminates
    return 0;
}

/**
 * Calculates the average of a given array
 *
 * The average of the array is calculated by summing up all the
 * elements in the array, and then dividing the total sum by the
 * number of elements in the array. The result is stored as a float,
 * and printed to the terminal.
 *
 * @params *arr Void pointer to the array containing data/numbers
 * @return NULL
 */
void *calculate_average(void *arr) {

    int sum = 0;
    float average = 0.0;

    // Deference void pointer and convert it to an int-array pointer
    int *int_array = (int *) arr;

    // Iterate through array containing data, and sum up elements
    for (int i = 0; i < SIZE; i++) {
        sum += int_array[i];
    }

    // Divide the sum by the size of the array
    average = ((sum * 1.0) / SIZE);

    // Print results to the terminal
    printf("The average value is: %.2f\n", average);

    // Terminate 'average' thread
    pthread_exit(0);
}

/**
 * Calculates the maximum element in an array
 * 
 * The maximum element in the array is located by iterating through
 * the entire array and comparing it with a previously stored value.
 * If the next element is greater than the current element, then
 * the maximum value is updated. This process is done for the entire
 * array
 *
 * @param *arr Void pointer to the array containing data/numbers
 * @return NULL
 */
void *calculate_maximum(void *arr) {

    // Deference void pointer and convert it to an int-array pointer
    int *int_array = (int *) arr;    

    // Assign first value in array to temporary variable
    int maximum = int_array[0];

    // Iterate through the entire array, and locate the max
    for (int i = 1; i < SIZE; i++) {
        // If value in temporary variable is less than the value in
        //   the `i'th` index of the array
        if (maximum < int_array[i]) {
            maximum = int_array[i]; // A new maximum value is found
        }
    }

    // Print results to terminal
    printf("The maximum value is: %d\n", maximum);

    // Terminate 'maximum' thread
    pthread_exit(0);
}

/**
 * Calculates the minimum element in an array
 * 
 * The minimum element in the array is located by iterating through
 * the entire array and comparing it with a previously stored value.
 * If the next element is smaller than the current element, then
 * the minimum value is updated. This process is done for the entire
 * array
 *
 * @param *arr Void pointer to the array containing data/numbers
 * @return NULL
 */
void *calculate_minimum(void *arr) {

    // Deference void pointer and convert it to an int-array pointer
    int *int_array = (int *) arr;    

    // Assign first value in array to temporary variable 
    int minimum = int_array[0];

    // Iterate through the entire array
    for (int i = 1; i < SIZE; i++) {
        // If the temporary variable is greater than the value at
        //   the `i'th` position in the array
        if (minimum > int_array[i]) {
            minimum = int_array[i]; // A new minimum value is found
        }
    }

    // Print results to terminal
    printf("The minimum value is: %d\n", minimum);

    // Terminate 'minimum' thread
    pthread_exit(0);
}

/**
 * Checks the size if the input arguments
 *
 * The size of the char-array (input) is checked. If the size of the
 * array is greater than 1, then 1 is returned. Alternatively, if the
 * size of the array is less than or equal to 1, then an error
 * message is printed to the terminal, and the function returns 0
 *
 * @param argc The number of elements in the input-ed array
 * @return An integer indicating the success of the function. 
 *           '1' = Success
 *           '0' = Failed
 */
int check_input_size(int argc) {

    // If greater than 1
    if (argc > 1) {
        return 1; // Success
    } else { // If less than or equal to 1
        // Print error message
        printf("ERROR: Invalid Number Of Arguments Supplied\n");
        printf("       You need to provide more than %d arguments\n",
                       (argc - 1));
    }

    return 0; // Failure
}

/**
 * Print greeting message
 *
 * @return Integer value: 0
 */
int print_greeting_message(void) {

    printf("\n");
    printf("||===============||\n");
    printf("|| Welcome To My ||\n");
    printf("|| Statistics    ||\n");
    printf("|| Calculator    ||\n");
    printf("||===============||\n");
    printf("\n");

    return 0;
}

/**
 * Calculates the size of the int-array
 *
 * The size of the integer array is calculated by subtracting the
 *   size of the char-array by 1. This value is stored in a global
 *   int.
 * The size of the int-array is one less than the size of the char
 *   array, because the first element in the char-array is not valid;
 *   only the subsequent elements are. Thus, 1 is subtracted from the
 *   size of the char-array.
 *
 * @param argc The size of the char-array
 * @return Integer value: 0
 */
int calculate_array_size(int argc) {

    SIZE = (argc - 1);
    return 0;
}

/**
 * Prints the size (number) of the int-array
 * 
 * The size of the int-array is printed to the terminal. The size
 * of the array determines what message is printed to the terminal.
 * This is because of singular and plural words; entry VS. entries. 
 * 
 * @param size The size of the int-array
 * @return Integer value: 0
 */
int print_preliminary_information(int size) {

    // If size is equal to 1
    if (size == 1) {
        // Print singular form of 'entry'
        printf("There is 1 entry: ");
    } else { // If size is 0, or greater than 1:
        // Print plural form of 'entry' 
        printf("There are %d entries:\n", size);
        //printf("\n");
    }

    return 0;
}

/**
 * Converts the char-array into an int-array
 * 
 * Iterates through the (size of) int-array. The value at `i + 1`
 * in the char-array is converted into an int, and copied to the
 * `i'th` value in the int-array. If this value is not an int,
 * then an error message is printed to the terminal, and the function
 * terminates with an exit code of 1. Alternatively, if there are
 * no problems with any char-conversions, then the function terminates
 * with an exit code of 0.
 * 
 * @param *argv[] The char-array
 * @param argc The size of the char-array
 * @param int_array[] The int-array
 * @param size The size of the int-array
 * @return An integer indicating the success of the function. 
 *           '1' = Success
 *           '0' = Failed
 */
int convert_to_int_array(char *argv[], int argc, 
                         int int_array[], int size) {

    long temp_value = 0;
    char *end_ptr;

    // Iterate through (size of) int-array
    for (int i = 0; i < size; i++) {

        /* 
         * Convert char at `i + 1` in char-array into an int, and
         *   copy it into a temporary variable. 
         * The character-to-integer conversion is done via the
         *   'strtol' function.
         * Arguments for 'strtol':
         *   argv[i+1] :: The character to be converted to an int;
         *                this is the `i + 1` index of the char-array
         *   &end_ptr  :: If the operation is unsuccessful, the
         *                bad character is stored here
         *   BASE_TEN  :: Specifies the base of the number; base 10
         *                in this case
         */
        temp_value = strtol(argv[i+1], &end_ptr, BASE_TEN);

        // If not NULL:
        if (*end_ptr) {
            // Print error message to terminal
            printf("\n\n");
            printf("ERROR: Could Not Parse Input As Integer\n");
            printf("       Invalid Character: '%c'", *end_ptr);
            printf("\n\n");
            return 1; // Return 1 to indicate failure
        }

        /*
         * Copy and convert the 'long' into an 'int' from the
         * temporary variable into the `i'th` index in the int-
         * array
         */
        int_array[i] = (int) temp_value;

        // Print the integer at the `i'th` index in the int-array
        printf("%d", int_array[i]);

        // Print commas after every element, except for the last one
        if (i != (size - 1)) {
            printf(", ");
        }
    }
    printf("\n\n");

    return 0; // Return 0 to indicate failure
}

/**
 * Prints the specified int-array to the terminal
 *
 * Iterates through the int-array, and prints every element in the
 * array. Once the int-array has been printed, the size of the int-
 * array is printed, and the function terminates.
 * 
 * @param arr[] The int-array to be printed
 * @param size The size of the int-array
 * @return Integer value: 0
 */
int print_array(int arr[], int size) {

    printf("\n");

    // Iterate through the (size of) int-array
    for (int i = 0; i < size; i++) {
        // Print element at `i'th` index
        printf("%d, ", arr[i]);
    }

    // Print size of the array
    printf("\nThe size is: %d\n", size);

    return 0;
}

/**
 * Prints the final message to the terminal
 *
 * @return Integer value: 0
 */
int print_farewell_message(void) {

    printf("\n");
    printf("||===============||\n");
    printf("|| Thank You For ||\n");
    printf("|| Using My      ||\n");
    printf("|| Software!     ||\n");
    printf("||===============||\n");
    printf("\n");

    return 0;
}
