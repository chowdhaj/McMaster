#include <stdio.h>
#include <stdlib.h>

int main() {

    int i, j, k; // initialize int i, j, k

    for (i = 1; i <= 5; ++i) { // for loop that will iterate 5 times
        for (j = 1; j <= 3; ++j) { // for loop that will iterate 3 times
            for (k = 1; k <= 4; ++k) // for loop that will iterate 4 times
                 printf("%s","*"); // prints an asterisk to the screen
            puts(""); // prints a newline // similar to printf("\n")
        }
        puts(""); // prints a newline to screen // acts similar to printf("\n")
    }

    return 0; // returns 0 // program has successfully executed
}
