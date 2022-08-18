/**
 * The purpose of Lab 5 is to write a C program that solves the
 * Banking System Problem via critical sections. In the Banking System
 * Problem, race conditions are possible if the users access the
 * account concurrently. To solve this, mutex locks are used to
 * ensure mutual exclusion.
 * 
 * @author Dr. Neerja Mhaskar
 * @author Jatin Chowdhary
 * @course CompSci 3SH3
 * @date February 8th, 2022
 */ 

// STEP 01 : Include the appropriate header files
// HINT    : pthread, stdio, stdlib, etc.

// STEP 02 : Use the `define` macro to assign values
// #define NUMBER_OF_THREADS ???
// #define ???

// STEP 03 : Declare the mutex lock
// HINT    : Use `pthread_mutex_t`

// STEP 04 : Put your threaded function prototypes here.
// HINT    : You only need to name them, nothing more.
// void * ??? (void * param);
// void * ??? (void * param);

// STEP 05 : Declare a global variable, called `amount`, and
//           initialize it to 0.
int amount = 0;

/**
 * In total, 6 threads are created; where 3 threads execute the
 * `deposit` function, and the other 3 threads execute the `withdraw`
 * function. Both functions, `deposit` and `withdraw` access and
 * modify the shared variable `amount`.
 */
int main(int argc, char * argv[]) {

    // STEP 06 : Check the number of arguments. If the nyumber of
    //           arguments is not 3, then terminate the program, and
    //           print an appropriate error message.

    // STEP 07 : Check the size of the 2nd and 3rd arguments. Both
    //           need to be greater than 0. If either, or both,
    //           argument(s) are less than or equal to 0, then print
    //           an appropriate error message before exiting.
    // TIP     : Use ``atoi()`` to convert the arguments to an int

    // STEP XX : Declare 2 `pthread_t` arrays. The first array is for
    //           the deposit threads, and the second array is for the
    //           withdraw threads.

    // STEP XX : Create default attributes

	return 0;
}

/**
 * The `deposit()` function simulates the act of depositing money in
 * the bank account. A mutex lock is used to maintain mutual
 * exclusion. The new amount is printed after the transaction is
 * completed.
 * 
 * @param (void *) Parameter is originally an int pointer, but is
 *                 casted to a void pointer.
 */
void * deposit(void * param) {

    // 
    pthread_exit(0);
}

/**
 * The `withdraw()` function simulates the act of withdrawing money
 * from the bank account. A mutex lock is used to maintain mutual
 * exclusion. The remaining amount is printed after the transaction
 * is completed.
 * 
 * @param (void *) Parameter is originally an int pointer, but is
 *                 casted to a void pointer.
 */
void * withdraw(void * param) {

    //
    pthread_exit(0);
}
