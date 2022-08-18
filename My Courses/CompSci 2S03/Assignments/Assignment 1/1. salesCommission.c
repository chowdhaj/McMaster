// Author: Jatin Chowdhary Chowdhaj

#include <stdio.h>
#include <stdlib.h>

int main() {

    printf("\n##############################\n"); // print divider
    printf("# Sales Comission Calculator #\n"); // print name of program
    printf("##############################\n"); // print divider
    printf("# This program will compute  #\n"); // print description of program
    printf("# weekly sales using the     #\n"); // print description of program
    printf("# following formula:         #\n"); // print description of program
    printf("# $200 + 9%% of weekly sales  #\n"); // print formula used to calculate sales
    printf("##############################\n\n"); // print description of program

    char prompt; // declare variable of type char and call it prompt
    printf("Press Enter To Begin\n"); // tell user to press enter to begin
    scanf("%c", &prompt); // store input (Enter) from user into prompt

    double sales; // declare variable of type double and call it sales
    do { // start do while loop
        printf("-------------------------------\n"); // print divider
        printf("Enter Weekly Sales (In Dollars)\n"); // tell user to enter weekly sales
        printf("-------------------------------\n"); // print divider
        printf("Enter -1 To End Program\n"); // tell user to enter -1 to end program, whenever
        printf("-------------------------------\n"); // print divider
        printf("Weekly Gross Sales --> $\a"); // tell user to enter weekly gross sales here (makes an alert sound)
        scanf("%lf", &sales); // store input from user into sales
        if (sales != -1.0) { // if sales is not -1.0, then do this:
            printf("-------------------------------\n"); // print divider
            printf("Weekly Earnings: $%.2lf\n", (200 + sales * 0.09)); // print weekly earnings to screen by applying the formula
            printf("-------------------------------\n\n"); // print divider
        } else { // if sales is -1.0, then:
            printf("-------------------------------\n"); // print divider
            printf("Thank You! Have A Good Day!\n\a"); // print a thank you message to screen
            printf("-------------------------------\n\n"); // print divider
        }
    } while (sales != -1.0); // loop continues while sales is not equal to -1.0

    return 0; // return 0 // program has successfully executed
}
