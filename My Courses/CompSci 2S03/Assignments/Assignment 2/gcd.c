// Author: Jatin Chowdhary chowdhaj

#include <stdio.h>
#include <stdlib.h>

int gcd (int a, int b); // function prototype

int main() {

    int a, b; // declares two variables of type int called 'a' and 'b'

    puts("\n-----------------------------"); // prints a divider
    puts("|  Greatest Common Divisor  |"); // prints name of program
    puts("-----------------------------"); // prints a divider

    printf("Enter Dividend Number ==> "); // asks user to input the dividend number
    scanf("%d", &a); // stores user input into 'a'

    puts("-----------------------------"); // prints a divider

    printf("Enter Divisor Number  ==> "); // asks user to input the divisor number
    scanf("%d", &b); // stores user input into 'b'

    puts("-----------------------------"); // prints divider

    printf("The GCD Of %d And %d is: %d\n", a, b, gcd(a,b)); // prints the GCD of 'a' and 'b'

    puts("-----------------------------\n"); // prints divider

    return 0;
}

/*
 * this function is called gcd
 * its return type is int and takes two arguments of type int
 * this function calculates the greatest common divisor of two integers using euclidean's algorithm
 * how it works:
 * 1. if 'a' or 'b' equal to 0, return the respective number
 * 2. while 'b' is not equal to 0, set 'c' to 'b', store the modulus of 'a' and 'b' in 'b', and 'a' gets 'c'. return 'a'
 */
int gcd (int a, int b) {

    if (a == 0) { // if 'a' is equal to 0 then return 'a'
        return a;
    } else if (b == 0) { // if 'b' is equal to 0 then return 'b'
        return b;
    } else {
        int c; // declare a variable of type int called 'c'
        while (b != 0) { // while 'b' is not 0
            c = b; // assign 'b' to 'c'
            b = a % b; // assign the modulus of 'a' and 'b' to 'b'
            a = c; // assign 'c' to 'a
            //printf("%d | %d\n", a,b); // prints the values of a and b upon each iteration // commented out b/c its not required
        }
        return a; // return 'a' after end of while loop
    }
}
