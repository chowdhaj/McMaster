// I did write this, but abandoned it later on (Hence, the lack of comments)
// I left it for reference

#include <stdio.h>
#include <stdlib.h>

int main() {

    int num1 = 1, num2 = 1, num3, input;

    printf("What term of the fibonacci sequence do you want?\n(Enter a positive integer)\n==> ");
    scanf("%d", &input);

    if (input <= 0) {

        puts("Not Valid");

    } else if (input == 1) {

        printf("%d\n", 0);

    } else if (input == 2) {

        printf("%d, %d\n", 0, num1);

    } else {

        printf("%d, %d, %d, ", 0, num1, num2);
        input -= 3;
        while (input > 0) {
 
            num3 = num1 + num2; 
            printf("%d, ", num3);
            num1 = num2;
            num2 = num3;
            input--;
        }

    }

    puts("");
    
    return 0;

}
