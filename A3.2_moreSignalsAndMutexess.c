#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

pthread_mutex_t mutex;
long counter;
time_t end_time;

void *counter_thread (void *arg)
{
    int status;

    while (time (NULL) < end_time)
    {
        status = pthread_mutex_lock (&mutex);

        if (status == 0)
        printf("Counter Thread: Locked mutex for Counter so it can be incremented\n");
        ++counter;
        status = pthread_mutex_unlock(&mutex);

        if(status == 0)
        printf("Counter Thread: Unlock mutex for Counter since we are done with the Counteer\n");

        sleep(1);
    }
    
    printf("Final counter is %lu\n",counter);
    return NULL;
}

void *monitor_thread (void *arg)
{
    int status;
    int misses = 0;

    while (time (NULL) < end_time)
    {
        sleep(3);
        status = pthread_mutex_trylock (&mutex);

        if (status !=EBUSY)
        {
            printf("Monitor Thread: The trylock will lock the mutez so we can safely read the Counter\n");
            printf("Monitor Thread: The Counter from Monitor is s%ld\n", counter);

            status = pthread_mutex_unlock (&mutex);

            if (status == 0)
            {
                printf("Moniter Thread: Will now unlcok the mutex since we are done with the Counter\n");
            }
            else
            {
                ++misses;
            }
        }

        printf("Final Moniter: Thread missed we %d times. \n", misses);
        return NULL;  
    }
    
}

int main(int argc, char *argv[])
{
    int status;
    pthread_t counter_thread_id;
    pthread_t monitor_thread_id;

    pthread_mutex_init(&mutex, 0);
    end_time = time (NULL) + 60;

    if(pthread_create (&counter_thread_id, NULL, counter_thread, NULL))
        printf("Create counter thread failed");

    if(pthread_create (&monitor_thread_id, NULL, counter_thread, NULL))
        printf("Create counter thread failed");



    if(pthread_join(counter_thread_id, NULL))
        printf("Joined counter thread failed");

    if(pthread_join(monitor_thread_id, NULL))
        printf("Joined counter thread failed"); 

    return 0;       
}