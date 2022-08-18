question5.c

pthread_mutex_t flock = PTHREAD_MUTEX_INITIALIZER;

// function main -----------------------------------------------------
int main() {

    int tid1, tid2;
    int* ret;
  
    if (pthread_create(&tid1, NULL, doit,NULL) != 0)
        sys_exit("pthread error\n");

    if (pthread_create(&tid2, NULL, doit,NULL) != 0)
        sys_exit("pthread error\n");

    pthread_join(tid1,(void**)ret);
    pthread_join(tid2,(void**)ret);

    msg_exit("terminating the process\n");
    
    return 0;
}

void* doit(void* a) {
    pthread_mutex_lock(&flock);
    msg("thread %d, hit enter to continue", pthread_self());
    getchar();
    msg("thread %d, bye\n", pthread_self());
    pthread_exit(NULL);
}

/*

------
OUTPUT
------

Scenario A:
    thread 2, hit enter to continue
    thread 2, bye
    thread 3, hit enter to continue
    thread 3, bye
    terminating the process

Scenario B:
    thread 2, hit enter to continue
    thread 2, hit enter to continue
    thread 2, bye

*/
