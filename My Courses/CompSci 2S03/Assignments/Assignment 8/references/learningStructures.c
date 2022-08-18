#include <stdio.h>
#include <stdlib.h>

// Structures are a group of variables
// They can be (and usually are) of different types
// In a struct, you can have an int, char[], and a float
// On the other hand, with arrays, you can only have one type of variable
// Structures are like blueprints for a collection of data
// Structures are defined at the top, but can also be defined at the bottom, but it'll require a prototype
// Commonly, structures are defined in a separate header file. But they can also be defined inside the file

// Defining a structure called 'employee'
struct employee {

	// Declare the members of the struct in here; within the braces
	unsigned int employeeNumber; // holds employeeNumber
	char * firstName; // holds first name
	char * lastName; // holds last name
	unsigned int age; // holds age
	float weight; // holds weight in lbs
	float height; // holds weight in cm
}; // Don't forget the semicolon here

// Defining a struct is similar to a function. The only difference is: Structs don't have parameters.

// Defines a structure called 'fraction'
// The typedef statement defines it as a 'fraction'. Now, it's no longer 'struct fraction', it's just 'fraction'
// The 'typedef' keyword allows you to create an alternate name for a type. 'struct fraction' becomes 'fraction'
typedef struct {

	// These are the group of variables
	int numerator; // holds top of fraction
	int denominator; // holds bottom of fraction

} fraction;

void printEmployeeInfo(struct employee e); // function prototype for printEmployeeInfo
// NOTE: The function prototypes come AFTER the struct OR the prototype of the struct
// This is because this function has struct employee as its parameter. Thus, C needs to know the existence of struct employee, first
// Therefore, it's a good idea to define structs in a separate header file and import that file
// #include "employee.h" // An example of what you can do
// The function prototype for struct employee is: --> struct employee;

void printFraction(fraction f); // function prototype for printFraction
// The struct for fraction is defined BEFORE this function. This is b/c C needs to know the existence of 'fraction'

int main() {

	struct employee john; // Declares a struct of type employee called 'john'
	struct employee bill; // Declares a struct of type employee called 'bill'

	// 'john' and 'bill' have access to the members of struct employee
	// In order to set these members for 'john' and 'bill', you use the dot (.) operator. For example: 

	john.employeeNumber = 1; // set employee number to 1
	john.firstName = "John"; // set first name to "John"
	john.lastName = "Smith"; // set last name to "Smith"
	john.age = 33; // set age to 33
	john.weight = 140.67; // set weight to 140.67 pounds
	john.height = 170.5; // set height to 170.5cm

	printEmployeeInfo(john); // print out john's information // calls a method to do this

	bill.employeeNumber = 2; // set employee number to 2
	bill.firstName = "Bill"; // set first name to "Bill"
	bill.lastName = "Gold"; // set last name to "Gold"
	bill.age = 41; // set age to 41
	bill.weight = 170.27; // set weight to 170.27 pounds
	bill.height = 183.8; // set height to 183.8cm

	printEmployeeInfo(bill); // print out bill's information // calls a method to do this

	fraction f; // Create a fraction, call it 'f'
	f.numerator = 3; // Assign 3 to the numerator variable of 'f'
	f.denominator = 5; // Assign 5 to the denominator variable of 'f'

	printFraction(f); // print fraction 'f'

	puts(""); // prints newline

	typedef unsigned long long UINT64;

	return 0; // returns 0 -> program ran successfully
}

/*
	This function takes a 'struct employee' and prints out all relevant information 
	about that employee. It prints it in an organized manner. All information about the employee
	(number, first name, last name, age, weight, and height) is/are printed. For example:
	printEmployeeInfo(john);

	Employee #1
	-----------
	First Name: John
	Last Name: Smith
	Age: 33
	Weight: 140.67lbs
	Height: 170.5cm
 */
void printEmployeeInfo(struct employee e) {

	printf("\nEmployee #%d\n------------", e.employeeNumber); // prints employee number followed by a divider
	printf("\nFirst Name: %s\nLast Name: %s\nAge: %d\nWeight: %.2flbs\nHeight: %.2fcm\n",
							e.firstName, e.lastName, e.age, e.weight, e.height);
	// prints all information pertaining to employee 'e'
	// Information includes: employee number, first name, last name, age, weight, and height

}

/*
	This function prints a 'fraction'; the struct
	It takes a 'fraction' and prints the group of variables (numerator + denominator)
	It also prints the floating point value of the 'fraction' by dividing the denominator from the numerator
 */
void printFraction(fraction f) {

	printf("\nThe Fraction Is: %d/%d", f.numerator, f.denominator); // Prints the fraction in the format (numerator/denominator)
	printf("\nFloating Point: %.2f\n", (float)f.numerator/f.denominator); // Prints the floating point of the fraction
}