// Author: Jatin Chowdhary chowdhaj

#include<stdio.h> 
#include<stdlib.h> 
#include<string.h>
#include<ctype.h>
#define SIZE 100

// function prototypes
struct LinkedList;
void addToList(struct LinkedList** head_ref, char new_charac);
void returnPalindrome(struct LinkedList *head, char palin[SIZE]);

int main() { 
    
    struct LinkedList* head = NULL; // creates a linked list
    char input[SIZE]; // declares an array of chars of 10 bytes
    
    printf("\nEnter A String...\n=> "); // prompts user
    fgets(input, SIZE, stdin); // gets input and stores it into input

    char c = 'c'; // declares a new char
    for(int i = 0; c != '\0'; i++) { // for loop iterates over input
        if (input[i] == '\n') { // this if statement replaces the newline with a null terminator
            input[i] = '\0'; // null terminator
        }
        c = input[i]; // 'c' equals the i'th char at input
        addToList(&head, c); // adds 'c' to the linked list
    }

    char backwards[SIZE];
    printf("\n%s\n=> ", "The Reversed String Is..."); // print text
    returnPalindrome(head, backwards); // returns linked list backwards
    
    printf("%s \t %s\n", backwards, input);

    if (strcmp(input, backwards)) { // compares strings
        puts("THIS IS NOT A PALINDROME!!!"); // prints no
    } else {
        puts("YES IT'S A PALINDROME!!!"); // prints yes
    }
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

// set linked list to another array of chars, backwards
void returnPalindrome(struct LinkedList *head, char palin[SIZE]) { 
    struct LinkedList *holder = head; // points to the first element in the list
    int i = 0;
    while(holder != NULL) {  // while pointer is not NULL
        palin[i] = holder->charac; // assigns char at node to palin
        i++; // increment
        printf("%c\t%c\n", holder->charac, palin[i]);
        //printf("%c", holder->charac); // print the char at the node
        holder = holder->next; // go to the next (previous) node
    } 
}   
