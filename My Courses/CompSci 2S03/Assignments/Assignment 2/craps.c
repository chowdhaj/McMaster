// Author: Jatin Chowhary chowdhaj

// Fig 5.14: fig05_14.c
// Simulating the game of craps
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // contains prototype for function time

// enumeration constants represent game status
enum Status {
    CONTINUE, 
    WON, 
    LOST
};

int rollDice(void); // function prototype
int runCrapsGame(int sum, int myPoint); // function prototype
int printBanter(int gamblingAmount); // function prototype

int main(void) {

    // randomize random number generator using current time
    srand(time(NULL));

    int bankBalance = 1000; // create int variable called bankBalance and set it to 1000
    int gamblingAmount; // this is the wager amount
    char continueCraps; // stores users choice of continuing the game or cashing out

    puts("\n############################"); // prints divider
    puts("# Welcome To The Crap Game #"); // prints name of the program/game
    puts("############################"); // prints divider

    do { // start do while loop // plays the crap game until user decides to cash out or gets busted
        printf("\nYour Current Bank Balance Is $%d.\nHow much would you like to wager?\n==> $", bankBalance); // asks user how much they wanna wager
        do { // start do while loop // checks to make sure user enters a correct amount for wagering
            scanf(" %d", &gamblingAmount); // stores users wager amount into 'gamblingAmount'
            if (gamblingAmount <= bankBalance && gamblingAmount >= 0) { // if gamblingAmount is greater than 0 and less than bankBalance, then:
                puts(""); // prints a new line
                printBanter(gamblingAmount); // calls a function called 'printBanter' that will print funny playful lines
                break; // break out of the do while loop // user has entered a proper wager amount
            } else { // if gambling amount is greater than bank balance or less than 0, then: 
                if (gamblingAmount > bankBalance) { // if wager amount is greater than bank balance, then:
                    printf("You're not that rich. Try Again\n==> $"); // tell user they're not that rich and to try again
                } else { // if wager amount is less than 0, then:
                    printf("That's not even possible. Try again\n==> $"); // tells user thats not possible and to try again
                }
            }
        } while (1); // execute the second do while loop infinitely // only breaks out once user enters in a correct wager value

        puts("\n############################\n"); // prints divider

        int sum = rollDice(); // roll dice
        int myPoint = sum; // player must make this point to win

        // runs the craps game by calling a function
        enum Status gameStatus = runCrapsGame(sum, myPoint); // can contain CONTINUE, WON, or LOST

        // while game not complete
        while (CONTINUE == gameStatus) { // player should keep rolling
            sum = rollDice();

            // determine game status
            if (sum == myPoint) { // if dice roll = 'point', then:
                gameStatus = WON; // set gameStatus to WON
            } else { // otherwise: 
                if (sum == 7) { // lose by rolling 7
                    gameStatus = LOST; // set gameStatus to LOSE
                }
            }
        }

        // display won or lost message
        if (gameStatus == WON) { // if user has won the game:
            puts("Player wins"); // print that the user has won
            bankBalance += gamblingAmount; // add wager amount to bank balance
            printf("Your new bank balance is $%d\n", bankBalance); // prints new bank balance
        } else { // player lost
            puts("Player loses"); // print that the player has lost
            bankBalance -= gamblingAmount; // subtract wager amount from bank balance
            printf("\nYour new bank balance is $%d\n", bankBalance); // prints new bank balance
            if (bankBalance == 0) { // if bank balance is equal to 0 (player has busted), then:
                puts("\n############################\n"); // prints divider
                printf("Sorry, You Busted!\n(You Lost All Your Money)\n\n"); // tells user they busted and lost all their money
                puts("############################\n"); // prints divider
                exit(0); // exits game b/c player has no money and lost the game
            }
        }
        puts("\n############################\n"); // prints divider
        printf("Would you like to continue? (Y/N) :: "); // asks the user if they wanna continue playing craps
        scanf(" %c", &continueCraps); // stores response into 'continueCraps'
        if (continueCraps == 'y' || continueCraps == 'Y') { // if user input is 'y' or 'Y' then continue game
            printf("\nGO BIG OR GO HOME!!!\n\n############################\n"); // prints a slur and divider
        } else { // if the user enters anything other than 'y' or 'Y', then the user wants to quit/cash out
            // print winnings/losses to screen to let user know how they did
            printf("\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\nYou %s: $%d\n\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n", bankBalance >= 1000 ? "Made" : "Lost", abs((bankBalance - 1000)));
            break; // break out of loop b/c user wants to cash out
        }

    } while(1); // keep playing the game until user decides to quit or gets busted // this is an infinite loop

}

/*
 * this function is called 'printBanter' 
 * it takes the wager amount and based off that, it prints a funny message to the screen
 */
int printBanter(int gamblingAmount) {

    if (gamblingAmount >= 0 && gamblingAmount <= 100) { // if wager amount is greater than or equal to 0 and less than or equal to 100, then:
        puts("Is that all you got? Wuss."); // prints a funny message
    } else if (gamblingAmount > 100 && gamblingAmount <= 200) { // if wager amount is greater than 100 and less than or equal to 200, then:
        puts("Is this your first time or are you a piker?"); // prints a funny message
    } else if (gamblingAmount > 200 && gamblingAmount <= 300) { // if wager amount is greater than 200 and less than or equal to 300, then:
        puts("Those are rookie numbers, you gotta pump those numbers up!"); // prints a funny message
    } else if (gamblingAmount > 300 && gamblingAmount < 450) { // if wager amount is greater than 300 and less than 450, then:
        puts("Not bad. But you can do better :)"); // prints a funny message
    } else if (gamblingAmount >= 450 && gamblingAmount <= 550) { // if wager amount is greater than or equal to 450 and less than or equal to 550, then:
        puts("Playing it safe huh? Bad idea!"); // prints a funny message
    } else if (gamblingAmount > 550 && gamblingAmount <= 750) { // if wager amount is greater than 550 and less than or equal to 750, then:
        puts("Are you ready to mortgage your house?"); // prints a funny message
    } else if (gamblingAmount > 750 && gamblingAmount < 900) { // if wager amount is greater than 750 and less than 900, then:
        puts("Say goodbye to your kids college fund!"); // prints a funny message
    } else { // if wager amount is greater than or equal to 900, then: 
        puts("Oh, you're going for broke, huh?"); // prints a funny message
    }

    return 0;
}

/*
 * this function is called 'runCrapsGame'. it takes two integers and returns an integer
 * this function plays the craps game. the options are in a switch statement
 * based off the role, it returns a number which corresponds to the 'enum Status'
 */
int runCrapsGame(int sum, int myPoint) {
 
    // determine game status based on sum of dice
    switch(sum) {

        // win on first roll
        case 7: // 7 is a winner
        case 11: // 11 is a winner
            return 1;
            //break;

        // lose on first roll
        case 2: // 2 is a loser
        case 3: // 3 is a loser
        case 12: // 12 is a loser
            return 2;
            //break;

        // remember point
        default:
            //gameStatus = CONTINUE; // player should keep rolling
            //myPoint = sum; // remember the point
            printf("Point is %d\n", myPoint);
            return 0;
            break; // optional
    }
}

// roll dice, calculate sum and display results
int rollDice(void) {

    int die1 = 1 + (rand() % 6); // pick random die1 value
    int die2 = 1 + (rand() % 6); // pick random die2 value

    // displays result of this roll
    printf("Player rolled %d + %d = %d\n", die1, die2, die1 + die2);
    return die1 + die2;
}
