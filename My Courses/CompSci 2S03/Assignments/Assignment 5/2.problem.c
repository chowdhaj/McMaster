// Author: Jatin Chowdhary chowdhaj

#include <stdio.h>
#include <stdlib.h>
#include <math.h> 

// function prototypes
void add(double d1, double d2);
void subtract(double d1, double d2);
void multiply(double d1, double d2);
void divide(double d1, double d2);
void printMenu();

int main() {

	void (*funcPoint[4])(double d1, double d2) = {add, subtract, multiply, divide};
	// array of pointers contains the addresses to our functions
	// each function returns nothing and accepts two doubles as parameters

	double d1, d2; // declare d1 and d2
	int choice; // declare choice

	printf("\nInput Value #1 --> "); // tells user to enter first #
	scanf("%lf", &d1); // stores result into d1

	printf("Input Value #2 --> "); // tells user to enter second #
	scanf("%lf", &d2); // stores result into d2

	puts(""); // prints newline
	printMenu(); // prints menu of options
	printf("==> "); // tells user where to enter choice
	scanf("%d", &choice); // stores into choice

	puts(""); // prints newline
	(*funcPoint[choice-1])(d1, d2); // calls the respective function based on choice

	return 0;
}

// prints the menu of options
void printMenu() {

	puts("Select An Option\n----------------"); // prints title
	puts("1. Add\n2. Subtract"); // prints add and subtract
	puts("3. Multiply\n4. Divide\n"); // prints mulitply and divide
}

// adds two numbers together
void add(double d1, double d2) {

	printf("Adding %.2lf & %.2lf\n", d1, d2); // prints #s and what operation its doing
	printf("Result: %.2lf\n", d1 + d2); // adds and prints the result
	return;
}

// subtracts two numbers
void subtract(double d1, double d2) {

	printf("Subtracting %.2lf & %.2lf\n", d1, d2); // prints #s and what operation its doing
	printf("Result: %.2lf\n", d1 - d2); // subtract and prints the result
	return;
}

// multiplies two numbers
void multiply(double d1, double d2) {
	
	printf("Multiplying %.2lf & %.2lf\n", d1, d2); // prints #s and what operation its doing
	printf("Result: %.2lf\n", d1 * d2); // multiply and prints the result
	return;
}

// divides two numbers
void divide(double d1, double d2) {

	printf("Dividing %.2lf & %.2lf\n", d1, d2); // prints #s and what operation its doing
	printf("Result: %.2lf\n", d1 / d2); // divide and prints the result
	return;	
}
