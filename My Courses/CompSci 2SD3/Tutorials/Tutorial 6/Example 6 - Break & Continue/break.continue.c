/**
 * Demonstrates the difference between `break` and `continue`.
 * `break` is used to exit the loop.
 * `continue` is used to skip the current iteration and go to the
 * next one.
 * 
 * @author Jatin Chowdhary
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define TRUE  1
#define FALSE 0

int main(int argc, char const *argv[]) {


    for (int x = 1000; TRUE; x++) {
        if (x % 37 == 0) {
            printf("%d is the number\n", x);
            break;
        }
    }

    // BREAK DEMO
    for (int x = 0; x < 5; x++) {
        // x = 0,1,2,3,4
        printf("[BREAK] The value of 'x' is %d\n", x);
        // x = 0, 1, 2
        if (x == 2) {
            break;
        }
        
    }
    // HERE: This is where break ends up

    printf("%s\n", ""); // Print newline

    // CONTINUE DEMO
    for (int x = 0; x < 5; x++) {
        // x = 0,1,2,3,4
        printf("[CONTINUE] The value of 'x' is: %d\n", x);
        if (x == 2) { continue; }
        // EVERYTHING HERE AND BELOW
        
        // x = 0, 1, 3, 4
    }

    return 0;

}

/*

------
OUTPUT
------

[BREAK] The value of 'x' is 0
[BREAK] The value of 'x' is 1

[CONTINUE] The value of 'x' is: 0
[CONTINUE] The value of 'x' is: 1
[CONTINUE] The value of 'x' is: 3
[CONTINUE] The value of 'x' is: 4

 */

