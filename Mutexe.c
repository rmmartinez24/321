#include <stdio.h>
#include <pthread.h>

int counter = 0; 
pthread_mutex_t semaphore; 

void*increment_counter(void*arg)
{
    int i; 
    for(i=0; i < 10000; i++)
    {
        pthread_mutex_lock(&semaphore);
        counter = counter +1; 
        pthread_mutex_unlock(&semaphore); 
    }
    return NULL;
}

int main()
{
     pthread_t r1, r2;

    pthread_mutex_init(&semaphore, NULL);

    pthread_create(&r1, NULL, increment_counter, NULL);
    pthread_create(&r2, NULL, increment_counter, NULL);

    pthread_join(r1, NULL);
    pthread_join(r2, NULL);

    printf("Counter value: %d ", counter);

    pthread_mutex_destroy(&semaphore);

    return 0;
}