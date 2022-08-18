#include <stdio.h>

int main() {

    // Logical shift operators

    // >> // Shifting right (divide)
    // Shifting to the right means adding bits to the left

    // << // Shifting left (multiply)
    // Shifting to the left means adding bits to the right

    int a = 5;

    int x = 16;
    int y = x >> 2;

    int z = x | a;

    printf("The value is:%d\n",z);

    return 0;
}
