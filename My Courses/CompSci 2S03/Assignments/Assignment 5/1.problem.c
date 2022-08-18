// Author: Jatin Chowdhary chowdhaj

#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
// import math to use PI

// function prototypes
void circumference(double rad); 
void area(double rad);
void volume(double rad);
void printMenu();

int main() {

	void (*funcPoint[3])(double rad) = {circumference, area, volume}; 
	// array of pointers, contains the address of the functions

	double rad; // declare radius
	int choice; // declare choice 

  	printf("\nEnter Radius (Must Be Greater Than 0) :: "); // ask user to input radius	
	scanf("%lf", &rad); // store into 'rad'
	puts("");

	printMenu(); // print options menu
	printf("==> "); // indicate where to type
	scanf("%d", &choice); // store input into 'choice'

	(*funcPoint[choice-1])(rad); // call the respective function based on choice

	return 0;
}

// this function prints the menu of options
void printMenu() {

	puts("Selection An Option:");
	puts("1. Calculate Circumference"); // calc. circumference
	puts("2. Calculate Area"); // calc. area
	puts("3. Calculate Volume"); // calc. sphere
	return;
}

// this function calculates the circumference of a circle
void circumference(double rad) {

	printf("\nCalculating Circumference...\n"); // print what its doing
	printf("Radius: %lf units \n", rad); // print radius
	printf("Circumference: %lf units\n\n", 2 * M_PI * rad); // print result of circumference
	return;
}

// this function calculates the area of a circle
void area(double rad) {

	printf("\nCalculating Area...\n"); // print what its doing
	printf("Radius: %lf units \n", rad); // print radius
	printf("Area: %lf units squared\n\n", M_PI * rad * rad); // print result of area
	return;
}

// this functionc calculates the volume of a circle
void volume(double rad) {

	printf("\nCalculating Volume...\n"); // print what its doing
	printf("Radius: %lf units \n", rad); // print radius
	printf("Volume: %lf units cubed\n\n", (4 * M_PI * rad * rad * rad) / 3); // print result of volume
	return;
}
	
	

