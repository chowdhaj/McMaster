#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int global_value = 0;

void * runner (void * wow);

int main(int youcancallitanythingoyuwant, char * argv[]) {
    
    pid_t pid;
    pthread_t tid;
    pthread_attr_t attr;
    pthread_t tid1;

    pid = fork();

    if (pid == 0) {

        printf("[CHILD] Value = %d\n", global_value); // LINE C1
        
          ///////////
         // CHILD //
        /////////// 
        pthread_attr_init(&attr);
        pthread_create(&tid, &attr, runner, NULL);
        pthread_join(tid, NULL);
        printf("[CHILD] Value = %d\n", global_value); // LINE C2

        pthread_create(&tid1, &attr, runner, NULL);
        pthread_join(tid, NULL);
        printf("[CHILD] Value = %d\n", global_value); // LINE C2

    } else {

          ////////////
         // PARENT //
        ////////////
        wait(NULL);
        printf("[PARENT] Value = %d\n", global_value); // LINE P

    }

    //pthread_join

    return 0;

}

void * runner (void * wow) {
    global_value += 5;
    pthread_exit(NULL);
}


//int something() { return int }

//float something() { return float }

//void * something() { return anything }








