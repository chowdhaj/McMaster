#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

#define WAIT_SECS 10

int main(void) {

    pid_t pid;

    /* Fork a child process */
    pid = fork();

    if (pid < 0) { /* Error occured */
        fprintf(stderr, "Fork Failed\n");
        return 1;
    } else if (pid == 0) { /* Child process */
        execlp("/bin/ls","ls",NULL);
    } else { /* Parent process */
        /* Parent will wait for the child to complete */
        sleep(WAIT_SECS);
        wait(NULL);
        printf("Child complete\n");
    }

    return (0);
}
