#include <stdlib.h> 
#include <stdio.h>

const int SIZE = 4;
const int PRINT_LOCATION = 1;

int main(void) {

    int arr[SIZE] = {10,11,12,13};

    for (int i = 0; i < SIZE; i++) {
        printf("The value at position %d is %d\n",
            i, arr[i]);    
    }

    printf("\n");

    for (int i = 0; i < SIZE; i++) {
        printf("The location in memory for %d is %p\n",
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