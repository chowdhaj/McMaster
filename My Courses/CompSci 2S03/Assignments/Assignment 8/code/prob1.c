// Author: Jatin Chowdhary chowdhaj

#include <stdio.h>
#include <stdlib.h>

// self-referential structure
struct listNode {
	int data; // each listNode contains a intacter
	struct listNode *nextPtr; // pointer to next node
};

typedef struct listNode ListNode; // synonym for struct listNode
typedef ListNode *ListNodePtr; // synonym for ListNode*

// prototypes
void insert(ListNodePtr *sPtr, int value);
int isEmpty(ListNodePtr sPtr);
void printList(ListNodePtr currentPtr);
int search(struct Node* startPtr, int x);

int main(void) {

	ListNodePtr startPtr = NULL; // initially there are no nodes
	int item; // int entered by user

	puts("Enter your choice:\n" // print the menu of options
		"	Press 1 to insert an element into the list.\n"
		" 	Press 2 to search an element from the list.\n"
		" 	Press 3 to end.\n"
		"	Remember these options!");
	printf("%s ", ">>>"); // prompt
	unsigned int choice; // user's choice
	scanf("%u", &choice); // accept input and store it

	// loop, while user does not choose 3
	while (choice != 3) {

		switch (choice) { // switch ladder
			case 1: // case 1: enter an int into the LL
				printf("Enter A INT :: ");
				scanf("\n%d", &item);
				insert(&startPtr, item); // insert item in LL
				printList(startPtr); // prints list
				break;
			case 2: // recursively searches for item in LL
				if (!isEmpty(startPtr)) {
					printf("Enter INT To Search For :: "); // prompt
					scanf("\n%d", &item); // accept input
					if (search(startPtr, item)) { // search
						printf("%s\n", "SUCCESS!");
					} else {
						printf("%d not found.\n\n", item); // couldn't find it
					}
				} else {
					puts("List is empty.\n"); // list is empty
				}
				break;
			default:
				puts("WRONG choice.\n"); // invalid option
				break;
		}
		printf("%s ",">>>"); // prompt
		scanf("%u", &choice); // store input
	}	
}

// inserts an element into the LL
void insert(ListNodePtr *sPtr, int value) {

	ListNodePtr newPtr = malloc(sizeof(ListNode)); // allocate memory

	if (newPtr != NULL) { // if ptr is not null
		newPtr->data = value; // assign it value
		newPtr->nextPtr = NULL; // next pointer is null

		ListNodePtr previousPtr = NULL; 
		ListNodePtr currentPtr = *sPtr;

		while (currentPtr != NULL && value > currentPtr->data) { // iterate through LL
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
		}

		if (previousPtr == NULL) { // assign pointers to next
			newPtr->nextPtr = *sPtr;
			*sPtr = newPtr;
		} else {
			previousPtr->nextPtr = newPtr;
			newPtr->nextPtr = currentPtr;
		}
	} else {
		printf("%d not inserted. No memory available.\n", value); // no memory for LL insertion
	}
}

// checks if LL is empty/NULL
int isEmpty(ListNodePtr sPtr) {
	return sPtr == NULL;
}

// print the list
void printList(ListNodePtr currentPtr) {
	if (isEmpty(currentPtr)) { // print list is empty if its empty
		puts("List is empty.\n"); // text
	} else {
		puts("The list is:"); // else print the list
		while (currentPtr != NULL) { // iterate through LL
			printf("%d --> ", currentPtr->data); // print data
			currentPtr = currentPtr->nextPtr; // go to next pointer
		}
		puts("NULL\n"); // print last value
	}
}

int search(struct Node* startPtr, int x) { // recursively search list

    if (startPtr == NULL) // return 0 if we didnt find anything
        return 0; // return 0
    
    if (startPtr->data == x) // return 1 if we found a match
        return 1;  // return 1
  
    return search(startPtr->nextPtr, x); // recursively search list
} 