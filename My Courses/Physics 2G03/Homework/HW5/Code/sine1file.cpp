#include <iostream>

float sine(float x) {

    // Function to estimate the sine of a real value x
    // Your code goes here ...

    float approx = x - ((1.0/6.0)*x*x*x) + ((1.0/120.0)*x*x*x*x*x);
    return approx;
}

int main() {
    
    // Program for estimating the sine of a user specified real number
    // Filename sine1file.cpp Src: JWW 2020

    float val;
  
    std::cout << "Welcome to the sine estimator program\n";
    std::cout << "Input a real number\n";
    std::cin >> val;

    std::cout << "Sine( " << val << " ) = " << sine(val) << "\n";
}
