
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define TRUE  1
#define FALSE 0

int main(int argc, char const *argv[]) {

    // REGULAR WHILE LOOP:
    while (FALSE) {
        printf("## Did this print?\n");
    }

    // DO-WHILE LOOP:
    do {
        printf("$$ Did this print?\n");
    } while (FALSE);
    
    return 0;
}

// TODO: WHAT IS THE POINT OF A DO WHILE LOOP?