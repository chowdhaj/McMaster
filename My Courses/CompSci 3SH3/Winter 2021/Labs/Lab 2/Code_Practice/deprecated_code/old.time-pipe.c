/**
 * time-pipe.c
 *
 * This program uses shared memory for IPC between parent and child process
 *
 * Full credits to the textbook authors of Operating System Concepts
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/types.h>

#define BUFFER_SIZE 128
#define READ_END 0
#define WRITE_END 1

typedef struct timeval epoch_time;

int main(int argc, char *argv[]) {

    //char write_msg[BUFFER_SIZE] = "Hello-Hello People!\n";
    //char read_msg[BUFFER_SIZE];
    struct timeval get_start_time;

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
    } else if (pid == 0) { /* Child process */
        printf("Child created\n");

        /* Close the unused end of the pipe */
        close(fd[READ_END]);

        epoch_time start;
        gettimeofday(&start, NULL);
        //printf("read %lu\n", start.tv_usec);

        /* Write to the pipe */
        write(fd[WRITE_END], &start, sizeof(start));

        /* Close the write end of the pipe */
        close(fd[WRITE_END]);

        execlp(argv[1], argv[1], argv[2], NULL);

    } else { /* Parent process */

        /* Close the child */
        wait(NULL);
        epoch_time finish;
        gettimeofday(&finish, NULL);

        printf("Child complete\n");

        /* Close the unused end of the pipe */
        close(fd[WRITE_END]);

        /* Read from the pipe */
        read(fd[READ_END], &get_start_time, sizeof(get_start_time));
        //printf("read %lu\n", get_start_time.tv_usec);

        printf("Time Elapsed To Do Execute Command: %luus\n",
            finish.tv_usec - get_start_time.tv_usec);

        /* Close the read end of the pipe */
        close(fd[READ_END]);

    }

    return 0;
}
