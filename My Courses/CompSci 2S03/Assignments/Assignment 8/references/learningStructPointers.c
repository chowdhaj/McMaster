#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This is how to define a struct
// 'struct' followed by the name of struct. In this case, the name is 'person'
struct person {

	// Group of variables
	int age; // holds age
	char *name; // holds name
};

// Using 'typedef' you change the type from 'struct person' to 'person'
typedef struct{

	// Collection of variables
	int age; // holds age
	char *name; // holds name
} person;

void printPerson(struct person p); // function prototype
// Notice how its defined AFTER 'struct person'

void printPointerPerson (struct person *p); // function prototype // Defined after 'struct person'
// Takes a pointer to a struct
// Note: The asterisk/pointer(*) comes AFTER the name of the struct

int main() {
	
	// Struct is short for structure
	// It's used to group variables of different data types into one variable
	// You can store anything in structs, including other structs
	// Structs are like variables, but require the use of the dot operator to access the variables inside

	struct person dude; // declaring a new 'person' struct called 'dude'
	// We have a variable called 'dude', which is of type struct person

	// The dot (.) syntax is how you assign values to members of the struct
	dude.age = 28; // Assign 28 to "dude's" age
	dude.name = malloc(4 * sizeof(char)); // Allocating 4 bytes on the heap b/c 4 * 1 = 4 [ sizeof(char) = 1 ]
	strcpy(dude.name, "John"); // Copying "John" into 'dude.name'

	puts(""); // prints newline
	printPerson(dude); // prints the information pertaining to person 'dude'

	struct person *dudePointer = &dude; // Creating a pointer to the struct 'dude'
	// dudePointer is a POINTER to 'dude' // It holds the ADDRESS of 'dude'
	// We can deference the pointer to access the variables in the struct 'dude'

	(*dudePointer).age = 33; // dudePointer needs to be deferenced before values are assigned
	// Note: The parenthesis are only around 'dudePointer', b/c we only need to deference it
	// The following is WRONG --> (*dudePointer.age) // This tries to deference the whole thing, which doesn't make sense and throws an error
	(*dudePointer).name = realloc((*dudePointer).name, 5 * sizeof(char)); // Reallocate 5 bytes on the heap
	strcpy((*dudePointer).name, "Johnn"); // Copy "Johnn" into '(*dudePointer).name'

	printPointerPerson(dudePointer); // prints the group of variables a part of 'dude'
	// 'dudePointer' points to the address of 'dude'
	// The address of 'dude' is passed to printPointerPerson
	// You can even do this: printPerson(*dudePointer); // This passes the 'dudePointer' deferenced, which is just 'dude'

	// When dealing with structs and pointers, you can use special syntax to deference and access variables
	// The arrow (->) notation, accomplishes this
	// (*dudePointer).age = 33 >> IS THE SAME AS >> dudePointer->age = 36;

	dudePointer->age = 36; // Assigns 36 to 'dude.age'
	// dudePointer->age === (*dudePointer).age === dude.age // All three are reference to 'dude.age'
	dudePointer->name = realloc(dudePointer->name, 6 * sizeof(char));
	strcpy(dudePointer->name, "Johnny");

	printPointerPerson(dudePointer); // prints the group of variables a part of 'dude'
	// Since 'dudePointer' holds the address of 'dude', it'll print the variables in 'dude'

	printPerson(dude); // Prints the struct 'dude' to show that all modifications were made to 'dude'
	// Modifying dudePointer, modifies dude b/c the former points to the latter's ADDRESS in memory

	printf("\nValue of 'dude': %d", dude); // Prints the value of 'dude'
	// The value of dude is the FIRST variable in the struct. In this case it is 'age'
	// So the value of 'dude' is whatever 'age' is set as
	printf("\nAddress of 'dude.age': %p", &(dude.age)); // Prints the address of 'dude.age'
	printf("\nAddress Of 'dude': %p\n", &dude); // Prints address of 'dude'
	// The address of 'dude.age' is the SAME as the address of 'dude'
	// Structs are similar to arrays in the sense that 'dude' is a pointer to the FIRST value
	// In this case, the first variable defined in the 'struct person' is 'age'

	printf("\nVALUE Of 'dudePointer': %p", dudePointer); // Prints value of 'dudePointer'
	printf("\nAddress Of 'dudePointer': %p", &dudePointer); // Prints address of 'dudePointer'
	// Note: The VALUE of 'dudePointer' is DIFFERENT from the ADDRESS of 'dudePointer'
	
	if (dudePointer == &dude) puts("\n\n[EQUALITY] The ADDRESS of 'dude' == The VALUE of 'dudePointer'"); 
	// Prints that ADDRESS of 'dude' == VALUE of 'dudePointer'

	printf("\nThe Address of 'dude.age': %p\n", &(dude.age)); // Same as the address of 'dude'
	printf("The Address of 'dude.name': %p\n", &(dude.name));

	// However, keep in mind that you can't add to the address of 'dude' and expect to get the next variable
	// Structs and arrays work differently. In an array, elements are next to each other in memory
	// To solve this problem, you need to use a self referential struct

	puts("");
	return 0;
}

/* 
	This function takes a pointer to a struct and prints the information
	pertaining to the struct it poins to, by deferencing the pointer using
	arrow notation (->)
	i.e. Bob Is 22 Years Old
	Name = Bob
	Age = 22
 */ 
void printPointerPerson (struct person *p) {

	printf("[P] %s Is %d Years Old\n", p->name, p->age);
}

/*
 	This function takes a struct person and prints out the information
 	pertaining to it. In this case, it prints name and age using the dot syntax (.)
 	i.e. Bob Is 22 Years Old 
 	Name = Bob
 	Age = 22
 */
void printPerson(struct person p) {

	printf("%s Is %d Years Old\n", p.name, p.age); // prints the name and age in the struct person, 'p'
}
