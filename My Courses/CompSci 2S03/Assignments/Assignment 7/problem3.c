// Author: Jatin Chowdhary chowdhaj

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

	char fileName[25]; // declare array of char to hold 25 characters
	printf("\nWhat Is The Name Of The File?\n==> "); // prompt user
	scanf(" %s", fileName);	// store input

	unsigned int num; // declare unsigned int
	printf("\nHow Many Lines Do You Wanna Write?\n==> "); // prompt user
	scanf(" %u", &num); // store input 

	puts(""); // print newline

	FILE *writeFile = fopen(fileName, "a"); // open file as append

	char line[100]; // declare array of char to hold 100 characters

	fgets(line, 100, stdin); // get input from user, first 100 chars, and store it
	fprintf(writeFile, "\n"); // write \n into file

	for(unsigned int i = 1; i <= num; i++) { // iterate through 'num'
		printf("Line #%u: ", i); // print line number
		fgets(line, 100, stdin); // get input from user
		fprintf(writeFile, line); // write input into file
		//printf("> %s", line);
	}

	fclose(writeFile); // close file

	char c; // declare char
	printf("\nDo you wanna see the contents of '%s'\n(Y/N) ==> ", fileName); // prompt user
	scanf(" %c", &c); // store input

	char singleLine[150]; // array of chars that'll hold up to 150 chars

	if (c == 'y' || c == 'Y') { // if input from user is a y or Y
		FILE *readFile = fopen(fileName, "r"); // open file as read
		while (!(feof(readFile))) { // iterate through file and print contents
			fgets(singleLine, 150, readFile); // get first line of file
			puts(singleLine); // print it
		}
	} 

	return 0;
}