
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define STRING_SIZE 100

// TODO: DEFINING A STRUCT
typedef struct {
    char name[100];
    char author[100];
    int published_year;
    int isbn_number;
    int pages;
    float dewey_number;
} BOOK;

void print_book_info(void * book_pointer);

int main(int argc, char const *argv[]) {

    // TODO: DECLARING THE STRUCT
    BOOK my_book;

    // TODO: MODIFYING THE MEMBERS
    //my_book.name = "The Big Short";    // Error???
    sprintf(my_book.name,"The Big Short");
    // A = Destination
    // B = Source
    // Copy 'B' into 'A'

    //my_book.author = "Michael Burry";  // Error???
    sprintf(my_book.author,"Michael Barry");

    my_book.published_year = 2009;
    my_book.isbn_number = 101010101;
    my_book.pages = 302;
    my_book.dewey_number = 12334.231;

    printf("There are %d pages in the book\n", my_book.pages);

    // int x = 100;

    // TODO: PASS THE ADDRESS OF THE BOOK
    print_book_info(&my_book);

    //pthread_create(A, B, C, &struct);
    
    return 0;
}

void print_book_info(void * book_pointer) {

    // TODO: WHAT IS A BOOK POINTER???

    // int * idk  = book_pointer
    // INT POINTER = VOID POINTER

    BOOK * green    = book_pointer;
    // BOOK POINTER = VOID POINTER

    printf("The name of the book is: %s\n",
        green->name);
    // -> is just syntactic sugar

    printf("The author is: %s\n",
        green->author);

    printf("The year of publication is: %d\n",
        green->published_year);

    printf("The ISBN number is: %d\n",
        green->isbn_number);

    printf("The number of pages in the book is: %d\n",
        green->pages);

    printf("The Dewey Decimal code is: %f\n",
        green->dewey_number);

    // TODO: WHAT IF WE USED A VOID POINTER?

    // TODO: DIFFERENCE BETWEEN ( -> ) AND ( . )

}



// ANSWERS: 
//sprintf(my_book.name, "The Big Short");
//sprintf(my_book.author, "Michael Burry");