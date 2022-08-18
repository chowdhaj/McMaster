#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main(void) {

    /* The size (in bytes) of shared memory object */
    const int SIZE = 4096;

    /* The name of the shared memory object */
    const char *name = "OS";

    /* Shared memory file descriptor */
    int fd;

    /* Pointer to shared memory object */
    char *ptr;

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
