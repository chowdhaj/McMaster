// Author: Jatin Chowdhary chowdhaj

#include <stdio.h>
#include <stdlib.h>

// function prototype
int packCharacters(char a, char b);
void printValue(int c, int x);

int main() {

	char a, b; // declares two chars
	printf("\nEnter A Character: "); // asks user to enter
	scanf(" %c", &a); // stores input

	printf("Enter Another Character: "); // asks user to enter
	scanf(" %c", &b); // stores input

	printValue(a, 1); // prints char 'a' in binary form
	printValue(b, 1); // prints char 'b' in binary form

	printf("\n'%c' & '%c' Packed In An Unsigned Integer:", a, b); // prints text
	printValue(packCharacters(a,b), 0); // packs 'a' and 'b' and prints the result in binary form
	puts(""); // newline

	return 0;
}

/*
 * this function prints decimal numbers in their binary forms 
 * it does this by creating a mask and then iterating through the size of the
 * mask and checking each value of the number
 * if it is a 1, then print '1' b/c 1 & 1 = 1
 * if it is a 0, then print '0' b/c 0 & 1 = 0
 */
void printValue(int c, int x) {

	unsigned int size = 4 * sizeof(c); // calculates size // in this case its 16, so we're gonna use 16 bits

	if (x)
		printf("\n'%c' In Bits As An Unsigned Integer Is: ", c); // prints text

	printf("\n%7d = ", c); // prints decimal number

	unsigned int mask = 1 << (size - 1); // creates a mask

	for (int i = 1; i <= size; i++) { // iterates through 'size'

		putchar(c & mask ? '1' : '0'); // prints '1' or '0' based off the first value of 'c' and 'mask'
		c <<= 1; // shifts number by 1 bit

		// prints a space after 8 bits
		if (i == 8) {
			putchar(' '); // print space
		}
	}

	puts(""); // newline

	return;
}

int packCharacters(char a, char b) {

	return (a << 8) | b; 
	// returns two packed characters by shifting the first one by 8 bits and then using OR for the second number
}

//printf("# %d\n", a);
//unsigned int packedValue = (a << 8) | b;
//printf("# %u\n", packedValue);
