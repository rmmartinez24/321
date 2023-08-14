#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Fork faild");
        return 1;
    }

    else if (pid == 0) 
    {
        for (int i = 0; i < 10; i++)
        {
            printf("Child process: %d\n", i +1);
            sleep(1);
        }
        exit(0);
    }

    else
    {
        for (int i = 0; i < 10; i++)
        {
            printf("Parent process: %d\n", i +1);
            sleep(2);
        }
        wait(NULL);
    }

    return 0;
}