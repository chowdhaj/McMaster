/**
 * Multi-threaded program that sums up the elements in an array/list.
 * The array consists of 20 natural numbers. It is divided into 2
 * smaller arrays, where the elements are summed up in its own
 * separate thread.
 * 
 * @author Dr. Neerja Mhaskar
 * @author Jatin Chowdhary
 * @course CompSci 3SH3
 * @date February 8th, 2022
 */ 

// STEP 01 : Include all necessary files
// #include ???

// STEP 02 : Define macros, global array, function prototype, etc.
// #define ???
// int list[???] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
// void * ??? (void * ???);

// STEP 03 : Define a data structure to store the indexes of the
//           array.
// HINT    : Use a 'struct'
// typedef struct ??? { ... } ???;

/**
 * Main function creates the threads and passes the required
 * parameters - structs - to each thread. Threads are created and
 * terminated in the main function. In addition, the structs are
 * free'd upon thread completion. Finally, the sum of the numbers is
 * printed to the terminal, before the program is terminated.
 */
int main(int argc, char * argv[]) {

    // STEP 04 : Declare and initialize variables

    // STEP 05 : Create an array of thread identifiers
    // HINT    : Use the `pthread_t` type

    // STEP 06 : Declare attributes for the thread(s)
    // HINT    : Use `pthread_attr_t` and `pthread_attr_init()`
    // NOTE    : Only default attributes are used

    // STEP 07 : Declare and initialize the first struct, and set the
    //           indices to represent the first half of the array.
    // HINT    : The beginning index is the start of the array, and
    //           the last index is the middle of the array

    // STEP 08 : Create a thread to sum up the elements in the first
    //           half of the array.
    // HINT    : Use the (default) attributes from Step 06, the
    //           threaded function defined below, and pass the struct
    //           from Step 07 as the argument.

    // STEP 09 : Declare and initialize the second struct, and set
    //           the indices to represent the latter half of the
    //           array.
    // NOTE    : This is similar to STEP 07.

    // STEP 10 : Create another thread to sum up all the elements
    //           in the latter half of the array.
    // NOTE    : This is similar to STEP 08, but some parameters are
    //           different.

    // STEP 11 : Using a for-loop, wait for the 2 newly created
    //           threads to finish.
    // HINT    : Iterate over the `pthread_t` array created in STEP
    //           05, and use `pthread_join()`.

    // STEP 12 : Sum up the values returned from each thread. Store
    //           the result in a variable - created in Step 04.

    // STEP 13 : Print the sum calculated in Step 12
    // printf("The sum of the array is: %d\n", ???);

    // STEP 14 : Deallocate the structs created in Step 07 and 09.
    // NOTE    : If you use `malloc()` to allocate memory, then you
    //           must use `free()` to deallocate memory.
    
    // STEP 15 : Return 0 to terminate the program with a successful
    //           exit (status) code.
    return 0;
}

/**
 * Thread helper function that calculates the sum of the elements in
 * the array, starting at the given index. The result is stored in
 * one of the struct's members.
 *
 * @param (void *) Parameter is a struct pointer, but casted to a
 *                 void pointer.
 * @arg (void *) Returns nothing (NULL).
 */
void * sum (void * param) {

    // STEP 16 : Declare and initialize variables.
    // NOTE    : Depending on your implementation, you may or may not
    //           need to do this.

    // STEP 17 : Cast the void pointer parameter to the correct type.
    // HINT    : The type of the 'struct' is whatever you assigned it
    //           in Step 03.

    // STEP 18 : Create new variables to temporarily store the
    //           members of the 'struct'.
    // HINT    : Since the 'struct' is a pointer, the arrow operator
    //           should be used to access the members.
    // NOTE    : This is optional, and you can choose to directly
    //           work with the members of the 'struct'.

    // STEP 19 : Print the indices of the array (the beginning and
    //           end) to the terminal.
    // printf("Beginning: %d | End: %d\n", ???, ???);

    // STEP 20 : Using the indices from Step 18, sum up all the
    //           corresponding elements in the array.
    // HINT    : Store the result in a temporary variable declared in
    //           STEP 16.

    // STEP 21 : Store the value from Step 20 into one of the members
    //           of the 'struct'.
    // HINT    : Use the arrow operator to access the 'struct'

    // STEP 22 : Terminate the thread
    pthread_exit(NULL);
}
