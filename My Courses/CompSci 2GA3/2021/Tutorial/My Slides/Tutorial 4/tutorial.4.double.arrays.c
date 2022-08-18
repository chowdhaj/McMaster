#include <stdlib.h> 
#include <stdio.h>

const int SIZE = 4;
const int PRINT_LOCATION = 0;

int main(void) {

    double arr[SIZE] = {11.1, 12.2, 13.3, 14.4};

    for (int i = 0; i < SIZE; i++) {
        printf("The value at position %d is %f\n",
            i, arr[i]);    
    }

    printf("\n");

    for (int i = 0; i < SIZE; i++) {
        printf("The location in memory for %f is %p\n",
            arr[i], &arr[i]);    
    }

    // Is the address of "arr" the same as "arr[0]"?
    if (PRINT_LOCATION) {
        printf("\n");
        printf("The base address is: %p\n", arr);
        printf("The base address is: %p\n", &arr[0]);
    }

    return 0;
}