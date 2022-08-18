/**
 * Introduces the `pthread` library by creating a simple threaded
 * function that calculates the sum of a simple series. Students are
 * expected to follow along and fill in the 'TODOs'. Doing is the
 * best way to learn.
 * 
 * @author Dr. Neerja Mhaskar
 * @author Jatin Chowdhary
 * @course CompSci 3SH3
 * @date February 8th, 2022
 */ 

#include <stdio.h>
#include <stdlib.h>

/**
 * TASK:
 * Write a multithreaded program that calculates the summation of a
 * non-negative integer in a separate thread. Make sure that the user
 * inputs the correct number of arguments, and that the number given
 * by the user is non-negative. Create threads using the `pthreads`
 * API (POSIX Standard).
 */
int main(int argc, char * argv[]) {

    // 1. Include the `pthread` header file.
    // TODO

    // 2. Check the the number of arguments via `argc`. Ensure that
    //    this number is exactly 2. If exactly 2 arguments are not
    //    provided, terminate/exit the program.
    // TODO

    // 3. Convert the second (supplied) argument from a character
    //    array to an int via `atoi`
    // TODO

    // 4. Check if the converted number/int is non-negative. In other
    //    words, the number needs to be positive; greater than 0. If
    //    the number is less than 0, terminate the program.
    // TODO

    ///////////////////////////////////////////////////////
    // Now we will declare, create, and execute a thread //
    ///////////////////////////////////////////////////////

    // 5a. Declare a thread identifier `tid` variable.
    // TODO

    // 5b. What is the purpose of `tid`?
    // TODO

    // 6a. Declare a set of thread attributes; don't specify anything,
    //     just declare it.
    // TODO

    // 6b. Concisely explain what is the purpose of thread attributes?
    // TODO

    // 7. Use the `pthread_attr_init()` function to set the attributes
    //    of the thread to default.
    // TODO

    // 8. Create a threaded function called `runner`, below the
    //    `main()` function. This threaded function will calculate
    //    the sum from 0 to a specified number.
    // TODO

    // 15. Create and execute the thread via `pthread_create`
    //     Hint: `pthread_create()` takes 4 arguments
    // TODO

    // 16. Wait for the thread to finish/exit before allowing `main()`
    //     to terminate/exit.
    //     Hint: Use `pthread_join()`

    // 17. Print the sum/result to the terminal
    // TODO

    // 18. Return 0 to indicate that the program terminated without
    //     errors.
    // TODO

    // 19a. Compile the program and run it. Use the provided makefile.
    // TODO

    // 19b. Is the `-pthread` required when compiling?
    //      Hint: The answer is different depending on which machine
    //      you are using (i.e. VM Vs. Host).
    // TODO

    // 20. Is there another way to specify default attributes?
    //     Hint: NULL!
    // TODO

    // 21. What if the `pthread_join()` line was commented out? What
    //     do you think will happen? Try it out! Write about your
    //     findings below.
    // TODO

    // 22. In total, how many threads are running?
    // TODO

    // 23a. Create another thread that calculates the sum of numbers
    //      from 0 to 100.
    //      Tip: Write your code above `return 0`.
    // TODO

    // 23b. Now, in total, how many threads are running?

    // 24. HOMEWORK: Create a thread that calculates the sum of
    //     numbers from 0 to 50.
    //     Tip: Write your code above `return 0`.
    // TODO
    
}

/**
 * Thread helper function that calculates the sum from 0 to a
 * specified number. Result is stored in a global int. Hence, nothing
 * is returned to the caller (i.e. void).
 * 
 * When a thread is created via `pthread_create`, this thread is
 * executed.
 *
 * @param (void *) Parameter is a character array, but casted to a
 *                 void pointer.
 */
void * runner (void * param) {

    // 9a. Why is the parameter a void pointer?
    // TODO

    // 9b. How is it possible that something (i.e. char, int, etc.)
    //     can be casted to void?
    // TODO

    // 10. Use `atoi`, just like before to convert the argument to an
    //     an integer. Store the result in an int data type.
    // TODO

    // 11. Declare a variable that will store the result of the
    //     summation. Note that this needs to be accessible to the
    //     main thread/function. Use your knowledge of processes and
    //     threads to decide whether the variable should be local or
    //     global. Finally, initialize it to 0.
    // TODO

    // 12. Calculate the sum from 0 to the specified number. Store the
    //     result in the variable created in (11)
    //     Hint: Use a for-loop.
    // TODO

    // 13a. Terminate the threaded function.
    //      Hint: Use `pthread_exit(NULL)` OR `pthread_exit(0)`
    // TODO

    // 13b. What's the difference between `pthread_exit(NULL)` and
    //      `pthread_exit(0)`?
    // TODO

    // 14a. Add the prototype for the threaded function at the top
    // TODO

    // 14b. What's the point of function prototypes?
    // TODO
}
