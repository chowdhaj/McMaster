#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h> 

int global_int = 0;

int main(int argc, char const *argv[]) {
    /* code */

    printf("This is the parent/main process\n");
    // printed once

    pid_t pid = fork();

    //kill(0, 9);
    
    if (pid == 0) {
        // CHILD //
        printf("[CHILD] The value of PID is: %d\n", pid);
        printf("[CHILD] My PID is: %d\n", getpid()); // THIS
        //exit(0);
        global_int += 100;
        printf("[CHILD] The integer is: %d\n", global_int);
    } else {
        // PARENT // 
        //wait(NULL);

        kill(pid, 9);

        printf("The value of PID is: %d\n", pid); // THIS
        global_int+=50;
        printf("[PARENT] The integer is: %d\n", global_int);
        // 10, 10, 10, 10
    }

    return 0;
}