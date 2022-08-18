// Author: Jatin Chowdhary chowdhaj
 
#include <stdio.h>
#include <math.h>
#include <time.h>

// these are function declarations
void printTowersHorizontally(int num[3][9], int lenOfArray);
void printTowersVertically(int num[3][9], int lenOfArray);
void sortArrayFromLeastToGreatest(int *arr, int size); 
void shiftDiskToTop(int *arr1, int *arr2, int size);
void removeTopDisk(int *arr, int size);

// more function declarations
int isLeftDiskSmaller(int *arr1, int *arr2, int size); 
int arrayIsEmpty(int *arr, int size); 
int getTopDisk(int *arr, int size); 

int main() {

    // initialize and declare a multi-dimensional array that is 3 x 9
    int num[3][9] = {  
        {0,0,1,2,3,4,5,6,7}, // represents the first tower/peg // tower A // tower 1
        {0,0,0,0,0,0,0,0,0}, // represents the second tower/peg // tower B // tower 2
        {0,0,0,0,0,0,0,0,0} // represents the third tower/peg // tower C // tower 3
    };

    int lengthOfArray = 9; // length of the multi-dimensional array // corresponds to disks on tower

    // prints the name of the program along with some instructions
    puts("\n#######################################\n# Tower Of Hanoi # Iterative Solution #\n#######################################");
    printf("# There Are %d Disks On The 1st Tower  #\n", lengthOfArray); // prints how many disks are on the first tower
    printf("# If You Want To Add/Subtract Disks   #\n"); // prints instructions
    printf("# Please Modify The Source Code       #\n"); // prints instructions
    puts("#######################################"); // prints divider

    puts("\n---------------------------------------\n"); // prints separator

    int loop = pow(2, lengthOfArray) - 1; // represents number of iterations based on # of disks
    int isEven; // declares a variable of type int // will be used as a binary number to store whether there is an even or odd number of disks

    // this if statement calculates whether there is an even or odd number of disks on the first tower
    if (lengthOfArray % 2 == 0) { // if length of array mod 2 is 0, then:
        isEven = 1; // there is an even number of disks
    } else { // else:
        isEven = 0; // odd number of disks
    }

    puts("#######################################"); // prints divider
    puts("#       Base Case | (Moves = 0)       #"); // prints base case
    puts("#######################################"); // prints divider

    puts(""); // prints a line
    printTowersVertically(num, lengthOfArray); // prints the initial view of the towers, when moves = 0

    clock_t begin = clock();  // start time

    for(int i = 1; i <= loop; i++) { // this for loop iterates over 'loop'

        puts("#######################################"); // prints divider
        printf("#       Iterative | (Moves = %d)     #\n", i); // prints which move/step your own
        puts("#######################################\n"); // prints divider

        if (isEven) { // if there are an even number of disks

            if (i % 3 == 1) { // if i mod 3 equals 1

                // Makes Legal Move Between Array 0 & Array 1

                if (arrayIsEmpty(num[1], lengthOfArray)) {

                    shiftDiskToTop(num[0], num[1], lengthOfArray);
                    removeTopDisk(num[0], lengthOfArray);
                    sortArrayFromLeastToGreatest(num[1], lengthOfArray);

                } else {

                    if (isLeftDiskSmaller(num[1], num[0], lengthOfArray)) {

                        shiftDiskToTop(num[1], num[0], lengthOfArray);
                        removeTopDisk(num[1], lengthOfArray);
                        sortArrayFromLeastToGreatest(num[0], lengthOfArray);

                    } else {

                        shiftDiskToTop(num[0], num[1], lengthOfArray);
                        removeTopDisk(num[0], lengthOfArray);
                        sortArrayFromLeastToGreatest(num[1], lengthOfArray);

                    }
                
                }

            } else if (i % 3 == 2) {

                // Makes Legal Move Between Array 0 & Array 2

                if (arrayIsEmpty(num[2], lengthOfArray)) {

                    shiftDiskToTop(num[0], num[2], lengthOfArray);
                    removeTopDisk(num[0], lengthOfArray);
                    sortArrayFromLeastToGreatest(num[2], lengthOfArray);
                
                } else {

                    if (isLeftDiskSmaller(num[2], num[0], lengthOfArray)) {

                        shiftDiskToTop(num[2], num[0], lengthOfArray);
                        removeTopDisk(num[2], lengthOfArray);
                        sortArrayFromLeastToGreatest(num[0], lengthOfArray);

                    } else {

                        shiftDiskToTop(num[0], num[2], lengthOfArray);
                        removeTopDisk(num[0], lengthOfArray);
                        sortArrayFromLeastToGreatest(num[2], lengthOfArray);

                    }
                
                }

            } else  if (i % 3 == 0) {

                // Makes Legal Move Between Array 1 & Array 2

                if (arrayIsEmpty(num[2], lengthOfArray)) {

                    shiftDiskToTop(num[1], num[2], lengthOfArray);
                    removeTopDisk(num[1], lengthOfArray);
                    sortArrayFromLeastToGreatest(num[2], lengthOfArray);
                
                } else {

                    if (isLeftDiskSmaller(num[1], num[2], lengthOfArray)) {

                        shiftDiskToTop(num[1], num[2], lengthOfArray);
                        removeTopDisk(num[1], lengthOfArray);
                        sortArrayFromLeastToGreatest(num[2], lengthOfArray);

                    } else {

                        shiftDiskToTop(num[2], num[1], lengthOfArray);
                        removeTopDisk(num[2], lengthOfArray);
                        sortArrayFromLeastToGreatest(num[1], lengthOfArray);

                    }
                
                }

            } else { printf("#"); }

        } else { // if there is an odd number of disks

            if (i % 3 == 1) {

                // Makes Legal Move Between Array 0 & Array 2

                if (arrayIsEmpty(num[2], lengthOfArray)) {

                    shiftDiskToTop(num[0], num[2], lengthOfArray);
                    removeTopDisk(num[0], lengthOfArray);
                    sortArrayFromLeastToGreatest(num[2], lengthOfArray);

                } else {

                    if (isLeftDiskSmaller(num[0], num[2], lengthOfArray)) {

                        shiftDiskToTop(num[0], num[2], lengthOfArray);
                        removeTopDisk(num[0], lengthOfArray);
                        sortArrayFromLeastToGreatest(num[2], lengthOfArray);

                    } else {

                        shiftDiskToTop(num[2], num[0], lengthOfArray);
                        removeTopDisk(num[2], lengthOfArray);
                        sortArrayFromLeastToGreatest(num[0], lengthOfArray);

                    }
                }

            } else if (i % 3 == 2) {

                // Makes Legal Move Between Array 0 & Array 1

                if (arrayIsEmpty(num[1], lengthOfArray)) {

                    shiftDiskToTop(num[0], num[1], lengthOfArray);
                    removeTopDisk(num[0], lengthOfArray);
                    sortArrayFromLeastToGreatest(num[1], lengthOfArray);

                } else if (arrayIsEmpty(num[0], lengthOfArray)) {

                    shiftDiskToTop(num[1], num[0], lengthOfArray);
                    removeTopDisk(num[1], lengthOfArray);
                    sortArrayFromLeastToGreatest(num[0], lengthOfArray);

                } else {

                    if (isLeftDiskSmaller(num[0], num[1], lengthOfArray)) {

                        shiftDiskToTop(num[0], num[1], lengthOfArray);
                        removeTopDisk(num[0], lengthOfArray);
                        sortArrayFromLeastToGreatest(num[1], lengthOfArray);

                    } else {

                        shiftDiskToTop(num[1], num[0], lengthOfArray);
                        removeTopDisk(num[1], lengthOfArray);
                        sortArrayFromLeastToGreatest(num[0], lengthOfArray);

                    }
                }

            } else if (i % 3 == 0) {

                // Makes Legal Move Between Array 2 & Array 1

                if (arrayIsEmpty(num[1], lengthOfArray)) {

                    shiftDiskToTop(num[2], num[1], lengthOfArray);
                    removeTopDisk(num[2], lengthOfArray);
                    sortArrayFromLeastToGreatest(num[1], lengthOfArray);

                } else {

                    if (isLeftDiskSmaller(num[2], num[1], lengthOfArray)) {

                        shiftDiskToTop(num[2], num[1], lengthOfArray);
                        removeTopDisk(num[2], lengthOfArray);
                        sortArrayFromLeastToGreatest(num[1], lengthOfArray);

                    } else {

                        shiftDiskToTop(num[1], num[2], lengthOfArray);
                        removeTopDisk(num[1], lengthOfArray);
                        sortArrayFromLeastToGreatest(num[2], lengthOfArray);

                    }
                }

            } else { printf("#"); }

        }

    printTowersVertically(num, lengthOfArray); // print out towers after each iteration

    }

    clock_t stop = clock(); // stop time

    double executionTime = (double)(stop - begin) / CLOCKS_PER_SEC; // calculate execution time and store it into variable

    puts("--------------------------");
    printf("It took %lf CPU Time\n", executionTime); // print execution time to screen
    puts("--------------------------\n");

    return 0;
}

/*
 * this function sorts the array from least the greatest using bubble sort
 * it takes an array and the size of the array and returns the sorted array
 */
void sortArrayFromLeastToGreatest(int *arr, int size) {

    int swapped;

    while (1) {

        swapped = 0;

        for (int i = 0; i < size - 1; i++) {

            if (arr[i] > arr[i+1]) {
                int temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
                swapped = 1;
            }
        }

        if (swapped == 0) {
            break;
        }
    }
}

/*
 * this function removes the top disk from an array
 * takes an array and the size of the array
 */
void removeTopDisk(int *arr, int size) {

    for (int i = 0; i < size; i++) {
        if (!(arr[i] == 0)) {
            arr[i] = 0;
            break;
        }
    }
}

/*
 * this function gets the top disk from an array
 * takes an array and the size of the array and returns the top disk
 *
 */
int getTopDisk(int *arr, int size) {

    for (int i = 0; i < size; i++) {
        if (!(arr[i] == 0)) {
            return arr[i];
        }
    }
    return 0;
}

// this function shifts/moves disks from one array to another
void shiftDiskToTop(int *arr1, int *arr2, int size) {

    arr2[0] = getTopDisk(arr1, size);

}

// checks if an array is empty // if empty, then there are no disks
int arrayIsEmpty(int *arr, int size) {

    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }

    if (sum == 0) {
        return 1;
    } else {
        return 0;
    }
}

// checks to see if the top most disk from array X is smaller than the top most disk from array Y
int isLeftDiskSmaller(int *arr1, int *arr2, int size) {

    int topOfDisk1, topOfDisk2;

    for (int i = 0; i < size; i++) {
        if (!(arr1[i] == 0)) {
            topOfDisk1 = arr1[i];
            break;
        }
    }

    //printf("\n# %d #\n", topOfDisk1);

    for (int i = 0; i < size; i++) {
        if (!(arr2[i] == 0)) {
            topOfDisk2 = arr2[i];
            break;
        }
    }

    //printf("\n# %d #\n", topOfDisk2);

    if (topOfDisk1 < topOfDisk2) {
        return 1;
    } else {
        return 0;
    }
}

// prints the towers, horizontally
void printTowersHorizontally(int num[3][9], int lenOfArray) {

    printf("\nPrinting Towers Horizontally:\n\n");
    for (int i = 0; i < 3; ++i) { 
        for (int j = 0; j < lenOfArray; ++j) { 
            printf("%d ", num[i][j]);
        }
    	printf("| Tower %d\n", i + 1);
    }
    puts("");
}

// prints the towers, vertically
void printTowersVertically(int num[3][9], int lenOfArray) {

    //printf("\nPrinting Towers Vertically:\n\n");
    for (int j = 0; j < lenOfArray; ++j) { 
        for (int i = 0; i < 3; ++i) { 
            if (num[i][j] != 0) {
                printf("%d\t", num[i][j]);
            } else {
                printf(" \t");
            }
            
        }
        puts("");
    }
    printf("-\t-\t-\n1\t2\t3");
    puts("\n");
}

/*

    char printTowers;
    printf("Do You Want The Towers Printed?\n(Y/N) ==> ");
    scanf(" %c", &printTowers);

    int decision;
    if (printTowers == 'y' || printTowers == 'Y') {
        decision = 1;
    } else {
        decision = 0;
    }

    char horizontalOrVertical;
    if (decision) {
        printf("\nDo You Want Them Horizontally Or Vertically Printed?\n(H/V) ==> ");
        scanf(" %c", &horizontalOrVertical);
    }

    int orientation;
    if (horizontalOrVertical == 'v' || horizontalOrVertical == 'V') {
        orientation = 1;
    } else {
        orientation = 0;
    }

 */