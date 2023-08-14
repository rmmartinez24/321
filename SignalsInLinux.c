#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define WAKEUP_SIGNAL SIGUSR1

void child_handler(int signum) {
    if (signum == WAKEUP_SIGNAL) {
        printf("Child process received WAKEUP signal.\n");
        for (int i = 0; i < 20; i++) {
            printf("Child: Iteration %d\n", i);
            sleep(1);
        }
        exit(1);
    }
}

int main() {
    pid_t child_pid;
    
    // Creating child process
    child_pid = fork();
    
    if (child_pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (child_pid == 0) {

        signal(WAKEUP_SIGNAL, child_handler);
        
        printf("Child process is sleeping...\n");
        pause();
    } else {
        
        // Parent process
        for (int i = 0; i < 30; i++) {
            printf("Parent: Iteration %d\n", i);
            sleep(1);
            if (i == 5) {
                kill(child_pid, WAKEUP_SIGNAL);
            }
        }
        exit(1);
    }
    
    return 0;
}
