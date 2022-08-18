#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function(void *parameter);

int main() {
  pthread_t thread1, thread2;
  char *message1 = "Thread 1 running";
  char *message2 = "Thread 2 running";

  int ret1 = pthread_create(&thread1, NULL, thread_function, (void *)message1);
  int ret2 = pthread_create(&thread1, NULL, thread_function, (void *)message2);

  // how many threads we have now in total ?   3 threads in total
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  printf("main complete\n");
  return 0;
}

void *thread_function(void *parameter) {
  pthread_t id = pthread_self();
  char *message = (char *)parameter;
  printf("Thread %lu: %s\n", id, message);
}

