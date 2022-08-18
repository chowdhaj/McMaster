#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct timeval timeval_t;

int main(void) {

    /* The size (in bytes) of shared memory object */
    const int SIZE = 4096;

    /* The name of the shared memory object */
    const char *name = "OS";

    /* Strings written to shared memory */
    //const char *message_0 = "Lab 2 ";
    //const char *message_1 = "Practice!\n";

    /* Shared memory file descriptor */
    int fd;

    /* Pointer to shared memory object */
    char *ptr;

    /* Create the shared memory object */
    fd = shm_open(name, O_CREAT | O_RDWR, 0666);

    /* Configure the size of the shared memory object */
    ftruncate(fd, SIZE);

    /* Memory map the shared memory object */
    ptr = (char *)mmap(0, SIZE, PROT_READ | 
		                PROT_WRITE, MAP_SHARED, fd, 0);

    /* Write to the shared memory object */
    sprintf(ptr, "%i\n", 1234);
    ptr += sizeof(1234); //strlen(message_0);
    //sprintf(ptr, "%s", message_1);
    //ptr += strlen(message_1);

    /* Open the shared memory object */
    fd = shm_open(name, O_RDONLY, 0666);

    /* Memory map the shared memory object */
    ptr = (char *)mmap(0, SIZE, PROT_READ, MAP_SHARED, fd, 0);

    /* Read from the shared memory object */
    printf("%s", (char *)ptr);

    /* Remove the shared memory object */
    shm_unlink(name);

    return 0;
}
