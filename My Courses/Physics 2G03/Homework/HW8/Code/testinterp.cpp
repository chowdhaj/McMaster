#include <iostream>
#include <cmath>
#include "interp.cpp"

int main(int argc, char const *argv[]) {

    float x1 = 3;
    float y1 = 13.75;
    float x2 = 4;
    float y2 = 19;
    float x = 3.25;

    std::cout << "Y-Intercept Is: " 
              << interpolate(x1, y1, x2, y2, x) 
              << std::endl;
    // Outputs: 15.0625

    
    float xi[] = { 0,    1,  2,     3, 4 };
    float yi[] = { 7, 7.75, 10, 13.75, 19};
    int size = 5;

    // Test Case When `x = 3.25`
    x = 3.25;
    std::cout << "Y-Intercept Is: "
              << lookup(xi, yi, x, size) 
              << std::endl;

    // Test Case When `x = 4.31`
    x = 4.31;
    std::cout << "Y-Intercept Is: "
              << lookup(xi, yi, x, size) 
              << std::endl;

    // Test Case When `x = 0.55`
    x = 0.55;
    std::cout << "Y-Intercept Is: "
              << lookup(xi, yi, x, size) 
              << std::endl;

    return 0;
}