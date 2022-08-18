
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define TRUE  1
#define FALSE 0

int main(int argc, char const *argv[]) {

    // strncmp = STRING N COMPARE
    // strncmp (A,B,C)
    // A = string1
    // B = string2
    // C = integer

    if (strncmp("this", "that", 4)) {
        printf("1.They are different\n"); // THIS ONE
    } else {
        printf("1.They are same\n");
    }

    if (strncmp("quit", "quit", 4)) {
        printf("2.They are the different\n");
    } else {
        printf("2.They are same\n");   // THIS ONE
    }

    if (strncmp("quitters", "quit", 8)) {
        printf("3.They are the different\n"); // THIS ONE
    } else {
        printf("3.They are same\n");
    }

    if (strncmp("quitters", "quit", 4)) {
        printf("4.They are the different\n");
    } else {
        printf("4.They are same\n");     /// THIS ONE
    }

    return 0;

}
