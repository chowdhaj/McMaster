// Author: Jatin Chowdhary chowdhaj

#include<stdio.h> 
#include<stdlib.h> 
#include<string.h>
#include<ctype.h>    

// function prototypes
struct LinkedList;
void addToList(struct LinkedList** head_ref, char new_charac);
void printList(struct LinkedList *head);

int main() { 
    
    struct LinkedList* head = NULL; // creates a linked list
    char input[10]; // declares an array of chars of 10 bytes
    
    printf("\nEnter A String...\n=> "); // prompts user
    fgets(input, 10, stdin); // gets input and stores it into input

    char c = 'c'; // declares a new char
    for(int i = 0; c != '\0'; i++) { // for loop iterates over input
        if (input[i] == '\n') { // this if statement replaces the newline with a null terminator
            input[i] = '\0'; // null terminator
        }
        c = input[i]; // 'c' equals the i'th char at input
        //printf("%c\n", c);
        //if (!(c == ' '))
        addToList(&head, c); // adds 'c' to the linked list
    }

    printf("\n%s\n=> ", "The Reversed List Is..."); // print text
    printList(head); // prints linked list backwards
    puts("\n"); // prints newline x2

    return 0; // return 0
} 

// Creates a self referential struct LinkedList // This is the linked list
struct LinkedList { 
    char charac; // Holds a character
    struct LinkedList* next; // Points to the next LinkedList which will hold a character and LinkedList
}; 
    
// adds a character to the list
void addToList(struct LinkedList** head_ref, char new_charac) { 
    struct LinkedList* new_LinkedList = (struct LinkedList*) malloc(sizeof(struct LinkedList)); // creates space for the linked list
    // malloc allocates memory      
    new_LinkedList->charac = new_charac; // the character in Node equals to the character passed to this function
    new_LinkedList->next = (*head_ref); // the pointer equals (points to) the next Node
    (*head_ref) = new_LinkedList; // pointer equals the new LL
} 

// prints the linked list, backwards
void printList(struct LinkedList *head) { 
    struct LinkedList *holder = head; // points to the first element in the list
    while(holder != NULL) {  // while pointer is not NULL
        printf("%c", holder->charac); // print the char at the node
        holder = holder->next; // go to the next (previous) node
    } 
}   
