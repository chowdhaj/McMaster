#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 128
#define READ_END 0
#define WRITE_END 1

int main(void) {

    char write_msg[BUFFER_SIZE] = "Hello Fellow Peers!\n";
    char read_msg[BUFFER_SIZE];

    int fd[2];
    pid_t pid;

    /* Create the pipe */
    if (pipe(fd) == -1) {
        fprintf(stderr, "Pipe failed\n");
        return 1;
    }

    /* Fork a child process */
    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }

    if (pid > 0) { /* Parent process */
        /* Close the unused end of the pipe */
        close(fd[READ_END]);

        /* Write to the pipe */
        write(fd[WRITE_END], write_msg, strlen(write_msg)+1);

        /* Close the write end of the pipe */
        close(fd[WRITE_END]);

        /* Close child */
        wait(NULL);
    } else { /* Child process */
        /* Close the unused end of the pipe */
        close(fd[WRITE_END]);

        /* Read from the pipe */
        read(fd[READ_END], read_msg, BUFFER_SIZE);
        printf("read %s", read_msg);

        /* Close the read end of the pipe */
        close(fd[READ_END]);
    }

    return 0;
}
