// Author: Jatin Chowdhary chowdhaj

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// function prototype
void printArray(int *arr, int size);
void getTenNumbers(int *arr, int size);
void generateTenNumbers(int *arr, int size);

// function prototype
int printUniqueValues(int *num, int size);

int main() {
	
    int numbers[10]; // declare array
    int size = 10, choice; // declare int variables // size is size of array
    
    printf("\nWould You Like To Generate 10 Numbers Or Input Them?\n(0 = Generate | 1 = Input)\n==> "); // asks user if he wants to input 10 numbers or generate them
    scanf("%d", &choice); // store input
     
    // check if input matches specifications
    if (choice == 1) { // if 1, then
    	getTenNumbers(numbers, size); // have the user give 10 numbers
    } else if (choice == 0) { // if 0, then
    	generateTenNumbers(numbers, size); // generate 10 numbers
    } else { // if none
    	puts("\n---------------------------------"); // print divider
    	puts("ERROR: Not Valid. Exiting Program"); // print error
    	puts("---------------------------------\n"); // print divider
    	exit(0); // exit program
    }

    puts("\nYour Numbers Are:"); // tells the user about the numbers
    printArray(numbers, size); // prints numbers 

    puts("The Unique Numbers Are:"); // prints title
    if (!(printUniqueValues(numbers, size))) { // if there are no unique numbers
    	printf("(There Are No Unique Numbers)\n\n"); // tell user
    } else {
    	puts("\n"); // else print a newline
    }

    return 0;

}

/*
 * this function prints the unique values in the array
 */
int printUniqueValues(int *num, int size) {

	int shouldPrint = 1, counter = 0; // declare variables of type int

	for (int i = 0; i < size; i++) { // for loop that iterates through array
		shouldPrint = 1; // sets variable to 1
	
		for (int j = 0; j < size; j++) { // for loop that iterates through array
			if (i != j) { // if i does not equal j then
				if (num[i] == num[j]) { // if the i'th index of array equals the j'th index then:
					shouldPrint = 0; // set variable to 0
					break; // break out of loop
				}	
			}
		}

		if (shouldPrint) { // if shouldPrint is 1 then
			printf("%d, ", num[i]); // print i'th index of array
			counter++; // increment counter by 1
		}

	}
	return counter; // return counter
}

/*
 * this function generates 10 numbers
 */
void generateTenNumbers(int *arr, int size) {

	for(int i = 0; i < size; i++) { // iterates through array
		arr[i] = rand() % 9 + 1; // generates a random number and stores that into the array
    }
}

// this function gets 10 numbers from the user
void getTenNumbers(int *arr, int size) {

	puts("\nPlease Enter 10 Integers:"); // tells user to enter 10 integers

    for(int i = 0; i < size; i++) { // iterates through array

        printf("%s%d) ", (i != 9) ? "0" : "", i+1); // prints what number you're at
        scanf(" %d", &arr[i]); // stores input into array
    }
}

// this function prints the array
void printArray(int *arr, int size) {

	for(int i = 0; i < size; i++) { // iterates through array
		printf("%d", arr[i]); // prints the element in the array
		if (i != 9) { 
			printf(", "); // prints commas after each number but NOT after the last one
		}
	}
	puts("\n"); // prints a newline
}