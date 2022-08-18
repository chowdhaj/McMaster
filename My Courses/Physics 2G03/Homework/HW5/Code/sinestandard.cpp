#include <iostream>
#include <cmath>

int main() {

    // Program for estimating the sine of a user specified real number
    // Uses standard sin function from cmath
    // Filename sinestandard.cpp Src: JWW 2020

    float val;
  
    std::cout << "Welcome to the sine estimator program\n";
    std::cout << "Input a real number\n";
    std::cin >> val;

    std::cout << "Sine( " << val << " ) = " << sin(val) << "\n";
}
