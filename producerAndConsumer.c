#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>

int MAX = 100; 
int WAKEUP = SIGUSR1; 
int SLEEP = SIGUSR2; 

pid_t otherPid; 

sigset_t sigSet; 


struct CIRCULAR_BUFFER
{
    int count; 
    int start; 
    int end; 
    int buffer[100];
}; 

struct CIRCULAR_BUFFER *buffer = NULL; 


void waitUntilWoken()
{
    int nSig;

    printf("Sleeping.....\n");
    sigwait(&sigSet, &nSig);

    printf("Awaken: \n");

}


void wakingUpAlt()
{   
    kill(otherPid, SIGUSR1);
}


int getValue()
{
    int value = buffer->buffer[buffer->end];
    printf("Consumer value %c\n", value);

    ++buffer->end;
    if(buffer->end == MAX)
    buffer -> end=0;
    --buffer->count;

    return value;
}


void putValue(int value)
{
    buffer->buffer[buffer->start]=value;
    printf("Producer value of %c\n", buffer->buffer[buffer->start]);

    ++buffer->start; 
    if(buffer->start == MAX)
    buffer->start = 0; 
    ++buffer->count;
}


void consumer()
{
    sigemptyset(&sigSet);
    sigaddset(&sigSet, WAKEUP);
    sigprocmask(SIG_BLOCK, &sigSet, NULL);

    printf("Running Consumer Process \n");
    waitUntilWoken();
    int name = 0; 
    while(name !=0)
    {
        name=getValue();
        sleep(1); 
        ++name; 
    }
    printf("Currently Exiting Consumer Process \n");
    exit(1);
}


void producer()
{
    int value =0;
    printf("Currently Running Producer Process \n"); 
    char myName[5] = "Kevin"; 
    for(int x =0; x< strlen(myName);++x)
    {
        putValue(myName[x]);
        sleep(1); 
    }
    putValue(0);
    wakingUpAlt();

    printf("Exiting Producer Process...\n");
    exit(1);
}


int main(int argc, char* argv[])
{
    pid_t pid; 
    buffer=(struct CIRCULAR_BUFFER*)mmap(0,sizeof(buffer),PROT_READ| PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1,0);
    buffer ->count=0;
    buffer->start=0;
    buffer->end=0; 

    pid = fork();

    if (pid == -1)
    {
        printf("Can't fork, error %d\n", errno);
    }

    if (pid == 0)
    {
        otherPid = getppid();
        producer();
    }

    else
    {
        otherPid=pid;
        consumer();
    }
}