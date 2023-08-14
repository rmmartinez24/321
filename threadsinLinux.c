#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thread1_function(void *arg) {
    for (int i = 0; i < 10; ++i) {
        printf("Thread 1: Message %d\n", i + 1);
        sleep(1);
    }
    pthread_exit(NULL);
}

void *thread2_function(void *arg) {
    for (int i = 0; i < 10; ++i) {
        printf("Thread 2: Message %d\n", i + 1);
        sleep(2);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;

    //thread 1
    if (pthread_create(&thread1, NULL, thread1_function, NULL) != 0) {
        perror("pthread_create for thread 1");
        exit(EXIT_FAILURE);
    }

    // thread 2
    if (pthread_create(&thread2, NULL, thread2_function, NULL) != 0) {
        perror("pthread_create for thread 2");
        exit(EXIT_FAILURE);
    }

    if (pthread_join(thread1, NULL) != 0) {
        perror("pthread_join for thread 1");
        exit(EXIT_FAILURE);
    }

    if (pthread_join(thread2, NULL) != 0) {
        perror("pthread_join for thread 2");
        exit(EXIT_FAILURE);
    }

    printf("Main program exit.\n");

    return 0;
}
