#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void resourceAccess(int processNum) 
{
    // Simulate resource access
    printf("Process %d: Trying to access resource\n", processNum);
    sleep(2);
    printf("Process %d: Resource accessed\n", processNum);
}

void handleTimeout(int sig) 
{
    printf("Timeout occurred! Process will be terminated.\n");
    exit(1);
}

int main() 
{
    signal(SIGALRM, handleTimeout);

    pid_t p1, p2;
    
    p1 = fork();
    if (p1 == 0) 
    { // Child process P1
        printf("Process P1: Running\n");
        resourceAccess(1);
        return 0;
    }
    
    p2 = fork();
    if (p2 == 0) 
    { // Child process P2
        printf("Process P2: Running\n");
        resourceAccess(2);
        return 0;
    }
    
    // Parent process
    sleep(5);

    return 0;
}
