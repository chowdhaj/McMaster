// Author: Jatin Chowdhary chowdhaj

#include <stdio.h>
#include <stdlib.h>

// function prototype
void printBits(unsigned int num);
void unpackCharacters(unsigned int packedChar);

int main() {

	unsigned int packed; // declare unsigned int
	printf("\nEnter A Packed Character Value (Int) :: "); // prompt user to enter packed char value
	scanf("%u", &packed); // store input into packed

	unpackCharacters(packed); // unpack the characters
	puts(""); // newline

	return 0;
}

void unpackCharacters(unsigned int packedChar) {

	printf("\nThe Packed Value Is: "); // prints text
	printBits(packedChar); // prints packed character value in decimal

	char packedLeft = (packedChar & 65280) >> 8; // unpacked the left value by:
	// ANDs 'packed' with 65280, which gets rid of the right value
	// shifts the result by 8 bits to move it into the right most place
	// NOTE: you can just shift by 8 bits and ignore the mask altogether --> char packedLeft = packedChar >> 8
	printf("\nThe Left Unpacked Value Is: %c", packedLeft); // prints left value as a char
	printBits(packedLeft); // prints left value in binary form
	
	char packedRight = packedChar & 255; // unpacks right value by ANDing it with 255, getting rid of the left value
	printf("\nThe Right Unpacked Value Is: %c", packedRight); // prints right value as a char
	printBits(packedRight); // prints right value in binary form

}

void printBits(unsigned int num) {

	unsigned int size = sizeof(num) * 4; // calculates size (i.e. how many bits to be used) // 16 in this case
	unsigned int mask = 1 << (size - 1); // creates a mask

	printf("\n%7u == ", num); // prints decimal number

	// this for loop iterates through 'size' and prints the binary form, bit by bit
	for (int i = 1; i <= size; i++) {
		putchar(num & mask ? '1' : '0'); // prints '1' or '0' based off the first value of 'num' and 'mask'
		num <<= 1; // shifts by 1 bit to the left

		// prints a space after 8 bits
		if (i == 8)
			putchar(' '); // print space
	}
	puts(""); // newline

}