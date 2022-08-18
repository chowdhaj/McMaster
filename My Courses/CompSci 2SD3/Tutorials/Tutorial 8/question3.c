//question3.c

#include <pthread.h>

int main() {

    int tid1, tid2;
    int* ret;
    int a;

    a=2;
    if (pthread_create(&tid1, NULL, doit,(void*)&a) != 0)
        sys_exit("pthread error\n");

    a=3;
    if (pthread_create(&tid2, NULL, doit,(void*)&a) != 0)
        sys_exit("pthread error\n");

    pthread_join(tid1,(void**)ret);
    pthread_join(tid2,(void**)ret);

    msg_exit("terminating the process\n");

    return 0;
}

void* doit(void* a) {
    // PULL OUT
    msg("got %d\n",*((int*)a));
    pthread_exit(NULL);
}