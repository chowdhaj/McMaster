// Author: Jatin Chowdhary chowdhaj

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main() {
	
    int input, term1 = 0, term2 = 1, newTerm; // declare and initialize variables/terms

    printf("\nHow many terms do you want? :: "); // ask user how many terms
    scanf("%d", &input); // store input into 'input'
    printf("\nFibonacci Series: "); // print title

    clock_t start = clock(); // start clock

    for (int i = 0; i < input; i++) { // for loop: will iterate for 'input' number of times
        printf("%d, ", term1); // prints 'term1' to screen
        newTerm = term1 + term2; // next term equals the sum of 'term1' and 'term2'
        term1 = term2; // 'term1' gets 'term2'
        term2 = newTerm; // 'term2' gets 'newTerm' (aka the next term)
    }

    clock_t finish = clock(); // end clock

    double executionTime = (double)(finish - start) / CLOCKS_PER_SEC; // calculate execution time

    printf("\n\nThis took: %lf CPU Time\n\n", executionTime); // print execution time to screen

	return 0;
}
