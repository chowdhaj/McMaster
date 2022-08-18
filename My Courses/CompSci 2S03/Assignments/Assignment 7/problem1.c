// Author: Jatin Chowdhary chowdhaj

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function prototype
void writeToFile(char in[25], char out[25]);

int main() {

	char file1[25], file2[25], outFile[25]; // declaring arrays of chars
	// these will store file names

	printf("\nInput Name Of File 1 :: "); // prompt user for file name
	//fgets(file1, 25, stdin); 
	scanf(" %s", file1); // store input

	printf("Input Name Of File 2 :: "); // prompt user for file name
	//fgets(file2, 25, stdin);
	scanf(" %s", file2); // store input

	printf("Input Name Of Out File :: ");// prompt user for file name
	//fgets(outFile, 25, stdin);
	scanf(" %s", outFile); // store input

	writeToFile(file1, outFile); // write contents from file1 to outFile
	writeToFile(file2, outFile); // write contents from file2 to outFile

	puts(""); // newline
}

void writeToFile(char in[25], char out[25]) {

	FILE *readFile = fopen(in, "r"); // open file1 as read
	FILE *writeFile = fopen(out, "a"); // open outFile as append

	char line[200]; // declare array of chars that'll hold 200 characters

	while (!(feof(readFile))) { // while file1 is not at end of file

		fgets(line, 150, readFile); // get line of file1
		fprintf(writeFile, line); // write line of file1 into outFile
	}

	fprintf(writeFile, "\n"); // write newline into outFile

	fclose(readFile); // close file1
	fclose(writeFile); // close outFile

	return; // end of function
}
