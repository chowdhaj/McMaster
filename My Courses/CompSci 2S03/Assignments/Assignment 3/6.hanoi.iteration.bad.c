// Author: Jatin Chowdhary chowdhaj

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

// these are function declarations
int inArray(int val, int *even, int size);
void printDisks(char a, char b);
void printReverseDisks(char a, char b);

int main() {

    // creates an array of ints that stores numbers // these numbers correspond to the step when you
    // move from right to left in the tower of hanoi when there is an even number of disks in the beginning
    int even[24] = { 5, 6, 10, 11, 17, 18, 20, 22, 23, 24, 29, 30, 34, 35, 
    				 40, 41, 42, 44, 46, 47, 53, 54, 58, 59};

    // creates an array of ints and stores numbers // these numbers correspond to the step when you
    // move from right to left in the tower of hanoi when there is an odd number of disks in the beginning
    int odd[64] = { 3, 5, 9, 10, 11, 12, 15, 17, 20, 21, 22, 23, 27, 29, 
				   33, 34, 35, 36, 39, 40, 41, 44, 46, 47, 48, 51, 53, 
				   57, 58, 59, 60, 63, 65, 68, 69, 70, 71, 75, 77, 80, 
				   81, 82, 83, 84, 87, 88, 89, 92, 93, 94, 95, 99, 101, 
				   105, 106, 107, 108, 111, 113, 117, 118, 119, 123, 125};
    
    int oddSize = 64, evenSize = 24; // these ints store the size of the arrays above

    int disks, isEven, loops; // declares 3 variables of type int
    // disk: determines number of disks
    // isEven: boolean number that will determine whether there is an even number of disks
    // loops: number of iterations to be done: ((2^n) - 1)

    char t1, t2, t3; // declares 3 variables of type char // used to store name of towers
    // i.e. tower1 = A, tower2 = B, tower3 = C

    // asks the user to enter in disks
    printf("\nHow many disks are on the tower?\nEnter a small, positive, whole number\n==> ");
    scanf(" %d", &disks); // stores input

    // calculates if the number of disks is even or odd using modulus
    if (disks % 2 == 0) { // if disks = even, then:
    	isEven = 1; // isEven = 1 (true)
    } else { // else:
    	isEven = 0; // isEven = 0 (false)
    }
    
    // asks the user to enter a character for the first tower
    printf("\nWhat would you like to call the first tower?\nEnter a single character OR digit\n==> ");
    scanf(" %c", &t1); // stores input

    // asks user to enter a character for the second tower
    printf("\nWhat would you like to call the second tower?\nEnter a single character OR digit\n==> ");
    scanf(" %c", &t2); // stores input

    // asks user to enter a character for the third tower
    printf("\nWhat would you like to call the third tower?\nEnter a single character OR digit\n==> ");
    scanf(" %c", &t3); // stores input

    // prints out text and beginning of divider
    puts("\n***The disks will be moved from the first tower to the last tower***\n\n############\n#          #");

    loops = pow(2, disks) - 1; // calculates number of iterations to be done based on number of disks

    clock_t startTime = clock(); // starts time

    for (int i = 1; i <= loops; i++) { // for loop that iterates over 'loops'

    	if (isEven) { // if even number of disks then:

    		if (i % 3 == 1) { // if iteration step mod 3 equals 1, then:

    			if (!(inArray(i, even, evenSize))) { // if the iteration step is NOT in the 'even' array, then:

                    printDisks(t1, t2); // move disk from left to right

                } else { // if iteration step IS in the 'even' array, then:

                    printReverseDisks(t1, t2); // move disk from right to left

                }

    		} else if (i % 3 == 2) { // else if iteration step mod 3 equals 2, then:

                if (!(inArray(i, even, evenSize))) { // if the iteration step is NOT in the 'even' array, then:

                    printDisks(t1, t3); // move disk from left to right

                } else { // if iteration step IS in the 'even' array, then:

                    printReverseDisks(t1, t3); // move disk from right to left

                }

    		} else  if (i % 3 == 0) { // if iteration step mod 3 equals 0, then:

                if (!(inArray(i, even, evenSize))) { // if the iteration step is NOT in the 'even' array, then:

                    printDisks(t2, t3); // move disk from left to right

                } else { // if iteration step IS in the 'even' array, then:

                    printReverseDisks(t2, t3); // move disk from right to left

                }

    		} else {

    			printf("Done\n"); // prints done // this line is never executed // its just here for debugging purposes

    		}

    	} else { // else, if odd number of disks, then: 

    		if (i % 3 == 1) { // if iteration step mod 3 equals 1, then:

                if (!(inArray(i, odd, oddSize))) { // if iteration step is NOT in the 'odd' array, then:

                    printDisks(t1, t3); // move disk from left to right 

                } else {

                    printReverseDisks(t1, t3); // move disk from right to left

                }

    		} else if (i % 3 == 2) { // if iteration step mod 3 equals 2, then:

                if (!(inArray(i, odd, oddSize))) { // if iteration step is NOT in the 'odd' array, then:

                    printDisks(t1, t2); // move disk from left to right 

                } else {

                    printReverseDisks(t1, t2); // move disk from right to left

                }

    		} else  if (i % 3 == 0) { // if iteration step mod 3 equals 0, then:

                if (!(inArray(i, odd, oddSize))) { // if iteration step is NOT in the 'odd' array, then:

                    printDisks(t2, t3); // move disk from left to right 

                } else {

                    printReverseDisks(t2, t3); // move disk from right to left

                }

    		} else {

    			printf("Done\n"); // prints done // this line is never executed // its just here for debugging purposes

    		}

    	}
    }

    clock_t stopTime = clock(); // stop the time
    double executionTime = (double)(stopTime - startTime) / CLOCKS_PER_SEC; // calculate cpu time

    puts("#          #"); // print divider
    puts("############\n"); // print divider

    printf("***This took %lf CPU Time***\n\n", executionTime); // print execution time to screen

	return 0;
}

/*
 * this function moves the disks from left to right
 * it achieves this by having the left most tower on the left, and right most tower on the right
 * [i.e. 1 -> 3]
 * takes two arguments; char
 * returns nothing (void)
 */
void printDisks(char a, char b) {
    printf("#  ");
    printf("%c -> %c", a, b);
    printf("  #\n");
}

/*
 * this function moves the disks from right to left
 * it achieves this by having the right most tower on the right, and left most tower on the left
 * [i.e. 3 -> 1]
 * takes two arguments; char
 * returns nothing (void)
 */
void printReverseDisks(char a, char b) {
    printf("#  ");
	printf("%c -> %c", b, a);
    printf("  #\n");
}

/*
 * this function checks to see if a given value is inside a specified array
 * takes 3 arguments:
 *      1. value to check
 *      2. array
 *      3. length of array
 * returns 1 (true) if the value is inside the array, and 0 (false) otherwise
 */
int inArray(int val, int *arr, int size) {

    for (int i = 0; i < size; i++) { // iterates through the array
    	if (arr[i] == val) return 1; // if the i'th value is in the array, return 1 (true)
    }
	return 0; // return 0 (false)
}