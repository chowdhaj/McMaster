#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

int main() {

    double uflow = 0;
    for (int i = 0; i < 100; i++) {
        uflow = pow(2,((-1.0) * i));
        printf("2^-%d = %f\n", i, uflow);
    }

    return 0;
}
