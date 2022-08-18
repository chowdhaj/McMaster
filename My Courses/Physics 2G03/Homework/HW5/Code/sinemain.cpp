#include <iostream>
#include "sine.h"

int main() {

    // Program for estimating the sine of a user specified real number

    float val;

    std::cout << "Welcome to the Sine estimator program\n";
    std::cout << "Input a real number\n";
    std::cin >> val;

    std::cout << "Sine( " << val << " ) = " << sine(val) << "\n";
}
