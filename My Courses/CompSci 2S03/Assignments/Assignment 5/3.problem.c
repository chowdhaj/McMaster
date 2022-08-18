// Author: Jatin Chowdhary chowdhaj

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
  
void printLatinWord(char *charPointer); // function prototype

int main(void) {

    char temporaryInput[100]; // declares and initializes an array of chars
    // holds temporary input up to 100 words
    char *storeWordsPointer; // declares a char pointer

    printf("\nYour Sentence: "); // tells user to type sentence
 
    fgets(temporaryInput, 100, stdin); // stores the first 100 chars of input

    char sanitizedInput[100]; // creates new array of chars // holds 100 chars

    // this for loop removes the '\n' at the end of the input
    // fgets retains the '\n' of the input // we must get rid of it
    for (int i = 0; temporaryInput[i] != '\n'; i++) { // iterate through input
    	sanitizedInput[i] = temporaryInput[i]; // copy character from temp Input into sanitized Input, as long as its not a newline
    }

    printf("\nIn Pig Latin: "); // prints text
 
    storeWordsPointer = strtok(sanitizedInput, " "); // breaks up input and stores first string into char pointer
 
    while (storeWordsPointer != NULL) { // while the string pointer is not null

        printLatinWord(storeWordsPointer); // print the pig latin word associated with the string pointer
        storeWordsPointer = strtok(NULL, " "); // stores the next word into string pointer
    }

    puts("\n");

}

// this function will convert the word into pig latin
// takes a string pointer and returns nothing
void printLatinWord(char *charPointer) {

	printf("%s%cay ", charPointer + 1, charPointer[0]); // drops the first letter and adds to the end, followed by an 'ay' 
	return; // return
}