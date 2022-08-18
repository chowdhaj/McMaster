/**
 * prime_numbers.c
 *
 * C program that takes a command-line input, converts it from a
 * 'char-array' into a 'long', and calculates all primes from 2 up
 * until and including that number. The primes are computed in a
 * separate thread, and not the main thread. Prime numbers are
 * computed via the 'trial division' test, outlined in Wikipedia.
 * However, the technique used in this program is better and more
 * optimized. For example, it skips even numbers entirely and only
 * focuses on odd numbers. More information is found below via
 * comments; single-line and multi-line.
 * 
 * Note: The execessive comments are for learning purposes.
 * Note: This program uses Wikipedia's definition of a prime number
 *       https://en.wikipedia.org/wiki/Prime_number
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
#include <math.h>    // Include C Math Library For Math Functions

#define TRUE   1 // Define constant 1, to represent true
#define FALSE  0 // Define constant 0, to represent false

// Prototypes for helper functions
// All functions are defined below the 'main()' function
int print_greeting_message();
int check_input_size(int argc);
long convert_and_check_input(char * argv);
int print_farewell_message();
int is_prime(long prime);

// Prototypes for threaded functions
void *calculate_primes(void * prime);

// Global variable
const int BASE_TEN = 10;

int main(int argc, char * argv[]) {

    /*
     * Check size of input (number of command line arguments).
     * If there is an incorrect number of arguments, then terminate
     *   the program with a return value of 1.
     */
    if (check_input_size(argc)) {
        return 1;
    }

    long user_input;
    print_greeting_message(); // Print message

    /*
     * Convert and check second argument. This is the number to
     *   calculate primes up to. 
     * If the argument is valid, then it is stored in a 'long'.
     * Alternatively, if the argument is not valid, then the program
     *   terminates with a return value of 1.
     */ 
    if ((user_input = (convert_and_check_input(argv[1]))) < 0) {
        return 1;
    }

    int return_value;
    pthread_t prime_number_thread;

    /*
     * Create thread via 'pthread_create()' to calculate the primes.
     * The arguments for 'pthread_create()' are:
     *   &prime_number_thread :: Store the ID of the thread
     *   NULL                 :: Use default thread attributes
     *   *calculate_primes    :: The threaded function to run
     *   (void *) user_input  :: Void pointer to the argument
     * The return value of 'pthread_create()' is checked to see
     *   whether the thread is successfully created or not. If it
     *   failed, then an error message is printed to the terminal 
     *   and the program exits with a return value of -1.
     *   Furthermore, the return value is assigned to another
     *   variable inside the if-statement.
     */
    if ((return_value 
            = (pthread_create(&prime_number_thread, NULL,
                              *calculate_primes, 
                              (void *) user_input)))) {

        // Print error message if thread was not created
        printf("ERROR: Failed To Create Thread\n");
        printf("       The Program Will Terminate\n");
        return -1;
    }

    /*
     * Join thread with 'main()' via 'pthread_join()'. This ensures
     *   that the thread does not terminate before 'main()' finishes.
     * The arguments for 'pthread_join()' are:
     *   prime_number_thread :: ID of the thread to join
     *   NULL                :: Thread does not have a return type
     * The return value of 'pthread_join()' is checked to see if the
     *   thread was successfully joined with 'main()'. If the
     *   operation failed, then an error message is printed to the
     *   terminal and the program exits with a return value of -1
     */
    if ((return_value = 
        (pthread_join(prime_number_thread, NULL)))) {

        printf("ERROR: Failed To Join Thread With Main\n");
        printf("       The Thread May Not Finish In Time\n");
        return -1;
    }

    // Print final message
    print_farewell_message();

    // Main thread terminates
    return 0;
}

/**
 * Threaded function to compute primes.
 *
 * Iterates from 3 to prime number, and checks if each odd number
 * that lies in between is a prime number or not. The check is
 * carried out by another function. If the number is prime, then
 * it is printed to the terminal.
 *
 * @param *prime_number Void pointer to a 'long' variable containing
 *                      the prime number
 * @return NULL (This function does not return anything)
 */
void *calculate_primes(void * prime_number) {

    // Deference void pointer and convert to 'long' number
    long prime = (long) prime_number;

    printf("Calculating All Primes\n");
    printf("Up To And Including: %li\n", prime);

    printf("\nThe Primes Are:");
    printf("\n2");

    // Iterate from 3 to the prime number in increments of 2
    for (long i = 3; i <= prime; i += 2) {
        // If number is prime:
        if (is_prime(i)) {
            // Then, print number to console
            printf(", %li", i);
        }
    }

    printf("\n");

    // Terminate thread
    pthread_exit(0);
}

/*
 * Calculates whether a number is prime or not.
 * 
 * A given number is tested for primality via the 'trial division'
 * method. The function iterates from 3 to the square root of the
 * given number, in increments of 2, and checks if the original
 * number is divisible by any number in the range. If there is a
 * number that evenly divides the original number, the function
 * returns 0. Otherwise, it returns 1. 
 * 
 * @param prime The primality test is done on this variable
 * @return An integer indicating whether the number is prime or not
 *         '0' = Is Not Prime
 *         '1' = Is Prime
 */
int is_prime(long prime) {

    // Calculate square root of prime number, and add 1
    long prime_sqrt = sqrt(prime) + 1; 

    // Iterate from 3 to square root of prime number, in steps of 2
    for (int i = 3; i < prime_sqrt; i += 2) {
        // If an even divisor is found:
        if ((prime % i) == 0) {
            // Then, return 0
            return 0;
        }
    }

    // If no even divisor is found, then return 1
    return 1; 
}

/**
 * Checks the size (number) of input arguments
 * 
 * The number of arguments input-ed in the command line are checked.
 * If there are exactly 2 arguments, then the function terminates
 * with a value of 0. Otherwise, an error message is printed and the
 * function terminates with a value of 1.
 *
 * @param argc The size/number of input-ed arguments
 * @return Integer corresponding to the number of arguments
 *         '0' = There are exactly 2 arguments
 *         '1' = All other cases
 */
int check_input_size(int argc) {

    if (argc == 2) {
        return 0;
    }

    //printf("\n");
    printf("ERROR: Invalid number of arguments\n");
    printf("       Please provide a single number\n");
    //printf("\n");

    return 1;
}

/**
 * Prints greeting message to terminal
 * 
 * @return 0
 */
int print_greeting_message() {

    printf("\n");
    printf("||===============||\n");
    printf("|| Welcome To My ||\n");
    printf("|| Prime Number  ||\n");
    printf("|| Calculator :) ||\n");
    printf("||===============||\n");
    printf("\n");

    return 0;
}

/**
 * Converts and checks the input from a 'char-array' into a 'long'
 * 
 * The 2nd argument in the command line is converted from a 'char-
 * array' into a 'long' via the 'strtol' function. A character
 * pointer variable is checked to see if the operation is successful.
 * If the input contains invalid characters, then an error message is
 * printed, and the function is terminated with a return value of -2.
 * If the 'char-array' is successfully converted into a 'long', then
 * the number is checked for validity. If it is less than or equal to
 * 1, then an error message is printed (because prime numbers are
 * natural numbers greater than 2), and the function terminates with
 * a return value of -2. If there are no errors, the function returns
 * the converted 'long' value.
 *
 * @param *argv Pointer to the character array
 * @return temp_var If the function is successful, or '-2' if an
 *                  error occurs
 */
long convert_and_check_input(char * argv) {

    char *end_ptr;

    /*
     * Convert 'char-array' to 'long' via 'strtol'
     * The arguments for 'strtol' are:
     *   argv     :: Pointer to the 'char-array' to be converted
     *   &end_ptr :: Address of character; used for errors
     *   BASE_TEN :: Base of the number; base 10 in this case
     */
    long temp_var = strtol(argv, &end_ptr, BASE_TEN);

    // If 'strtol' fails to convert:
    if (*end_ptr) {
        printf("ERROR: Failed To Parse Input\n");
        printf("       '%s' Is Invalid Input\n", end_ptr);
        printf("\n");
        return -2;
    }

    // If the number is less than or equal to 1:
    if (temp_var <= 1) {
        printf("ERROR: (%li) does not fit the criteria of a\n", 
            temp_var);
        printf("       prime number according to Wikipedia\n");
        printf("\n");
        return -2;
    }

    // Return the converted 'long' if no errors occur
    return temp_var;
}

/**
 * Prints farewell message to terminal
 * 
 * @return 0
 */
int print_farewell_message() {

    printf("\n");
    printf("||===============||\n");
    printf("|| Thank You For ||\n");
    printf("|| Using My      ||\n");
    printf("|| Program!      ||\n");
    printf("||===============||\n");
    printf("\n");

    return 0;
}

/*

|-----------------|
| DEPRECATED CODE |
|-----------------|
| IGNORE THIS     |
|-----------------|

int did_fail(int return_value) {

    if (return_value == 0) {
        return 0;
    }

    return -1;
}

int is_prime(long prime) {

    if ((prime % 2) == 0) {
        return 0;
    } else if ((prime % 3) == 0) {
        return 0;
    } else if ((prime % 5) == 0) {
        return 0;
    } else if ((prime % 7) == 0) {
        return 0; 
    } else {
        int prime_sqrt = ((int) sqrt(prime)) + 1;
        for (int i = 11; i <= prime_sqrt; i++) {
            if (prime_sqrt < i) {
                return 0;
            }
            if (prime_sqrt % i == 0) {
                return 0;
            }
        }
    }

    return 1;
}

 */