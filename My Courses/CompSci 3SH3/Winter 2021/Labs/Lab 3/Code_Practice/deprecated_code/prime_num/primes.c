#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>

// Global variable
int prime;

// Prototypes for helper functions
int is_prime(int num);
int check_arguments(int argc);
int check_number(int num);
int did_fail(int code);

// Prototype for thread function
void *thread_function_print_primes();

int main(int argc, char *argv[]) {
    
    if (check_arguments(argc)) {
        return 1;
    }
    
    printf("Prime Number Calculator\n");
    prime = atoi(argv[1]); // Convert str to int
    
    if (check_number(prime)){
        return 1;
    }
    
    printf("Computing all primes up to: %d\n", prime);

    pthread_t thread_primes;

    // Create thread and check exit code
    if (did_fail(pthread_create(&thread_primes, NULL,
        thread_function_print_primes, NULL))) {
    
        printf("ERROR: Thread creation went awol\n");
    }

    // Join thread and check exit code
    if (did_fail(pthread_join(thread_primes, NULL))) {
        printf("ERROR: Thread failed to join\n");
    }

    printf("END\n");

    return 0;

}

// Thread function for printing primes
void *thread_function_print_primes() {

    pthread_t id = pthread_self();

    printf("The prime numbers are:\n");
    for (int i = 2; i <= prime; i++) {
        if (is_prime(i)) {
            printf("%d, ", i);
        }
    }

    printf("\nThread #%lu finished\n", id);

    return 0;
}

// Checks status code to see if function failed
int did_fail(int code) {
    
    if (code == -1) {
        return 1;
    }
    return 0;
}

// Checks number to see if its greater than or equal to 2
// This is used for checking the initial number
int check_number(int num) {
    
    if (num >= 2) {
        return 0;
    } else {
        printf("%d is not a valid number\n", num);
    }
    return 1;
}

// Checks the argument number to see if valid number of
// arguments was entered
int check_arguments(int argc) {
    
    if (argc == 2) {
        return 0;
    } else {
        printf("Incorrect number of arguments\n");
    }
    
    return 1;
    
}

/*
 * This is my prime number calculator. It checks if a 
 * number is a prime number. The most important part of
 * this function is the for loop that can calculate if
 * a number is prime or not. It iterates from 23 to the
 * square root of the number and tries to find a factor
 * 
 * In my quest to speed up this algorithm, I thought
 * that hardcoding some known primes would help. However,
 * the speed up is inconsequential because it only helps
 * for small prime numbers under 323. Large primes are 
 * unaffected by the switch statement.
 * 
 * In the future, a better approach would be to save known
 * primes in a list and traverse it. However, the list cannot
 * get to large otherwise it will drain the memory.
 */
int is_prime(int num) {

    switch (num) {
        case 2:
        case 3:
        case 5:
        case 7:
        case 11:
        case 13:
        case 17:
        case 19:
            return 1;
        default:
            if ((num % 2  == 0) || (num % 3  == 0) ||
                (num % 5  == 0) || (num % 7  == 0) ||
                (num % 11 == 0) || (num % 13 == 0) ||
                (num % 17 == 0) || (num % 19 == 0)) {
                    return 0;
            } else {
                int sr = sqrt(num) + 1;
                for (int i = 23; i <= sr; i++) {
                    if (num % i == 0) {
                        return 0;
                    }
            }
        }
    }

    return 1;
}
