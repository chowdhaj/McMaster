/**
 * time-shm.c
 *
 * This program uses shared memory for IPC between parent and child process
 *
 * Full credits to the textbook authors of Operating System Concepts
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define WAIT_SECS 10

int main(int argc, char *argv[]) {

    ///printf("%i\n", argc);
    ///printf("%s", argv[0]);
    struct timeval current_time;
    //gettimeofday(&current_time, NULL);

    ///long int start_time = 0, end_time = 0;

    const int SIZE = 4096;
    const char *name = "Shared_Memory";

    /* Shared memory file descriptor */
    int fd;

    /* Pointer to shared memory object */
    char *ptr;

    /* Create the shared memory object */
    fd = shm_open(name, O_CREAT | O_RDWR, 0666);

    /* Configure the size of the shared memory object */
    ftruncate(fd, SIZE);

    //const long int start_time = current_time.tv_sec;

    pid_t pid;

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) { /* Child process */
        printf("Child created\n");
        /* Memory map the shared memory object */
        ptr = (char *)mmap(0, SIZE, PROT_READ |
		                    PROT_WRITE, MAP_SHARED, fd, 0);
        gettimeofday(&current_time, NULL);
        ///printf("1. Start(s) = %ld\n", current_time.tv_sec);
        sprintf(ptr, "%lu\n", current_time.tv_usec);
        ptr += sizeof(current_time.tv_usec); //strlen(message_0);
        ///printf("2. Start(s) = %ld\n", current_time.tv_sec);
        ///gettimeofday(&current_time, NULL);
        ///start_time = current_time.tv_sec;
        ///printf("Start(s) = %ld\n", start_time);
        execlp(argv[1], argv[1], argv[2], NULL);
    } else { /* Parent process */
        /* Parent will wait for child to complete */
        sleep(0);
        wait(NULL);

        ///gettimeofday(&current_time, NULL);
        ///end_time = current_time.tv_sec;
        ///time_elapsed = (end_time - start_time);
        ///printf("Time Elapsed(s) = %d\n", time_elapsed);
        printf("Child complete\n");

        /* Open the shared memory object */
        fd = shm_open(name, O_RDONLY, 0666);

        /* Memory map the shared memory object */
        ptr = (char *)mmap(0, SIZE, PROT_READ, MAP_SHARED, fd, 0);

        /* Read from the shared memory object */
        //printf("%s", (char *)ptr);

        char *end_ptr;

        long int start_time = strtol((char *)ptr, 
            &end_ptr, 0);
        //printf("%lu#", start_time);

        gettimeofday(&current_time, NULL);
        printf("Time Elapsed To Do Execute Command: %luus\n", 
            current_time.tv_usec - start_time);

        /* Remove the shared memory object */
        shm_unlink(name);
    }

    return (0);
}
