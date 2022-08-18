// Author: Jatin Chowdhary chowdhaj

#include<stdio.h> 
#include<stdlib.h> 
#include<string.h>
#include<ctype.h>    

// function prototypes
struct Stack;
void addToStac(struct Stack** head_ref, int new_integer);
void printStac(struct Stack *head);
void deleteMiddle(struct Stack *head, int size);

int main() { 
    
    struct Stack* head = NULL; // creates a stac

    // adds the following nums to the stack
    addToStac(&head, 1);
    addToStac(&head, 2);
    addToStac(&head, 3);
    addToStac(&head, 4);
    addToStac(&head, 5);

    puts("\nYour stack: "); // ur stack
    printStac(head); // prints stac

    puts("\nNew stack: "); // new stac
    deleteMiddle(head, 5); // deletes middle

    puts("\n"); // newline

    return 0; // return 0
} 

// Creates a self referential struct Stack // This is the stac
struct Stack { 
    int integer; // Holds a int
    struct Stack* next; // Points to the next Stack which will hold a integerter and Stack
}; 
    
// adds a integerter to the stac
void addToStac(struct Stack** head_ref, int new_integer) { 
    struct Stack* new_Stack = (struct Stack*) malloc(sizeof(struct Stack)); // creates space for the stac
    // malloc allocates memory      
    new_Stack->integer = new_integer; // the integerter in Node equals to the integerter passed to this function
    new_Stack->next = (*head_ref); // the pointer equals (points to) the next Node
    (*head_ref) = new_Stack; // pointer equals the new LL
} 

// delete middle of the stac
void deleteMiddle(struct Stack *head, int size) { 
    struct Stack *holder = head; // points to the first element in the stac
    int s = size / 2; // size divided by 2
    int i = 0; // init an int
    while(holder != NULL) {  // while pointer is not NULL
        if (i != s) // if 'i' is not equal to 's'
            printf("%d", holder->integer); // print the int at the node
        i++; // inc 'i'
        holder = holder->next; // go to the next (previous) node
    } 
}

// prints the stac
void printStac(struct Stack *head) { 
    struct Stack *holder = head; // points to the first element in the stac
    while(holder != NULL) {  // while pointer is not NULL
        printf("%d", holder->integer); // print the int at the node
        holder = holder->next; // go to the next (previous) node
    } 
}   
