#include <stdio.h>
#include <stdlib.h>

int main() {
	
									/* GETTING STARTED WITH POINTERS */

	int tuna = 19;

	puts("\nAddress \t Value \t Name");
	printf("%p \t %d \t %s \n\n", &tuna, tuna, "tuna");
	// &tuna refers to the memory address of 'tuna' // %p is used as the format specifier // p = pointer
	// %d is used to print the value of tuna // since tuna holds 19, it'll print 19
	// %s is used to print a string // "tuna" is a string

	// A pointer refers to the MEMORY ADDRESS of a variable
	// So wherever the value of tuna (19) is stored, the pointer points/refers to that place in memory.

	// Since pointers are fundamental for programming (b/c they allow you to modify variables directly)
	// When you pass a variable to a function, what you're doing is passing a copy of that variable
	// Pointers allow you to pass the address in memory, thus allowing you to directly modify the variable itself

	int *tunaPointer = &tuna; // the address of 'tuna' is assigned to the pointer, 'tunaPointer'
	// The ampersand (&) is used to refer to the address of 'tuna'
	// &tuna = the memory address of tuna in memory
	// NOTE: The asterisk(*) comes BEFORE THE NAME!

	puts("\nAddress \t Value \t\t\t Name");
	printf("%p \t %p \t %s\n\n", &tunaPointer, tunaPointer, "tunaPointer");
	// %p is the format specifier for pointers
	// It's used to print out the memory address of variables AND the value of pointers 
	// Use %p when dealing with memory addresses // DO NOT use %d for printing out the value that pointers hold

	// Since a pointer variable is a variable, it is also stored in memory, thus, it has its OWN memory address
	// A pointer variable holds the memory address of another variable // DO NOT get confused by this

	// The VALUE that 'tunaPointer' holds is the SAME as the MEMORY ADDRESS of 'tuna'

									/* DEFERENCING POINTERS */

	// Deferencing a pointer means go to the memory address and GET THE VALUE
	// You can deference a pointer using an asterisk (*). For example:

	printf("\n*tunaPointer: %d (Deferenced)\n\n", *tunaPointer); 
	// Note, you need to use the correct format specifier when deferencing a pointer
	// %p is not valid b/c you are no longer printing a memory address, but the VALUE that it holds/stores

	// *tunaPointer is equal to tuna. For example:
	if (*tunaPointer == tuna) {
		puts("Values Are Same (*tunaPointer == tuna)");
		// Since tunaPointer and tuna, point to the SAME address in memory, then, the VALUE is the SAME
		// Note: &tunaPointer != &tuna, BUT... tunaPointer == &tuna
		if (tunaPointer == &tuna) {
			puts("Value of tunaPointer is the same as Memory address of tuna (tunaPointer == &tuna)");
		}
		//if (&tunaPointer == &tuna) {
		//	puts("This will NOT be printed b/c the addresses of the VARIABLES are DIFFERENT");
		//}
	} else {
		puts("Values Are Not Same");
	}

	// You can even modify 'tuna' using 'tunaPointer' by deferencing it. For example:
	*tunaPointer += 1; // 19 + 1 = 20 // tuna is now 20
	printf("\ntuna: %d\n*tunaPointer: %d\n", tuna, *(tunaPointer)); // You can put brackets around 'tunaPointer'; if it helps to see it
	// Both tuna and *tunaPointer are the exact same values b/c they point to the exact same address in memory

										/* ARRAYS & POINTERS */

	// Arrays are a collection of identical variable types; it's like a group of variables of the same type. For example:

	int arr[5] = {7, 12, 45, 67, 88}; // An array of 5 integers

	printf("\nIndex #\t Value \t Address\n"); // Titles/labels
	
	for (int i = 0; i < 5; i++) { // iterate through the array
		printf("arr[%d] \t %d \t %p\n", i, arr[i], &arr[i]); // print index, value, and address of index
		// arr[%d] prints the index/element # of the array // starts from 0 and goes to 4 {0 = 7, 1 = 12, 2 = 45, 3 = 67, 4 = 88}
		// %d prints the value of the array at the i'th index -> arr[i]
		// %p prints the address of the value of the array at the i'th index -> &arr[i]
	}

	// The thing about arrays is that the address of arr is the address of arr[0]. For example:
	printf("\nAddress of arr: %p\nAddress of arr[0]: %p\n", &arr, &arr[0]); // &arr == &arr[0]

	// You can even add to the address of 'arr' and get the next value. For example:
	printf("\nAddress of arr[2]: %p\nValue of arr[2]: %d\n", arr+2, *(arr+2));

	// Remember, 'arr' points to an ADDRESS, NOT A VALUE! 
	// So doing something like arr+2 is acceptable b/c all you're adding 2 to the memory address. (arr+2) == &arr[2]
	// *(arr+2) goes to the address of arr[2] and retrieves the VALUE. Hence, *(arr+2) == arr[2] b/c they reference the SAME value!

	if ((arr+2) == (&arr[2])) { // the addresses are the same!
		puts("\n(arr+2) == (&arr[2]) --> The address of (arr+2) is equal to the address of arr[2]");
	}

	if ((*(arr+2)) == arr[2]) { // the values are the same!
		puts("*(arr+2)) == arr[2] --> The deferenced address of (arr+2) is equal to arr[2]");
	}

	// Note //
	// Since 'arr' is just a memory address, you don't need to add an ampersand infront of it
	// &arr is identical to arr. For example:

	if (&arr == arr) puts("\nSame address!");

	// You don't need the ampersand for arrays b/c arrays ARE pointers
	printf("\nThe address of 'arr' is: %p", arr); // No ampersand (&) required
	printf("\nThe address of 'arr[2]' is: %p\n\n", arr+2); // You can even write &(arr)+2, but it's unnecessary

	// DO NOT DO THIS: &(arr+2)
	// This does not make sense. You are 2 to the address of 'arr' and then taking the address of that. This will throw an error!

										/* STRINGS & POINTERS */

	char movie1[] = "The Dark Knight Rises"; // Declare and initialize an array of chars
	// Remember, 'movie1' is a pointer constant. It points to the first value of the array

	// You can never put the name of the array on the left hand side. For example:
	//movie1 = "Something Else";
	// This is because 'movie1' points to the first element's address. 
	// So changing it will mess up the entire array b/c the compiler won't know where the other elements are
	// Hence, you can never assign the array name anything else. Even this is incorrect:
	//movie1[] = "Something Else";
	// Changing the value of this array requires a special function, strcpy

	char *movie2 = "Steve Jobs Bio"; // 'movie2' is a pointer variable
	puts(movie2); // This is acceptable b/c 'puts' takes a string and prints out chars until it reaches the null terminator
	// 'movie2' stores the address of where the string begins
	// Since 'movie2' is a variable, it can be changed/altered

	movie2 = "New Documentary";
	puts(movie2);

	// An array of char is not easily mutable b/c the name of the array is a POINTER CONSTANT, and constants are hard to change
	// A pointer to a string is a variable and can be modified. It's no different from something like this:

	int cool = 10; // Declares an int called 'cool' and assigns it a value of 10
	int *coolPointer = &cool; // Creates a pointer to the address of 'cool'

	// *coolPointer is a variable and can be mutated, just like 'movie2'
	// Both of these point to something, and can be changed. For example:

	int cooler = 21; // Declare an int called 'cooler' and assings it a value of 21
	coolPointer = &cooler; // Assign the address of 'cooler' to 'coolPointer'

	// Note: DO NOT USE THE ASTERISK (*) WHEN RE-ASSIGNING POINTERS
	// The asterisk is used during DECLARATION & DEFERENCING, only!

	puts("");
	return 0;
}