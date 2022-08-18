#include <iostream>
#include <iomanip>

float calculateNextTerm(int n) {    
    float t = ((n - 1.0) / ((2.0 * n) - 1));
    return t;
} 

int main() {
  
  // Program for estimate Pi to a given accuracy
  // Filename pi.cpp Src: JWW 2020

  int n;
  float term, small, sum, pi;
  
  std::cout << "Welcome to the pi estimator program\n";
  std::cout << "Please enter how precise you want the estimate to be\n>>> " ;
  std::cin >> small;

  if (small < 0) {
    std::cout << "That's not a valid number to estimate the precision of 'pi'\n" <<
      "Note: The lowest number you can input is 0" << std::endl;
    return 1;
  }
  
  n = 1;
  term = 1;
  sum = term;

  for (;;) {
    n++;
    term = term * calculateNextTerm(n);
    //std::cout << "!! term = " << term << std::endl; 
    sum += term;
    if (term <= small) break;
  }
  
  pi = sum * 2;
  
  std::cout << std::setprecision(20) << "Our pi estimate is " << pi << "\n";
  std::cout << "This differs from true pi by " <<
    pi - 3.141592653589793238462643383279502884197169399375105820974944e0 << "\n";
  std::cout << "The smallest term included was " << term << "\n"; 
  std::cout << "The number of terms summed was " << n << "\n";

  return 0;
}