/**
 * Assume all header files have been imported, and disregard syntax.
 * Assume that the code compiles without warnings/errors.
 */

int COUNT = 5;

main(){

    pid_t pid;
    pthread_t tid1, tid2;

    for (int i = 0; i < COUNT; i++) {
        
        pthread_create(tid1, ...);
        fork();

        if (pthread_join(tid1, NULL))
            printf("ERROR:ThreadJoinedException\n");
        else
            printf("Thread %d Joined Successfully\n");
    }

    while ((pid = fork()) == 0) pthread_create(tid2, ...);

    if (pthread_join(tid2, NULL))
        printf("ERROR:ThreadJoinedException\n");
    else
        printf("Thread %d Joined Successfully\n");

    printf("DONE!\n");
}
