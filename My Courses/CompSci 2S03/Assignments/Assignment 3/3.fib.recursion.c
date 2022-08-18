// Author: Jatin Chowdhary chowdhaj

#include <stdio.h>
#include <time.h>

/*
 * This function is called fibonacci. It takes one int and returns an int
 * Computes the nth fibonacci number using recursion
 */
int fibbonacci(int n) {
   if(n == 0){ // if n equals 0, then:
      return 0; // return 0
   } else if(n == 1) { // if n equals 1, then:
      return 1; // return 1
   } else { // if the above are false, do: 
      return (fibbonacci(n-1) + fibbonacci(n-2)); // recursively call the 'fibonacci' function, and 
                                                  // subtract 1 from 'n', and then add that to recursively 
                                                  // calling 'fibonacci' function, and subtract 2 from 'n'
   }
}

int main() {

   int n; // declare an int called 'n'
	 printf("\nHow many terms do you want? :: "); // ask user for how many terms
   scanf("%d", &n); // store input into 'n'


   printf("\nFibbonacci of %d: " , n); // print title

   clock_t start = clock(); // start clock
	
   for(int i = 0; i < n; i++) { // for loop that iterates 'n' number of times
      printf("%d, ", fibbonacci(i)); // prints fibonacci terms to screen by calling 'fibonacci' which computes them
   }

   clock_t finish = clock(); // stop clock

   double executionTime = (double)(finish - start) / CLOCKS_PER_SEC; // calculate execution time by stracting start time from finish time

   printf("\n\nThis took %lf CPU Time\n\n", executionTime); // print execution time to screen
}
