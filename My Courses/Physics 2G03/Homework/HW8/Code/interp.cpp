#include <iostream>
#include <cmath>
#include "interp_head.h"

/*
 * Finds the correct index of 'x' in an array and calculates the
 * interpolation of the 'y' value
 */
float lookup(float xi [], float yi [], float x, int size) {

    int index = 0;
    float diff = x - xi[0];

    for(int i = 0; i < size; i++) {
        if (abs(x - xi[i]) < diff) {
            diff = x - xi[i];
            index = i;
        }
    }

    if (index == (size - 1)) {
        index = index - 1;
    }
    
    return interpolate(xi[index],   yi[index], 
                       xi[index+1], yi[index+1], x);

}

/*
 * Calculates the interpolation of 'x' on two distinct points
 */
float interpolate(float x1, float y1, float x2, float y2, float x) {

    if (not_equal(x1, x2)) {
        std::cout << "The slope is infinite!" 
                  << std::endl;
        return 0.0;
    }

    const float tol = 0.001;

    float y = 0.0;
    float m = calculate_slope(x1, y1, x2, y2);
    float b1 = calculate_y_int(x1, y1, m);
    float b2 = calculate_y_int(x2, y2, m);

    if (abs(b1 - b2) <= tol) {
        y = float((m * x) + b1);
        return y;
    } else {
        std::cout << "Something went wrong with the Y-Intercept!\n"
                  << std::endl;
        return 0.0;
    }

    return y;
}

/*
 * Calculates if two floats are equal by subtracting them and
 * comparing the result to a tolerance range
 */
bool not_equal(float x1, float x2) {

    const float tol = 0.00001;
    if (abs(x1 - x2) >= tol) {
        return false;
    } else {
        return true;
    }
}

/*
 * Calculates the slope, given two distinct points
 */
float calculate_slope(float x1, float y1, float x2, float y2) {

    return float((y2 - y1) / (x2 - x1));
}

/*
 * Calculates the Y-Intercept given slope and 'x'
 */
float calculate_y_int(float x, float y, float m) {

    return float(y - (m * x));

}

/*

// Defunct main function used to test the code above

int main(int argc, char const *argv[]) {

    std::cout << "Y-Intercept Is: " 
              << interpolate(3, 13.75, 4, 19, 3.25) 
              << std::endl;
    // Outputs: 15.0625

    return 0;
}
*/