#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

sem_t semaphore;

struct thread_data 
{
    int thread_id;
    char *message;
};

void * thread(void * arg)
{
    sem_wait(&semaphore);
    struct thread_data *td = (struct thread_data *)arg;

    printf("Car %d is in the parking lot\n", td->thread_id);
    printf("%s\n", td->message);

    sleep(1);
    
    printf("Car %d is Parked\n\n", td->thread_id);
    td->message = "Taken";


    sem_post(&semaphore);
    return (void *)td;
}

int main(void)
{    

    sem_init(&semaphore, 0, 1);
    pthread_t parking;

    struct thread_data parked;

    for (int i = 0; i < 12; i++)
    {
        parked.thread_id = i + 1;
        parked.message = "Car parking";

        pthread_create(&parking, NULL, thread, (void*)(&parked));
        pthread_join(parking, (void *)(&parked));
        
        printf("Spot %d: %s\n\n", i + 1, parked.message);
    }
    
    sem_destroy(&semaphore);

    return EXIT_SUCCESS;
}