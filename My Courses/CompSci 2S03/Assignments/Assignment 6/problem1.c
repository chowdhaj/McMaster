// Author: Jatin Chowdhary chowdhaj

#include <stdio.h>
#include <stdlib.h>

// function prototype
void printValue(unsigned int num, unsigned int size);
int power2(unsigned int num, unsigned int pow);

int main() {

	unsigned int number, power, size = 8 * sizeof(number); // calculates size of 'number' and multiplies it by 8
	// this is done to get number of bits

	printf("\nPlease Enter A Number :: "); // prompts user to enter number
	scanf("%u", &number); // stores input

	printf("How Many Bits Would You Like To Shift :: "); // prompts user to enter number
	scanf("%u", &power); // stores input

	printf("\nStarting Value In Decimal & Binary:"); // prints text
	printValue(number, size); // prints number in bits

	printf("\n\nAfter Shifting %u, %u Bits To The Left:", number, power); // prints text
	printValue(number << power, size); // shifts number and prints result in bits
	puts("\n"); // newline

	return 0;
}

int power2(unsigned int num, unsigned int pow) {

	return num << pow; // returns the 'number' shifted by 'pow' number of bits
}

void printValue(unsigned int num, unsigned int size) {

	printf("\n%10u ==> ", num); // prints the decimal version of 'number'
	unsigned int mask = 1 << 31; // creates a mask by shifting 1, 31 bits

	// this for loop prints decimal numbers as binary
	for (int i = 1; i <= size; i++) { // iterate through the size of the number [size in bits]
		putchar(num & mask ? '1' : '0'); // puts a 1 or 0 depending on the value at the i'th index [& operator is used]
		num <<= 1; // shifts number by 1 bit

		// prints a space after 8 bits
		if (i % 8 == 0) {
			putchar(' '); // print space
		}
	}

	return;
}