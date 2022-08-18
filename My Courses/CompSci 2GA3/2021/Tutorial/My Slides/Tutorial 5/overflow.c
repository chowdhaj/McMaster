#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

const int MAX = INT_MAX;
const int MIN = INT_MIN;

int main() {

    printf("The largest integer value is: %d\n", MAX);
    printf("The smallest integer value is: %d\n", MIN);

    printf(" %d + 1 = %d\n", INT_MAX, INT_MAX + 1);
    printf("%d - 1 =  %d\n", INT_MIN, INT_MIN - 1);

    return 0;
}
