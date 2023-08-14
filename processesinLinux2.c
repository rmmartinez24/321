#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <spawn.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc !=2)
    {
        printf("Usage: %s <application_path>\n",argv[0]);
        return 1;
    }

    pid_t pid;
    posix_spawn_file_actions_t actions;
    posix_spawn_file_actions_init(&actions);

    if (posix_spawn(&pid, argv[1], &actions, NULL, argv + 1, NULL) !=0)
    {
        perror("posix_spawnp filed");
        return 1;
    }

    printf ("Spawned process with ID: %d\n", (int)pid);

    int status;
    waitpid(pid, &status, 0);

    posix_spawn_file_actions_destroy(&actions);

    return 0;
}