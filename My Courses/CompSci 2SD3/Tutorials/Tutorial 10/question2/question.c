#include <pthread.h>
#include <stdio.h>
#include <errno.h>

pthread_mutex_t flock = PTHREAD_MUTEX_INITIALIZER;

void* doit(void* a);

int main() {

    pthread_t tid1, tid2;
    
    int* ret;
    
    if (pthread_create(&tid1, NULL, doit,NULL) != 0) {
        printf("Error:%d", errno);
        return -1;
    }
    
    if (pthread_create(&tid2, NULL, doit,NULL) != 0) {
        printf("Error:%d", errno);
        return -1;
    }

    if (pthread_join(tid1,(void**)ret) != 0) {
        printf("Error:%d", errno);
        return -1;
    }

    if (pthread_join(tid2,(void**)ret) != 0) {
        printf("Error:%d", errno);
        return -1;
    }

    printf("terminating the process\n");
    return 0;

}

void* doit(void* a) {

    pthread_mutex_lock(&flock);
    printf("thread %lu, hey\n", pthread_self());
    printf("thread %lu, bye\n", pthread_self());
    pthread_mutex_unlock(&flock);
    pthread_exit(NULL);

}