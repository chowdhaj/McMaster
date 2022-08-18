// Author: Jatin Chowdhary chowdhaj

#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
  
/*
 * this function is called hanoi. It takes four arguments
 * argument 1: number of disks
 * argument 2: name of start tower
 * argument 3: name of temporary tower
 * argument 4: name of destination tower
 * using recursion, this function moves all disks without breaking any rules
 */
void hanoi(int disks, char start, char temporary, char destination) { 
    if (disks == 1) { // if disks equals to 1, then:
        printf("\n%c -> %c", start, temporary); // move the disk from starting to destination // this is the base case
        return; // end
    } else { // if base case is not met, then:
        hanoi(disks - 1, start, destination, temporary); // recursively call the function with one less disk on the starting tower
        printf("\n%c -> %c", start, temporary); // move the disk from starting to destination
        hanoi(disks - 1, destination, temporary, start); // recursively call the function with one less disk on the destination tower
    }
} 
  
int main() { 

    int disks; // declare variable of type int called 'disks' // this will represent # of disks on the tower
    char start, temporary, destination; // declare 3 variables of type char // used to represent towers

    // asks user how many disks are on the starting tower
    printf("\nHow many disks are on the tower?\n(Enter a positive integer greater than 0)\n==> ");
    scanf(" %d", &disks); // store input into 'disks'

    // asks user to assign a name to the starting tower // commonly referred to as 1
    printf("\nName of starting tower?\n(Enter a single character or number)\n==> ");
    scanf(" %c", &start); // store input into 'start'

    // asks user to assign a name to the temporary tower // commonly referred to as 2
    printf("\nName of temporary tower?\n(Enter a single character or number)\n==> ");
    scanf(" %c", &temporary); // store input into 'temporary'

    // asks user to assign a name to the destination tower // commonly referred to as 3
    printf("\nName of destination tower?\n(Enter a single character or number)\n==> ");
    scanf(" %c", &destination); // store input into 'destination'

    clock_t begin = clock(); // start time

    hanoi(disks, start, destination, temporary); // call the function 'hanoi' to solve the problem recursively

    clock_t stop = clock(); // stop time

    double executionTime = (double)(stop - begin) / CLOCKS_PER_SEC; // calculate execution time and store it into variable

    printf("\n\nIt took %lf CPU Time\n\n", executionTime); // print execution time to screen
    return 0; 
}