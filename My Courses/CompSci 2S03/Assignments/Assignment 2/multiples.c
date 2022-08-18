// Author: Jatin Chowdhary chowdhaj

#include <stdlib.h>
#include <stdio.h>

int multiples (int a, int b); // function prototype

int main() {

    int loop, first, second, ans; // declares 4 variables of type int
    
    puts("\n###########################"); // prints a divider
    puts("### Multiple Calculator ###"); // prints name of program
    puts("###########################"); // prints divider
    printf("How many pairs of integers\nwould you like to check: "); // asks user to input how many pairs of integers they wanna check
    scanf("%d", &loop); // accepts input and stores it in 'loop'
    puts("###########################"); // prints divider

    // this for loop iterates for 'X' number of times, where 'X' is the value of 'loop'
    for (int i = 1; i <= loop; i++) { 
        printf("%14s #%d\n", "Pair", i); // prints the nth pair
        printf("Enter Dividend Integer: "); // asks user to input dividend
        scanf("%d", &first); // stores input into 'first'
        printf("Enter Divisor Integer: "); // asks user to input divisor
        scanf("%d", &second); // stores input into 'second'
        int c = multiples(first, second); // declares and initializes a variable of type int called 'c' // holds either 1 or 0
        printf("[%d] (%s)\n", c, (c == 1) ? "Is A Multiple" : "Is Not A Multiple"); // prints 'c' and tells whether the divisor evenly divides into the dividend
        puts("############################"); // prints divider
    }

    puts(""); // prints a newline
    

}

/*
 * this function is called multiples
 * it has a return type of int and accepts two arguments that are of type int
 * returns either 1 or 0 based off the arguments
 * if the modulus of the first and second argument equals to 0, then return 1 (true), else return 0 (false)
 */
int multiples (int a, int b) {

    if (a % b == 0) { // if 'a' mod 'b' is 0 then return 1
        return 1;
    } else { // otherwise, return 0
        return 0;
    }
}
