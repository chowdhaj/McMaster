/**
 * sorting.c
 *
 * C program that uses multi-threading to sort a small list. It does
 * this by creating 3 threads. The first 2 threads are used to sort
 * one half of the list via bubble sort. The 3rd thread is used to
 * merge the two sorted sub-arrays into one sorted array. The sorting
 * algorithm can only handle numbers, and it can sort any int array. 
 * Structs are used to pass data to all the threads. The memory that
 * these structs occupy is not freed up before the 'main' thread
 * terminates.
 * Note: This program was created for educational purposes only.
 *
 * The makefile must be used to compile this program.
 *
 * Author: Jatin Chowdhary
 * Code borrowed from Operating System Concepts - 10th Edition
 *
 * License: GPL
 */

#include <pthread.h>  // Include 'pthread' library
#include <stdio.h>    // Include standard I/O library
#include <stdlib.h>   // Include standard library definitions

#define SIZE_ARRAY         10  // Define a constant number: 10
#define NUMBER_OF_THREADS  3   // Define a constant number: 03

// Prototype for thread that performs basic sorting algorithm
void *sorter(void *params);

// Prototype for thread that performs merging of results
void *merger(void *params);

// Initialize unsorted int array
int unsorted_arr[SIZE_ARRAY] = {7, 12, 19, 3, 18, 4, 2, 6, 15, 8};

// Declare int array; this will store the sorted array
int sorted_arr[SIZE_ARRAY];

// struct definition; used to store indices in array
typedef struct {
    int from_index;
    int to_index;
} parameters;

int main(int argc, const char *argv[]) {

    printf("BEGIN\n");

    int i;

    pthread_t workers[NUMBER_OF_THREADS];

    /* Establish the first sorting thread */

    // Declares and allocates space for parameters struct
    parameters *data = (parameters *) malloc(sizeof(parameters));
    // Note: structs are the only way to pass multiple types of data
    //       to a threaded function. This is because the
    //       'pthread_create' function does not allow more than 4
    //       arguments

    // Sets the 'from_index' variable to 0
    data->from_index = 0;

    // Sets the 'to_index' variable
    data->to_index = (SIZE_ARRAY / 2) - 1;

    /*
     * Sort the first half of the array on thread #1
     * 
     * The 'pthread_create()' function is used to create a thread
     * This thread is used to sort the first half of the array
     * 
     * &workers[0] :: The data type that stores the reference to the
     *                thread; it will store the ID of the thread.
     * 0           :: Uses default attributes when creating thread
     * sorter      :: The 'main' function that the thread will run. A
     *                pointer to the function is passed
     * data        :: The argument for the 'sorter' function. A
     *                pointer to 'data' is passed
     */
    pthread_create(&workers[0], 0, sorter, data);

    //printf("start index: %i, end index: %i\n", 
    //    data->from_index, data->to_index);

    /*
     * Establish the second sorting thread
     * 
     * Declares and allocates NEW space for the parameters struct
     * The old 'data' struct is not deleted, and is still in memory
     * This new memory space is different from the old one
     *
     * Note: In the real world, this is bad coding practice, because
     *       this can lead to memory leaks and other issues. Avoid
     *       dangling pointers, and always free up memory when you're
     *       done using it
     */
    data = (parameters *) malloc(sizeof(parameters));
    data->from_index = (SIZE_ARRAY / 2);
    data->to_index = SIZE_ARRAY - 1;

    // Sort the second half of the array on thread #2
    pthread_create(&workers[1], 0, sorter, data);
    // Note: The 'data' argument is not the same as the argument that
    //       was supplied to the first thread

    /* 
     * Now wait for the 2 sorting threads to finish
     * The 'pthread_join()' function suspends execution of the calling
     *   thread, until the target thread terminates. In other words,
     *   the two threads running the 'sorter' function are not
     *   terminated until the 'main' thread terminates. 
     * 
     * workers[i] :: Refers to the specific thread in the 'pthread'
     *               array. The 'pthread' ID is used
     * NULL       :: No return value associated to the 'sorter' thread
     */

    for (i = 0; i < (NUMBER_OF_THREADS - 1); i++) {
        pthread_join(workers[i], NULL);
    }

    /* Establish the merge thread */
    data = (parameters *) malloc(sizeof(parameters));
    data->from_index = 0;
    data->to_index = (SIZE_ARRAY / 2);

    /* Execute the merge thread */
    pthread_create(&workers[2], 0, merger, data);

    /* Wait for the merge thread to finish */
    pthread_join(workers[2], NULL);

    /* Output unsorted array */
    for (i = 0; i < SIZE_ARRAY; i++) {
        printf("%d  ", unsorted_arr[i]);
    }
    printf("\n");

    /* Output sorted array */
    for (i = 0; i < SIZE_ARRAY; i++) {
        printf("%d  ", sorted_arr[i]);
    }
    printf("\nEND\n");

    return 0;
}

/**
 * Sorting Thread
 *
 * This thread can essentially use any algorithm for sorting
 */
void *sorter(void *params) {

    // Deferences the void argument that is supplied to the function
    parameters *p = (parameters *)params;

    int i;
    int begin = p->from_index;
    int end   = p->to_index;

    // Print debugging information
    //printf("start index: %i, end index: %i\n", begin, end);

    int swapped = 1;
    int j = 0;
    int temp;

    // Bubble Sort
    while (swapped == 1) {
        swapped = 0;
        j++;

        for (i = begin; i <= end - j; i++) {
            if (unsorted_arr[i] > unsorted_arr[i+1]) {
                temp = unsorted_arr[i];
                unsorted_arr[i] = unsorted_arr[i+1];
                unsorted_arr[i+1] = temp;
                swapped = 1;
            }
        }
    }
    pthread_exit(0);
}

/**
 * Merge Thread
 *
 * Uses simple merge sort for merging two sorted sub-arrays
 */
void *merger(void *params) {

    parameters *p = (parameters *) params;

    int i, j;

    i = p->from_index;
    j = p->to_index;

    /* Position being inserted into sorted array */
    int position = 0;

    while(i < p->to_index && j < SIZE_ARRAY) {
        if (unsorted_arr[i] <= unsorted_arr[j]) {
            sorted_arr[position++] = unsorted_arr[i];
            i++;
        } else {
            sorted_arr[position++] = unsorted_arr[j];
            j++;
        }
    }

    /* Copy the remainder */
    if (i < p->to_index) {
        while (i < p->to_index) {
            sorted_arr[position] = unsorted_arr[i];
            position++;
            i++;
        }
    } else {
        while (j < SIZE_ARRAY) {
            sorted_arr[position] = unsorted_arr[j];
            position++;
            j++;
        }
    }
    pthread_exit(0);
}
