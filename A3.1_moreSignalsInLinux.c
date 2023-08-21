#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <errno.h>

// constants 
int max = 100;
int wakeup = SIGUSR1; 
int SLEEP = SIGUSR2; 

pid_t otherPid; //child pid 
sigset_t sigSet; //signal set

struct CIRCULAR_BUFFER
{
    int buffer[100];
    int count; 
    int lower;
    int upper;
};

struct CIRCULAR_BUFFER *buffer = NULL;

void sleepAndWait()
{
    int nSig; 

    printf("Sleeping........\n");
    sigwait(&sigSet, &nSig);
    printf("Awoken\n");
}

void wakeupOther()
{
    kill(otherPid, wakeup);
}

int getValue()
{
    int value = buffer->buffer[buffer->lower];
    printf("Consume read value of %c\n", value);
    ++buffer->lower;

    if (buffer->lower == max)

        buffer->lower = 0;
        --buffer->count;

        return value;

}

void putValue(int value)
{
    buffer->buffer[buffer->upper] = value;
    printf("Producer stored value of %c\n", buffer->buffer[buffer->upper]);
    ++buffer->upper;

    if (buffer->upper == max)
        buffer->upper = 0;
        ++buffer->count;
}

void consumer()
{
    sigemptyset(&sigSet);
    sigaddset(&sigSet, wakeup);
    sigprocmask(SIG_BLOCK, &sigSet, NULL);

    printf("Running the child conssumer process...\n");

    int character = 0;

    do
    {
       sleepAndWait();
       character = getValue();

    } while (character !=0);

    printf("Exiting the child consumer process...\n");
    _exit(1);
    
}

void producer()
{
    int value = 0;

    printf("Running the parent producer process...\n");

    char message[10] = "Rod Martinez";
    for(int x =0; x < strlen(message); ++x)
    {
        putValue(message[x]);
        wakeupOther();
        sleep(1);
    }

    putValue(0);
    wakeupOther();

    printf("Exiting the parent producer process...\n");
    _exit(1);
}

int main(int argc, char*argv[])
{
    pid_t pid;

    buffer = (struct CIRCULAR_BUFFER*)mmap(0,sizeof(buffer), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    buffer->count = 0;
    buffer->lower = 0;
    buffer->upper = 0;

    pid = fork();

    if (pid == -1)
    {
        printf("Can't fork, error %d\n", errno);
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        otherPid = getppid();
        producer();
    }
    else
    {
        otherPid = pid;
        consumer();
    }
    
    return 0;
}