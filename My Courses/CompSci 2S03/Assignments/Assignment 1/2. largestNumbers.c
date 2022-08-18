// Author: Jatin Chowdhary Chowdhaj

#include <stdio.h>
#include <stdlib.h>

int main() {

    printf("\n##################\n"); // print divider
    printf("# Largest Number #\n"); // print name of program to screen
    printf("##################\n\n"); // print divider

    printf("------------------\n"); // print divider
    printf("\aPlease Input Ten\nNon-Negative #'s\n"); // prints instructions to screen and makes an alert sound
    printf("------------------\n"); // prints divider

    int counter = 1; // declares and initializes a variable of type int, called counter, and assigns a value of 1
    float input; // declares a variable of type float called input
    float max; // declares a variable of type float called max
   
    while (counter <= 10) { // while counter is less than or equal to 10
        if (counter != 10) printf("0"); // if counter is not 10 then print 0
        printf("%d. ", counter++); // print counter to screen followed by a period, then increment counter by 1
        scanf("%f", &input); // prompt user for input and store that into the variable input
        if (counter == 2) max = input; // if counter is 2 then max gets input (assign value of input to max)
        if (input > max) { // if input is greater than max then...
            max = input; // ... max gets input (assign input to max)
        }
    }

    printf("------------------\n\a"); // print divider and make an alert sound
    printf("Largest Number Is:\n%.4f\n", max); // print largest number and format it to 4 decimal places
    printf("------------------\n\n"); // print divider

    return 0; // return 0 // code has been successfully executed
}
