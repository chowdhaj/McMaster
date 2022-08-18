// Author: Jatin Chowdhary chowdhaj

#include <stdio.h>
#include <stdlib.h>

// self referential struct 
struct Queue {
	int data; // holds data
	struct Queue *nextPtr; // pointer to next node
};

// type def statements
typedef struct Queue Queue;
typedef Queue *QueuePtr;

// function prototypes
void pop(QueuePtr *headPtr, QueuePtr *tailPtr);
void push(QueuePtr *headPtr, QueuePtr *tailPtr, int value);
void print(QueuePtr currentPtr);
void menu();
int isEmpty(QueuePtr headPtr);

int main(void) {

	QueuePtr headPtr = NULL; // points to head of list
	QueuePtr tailPtr = NULL; // points to tail of list
	int item; // holds value

	menu(); // prints menu
	unsigned int choice; // stores choice
	scanf("%u", &choice); // stores input

	while (choice != 3) { // while loop

		// switch ladder
		switch(choice) {

			// case 1: 
				// pushes data to queue
				// also referred to as insertion
			case 1:
				printf("Enter Number: "); // text
				scanf("\n%d", &item); // stores input
				push(&headPtr, &tailPtr, item); // calls the push function
				print(headPtr); // prints queue
				break; //break

			// case 2: 
				// deletes the head of the queue
				// removes the first element
			case 2: 
				if (!isEmpty(headPtr)) { // if queue is not empty: 
					pop(&headPtr, &tailPtr); // pop data
				}
				print(headPtr); // print queue
				break; // break

			default: // default case if 1 or 2 dont match
				puts("Invalid Choice\n"); // print text
				break;
		}

		menu(); // print menu
		scanf("%u", &choice); // store input
	}
	puts("\nFinished\n"); // print text
}

// this function pushes data to the queue data structure
void push(QueuePtr *headPtr, QueuePtr *tailPtr, int value) {
	
	QueuePtr newPtr = malloc(sizeof(Queue)); // allocate memory for queue

	if (newPtr != NULL) {  // if space is allocated
		newPtr->data = value; // assign 'value' to queue 
		newPtr->nextPtr = NULL; // nextPtr equals NULL
	
		if (isEmpty(*headPtr)) { // if queue is empty
			*headPtr = newPtr; // headPtr gets newPtr
		} else { 
			(*tailPtr)->nextPtr = newPtr; // else, tailPtr gets newPtr
		}

		*tailPtr = newPtr; // last pointer gets newPtr (NULL)
	} else { // space in memory not allocated, 'value' not pushed
		printf("%d not inserted; no memory\n", value); // print text
	}
}

// this function removes the value from a queue
void pop(QueuePtr *headPtr, QueuePtr *tailPtr) {
	
	QueuePtr tempPtr = *headPtr; // create a tempPtr which gets the address of headPtr
	*headPtr = (*headPtr)->nextPtr; // headPtr gets the next Pointer

	if (*headPtr == NULL) { // if headPtr is NULL
		*tailPtr = NULL; // tailPtr gets NULL
	}

	free(tempPtr); // clears memory allocated by tempPtr
}

// checks if queue is empty
int isEmpty(QueuePtr headPtr) {
	return headPtr == NULL; // returns 1 or 0 is headPtr is equal to NULL
}

// prints the menu [options]
// 1 = push to queue
// 2 = pop [delete from queue]
// 3 = exit program
void menu() {
	printf("Enter Your Choice:\n"
		"   1 -- To Push (Remove)\n"
		"   2 -- To Pop (Delete)\n"
		"   3 -- To End (Exit)\n"
		"> ");
	return; // return
}

// prints the queue
void print(QueuePtr currentPtr) {

	if (currentPtr == NULL) { // if the pointer is null
		puts("Queue is empty\n"); // queue is null
	} else {
		puts("The queue is:");

		while (currentPtr != NULL) { // iterates through the queue, going from head to tail
			printf("%d --> ", currentPtr->data); // prints each element [data]
			currentPtr = currentPtr->nextPtr; // goes to the next pointer; element in queue
		}
		puts("NULL\n"); // prints NULL
	}
}

// Reference: C How To Program By Deital