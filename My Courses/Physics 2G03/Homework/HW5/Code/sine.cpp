float sine(float x) {

    // Function to estimate the sine of a real value x
    float approx = x - ((1.0/6.0)*x*x*x) + ((1.0/120.0)*x*x*x*x*x);
    return approx;
}