// Author: Jatin Chowdhary chowdhaj

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double hypotenuse(double a, double b); // function prototype

int main() {

    double opposite, adjacent; // declaring two variables of type double called opposite and adjacent


    puts("\n**************************"); // prints a divider
    puts("* Hypotenuse  Calculator *"); // prints name of program
    puts("**************************"); // prints a divider

    printf("Enter Opposite Side ==> "); // asks user to input length of opposite side
    scanf("%lf", &opposite); // stores user input into the variable opposite

    printf("**************************\nEnter Adjacent Side ==> "); // tells user to enter adjacent side and prints a divider
    scanf("%lf", &adjacent); // stores user input into adjacent

    puts("**************************"); // prints a divider

    printf("The hypotenuse is %.2lf u.\n", hypotenuse(adjacent, opposite)); // prints the hypotenuse side to screen

    puts("**************************\n"); // prints a divider

    return 0;
}

/*
 * this function is called hypotenuse
 * its return type is double
 * it takes two doubles as its arguments
 * this function calculates the hypotenuse when given the opposite and adjacent side
 * hypotenuse = square root of opposite square + adjacent squared
 */
double hypotenuse (double a, double b) {

    double c = (a*a) + (b*b); // declares and initializes a variable of type double called 'c'
    // 'c' is assigned the square of 'a' and 'b'

    return pow(c, 0.5); // returns the square root of 'c'

}
