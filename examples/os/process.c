#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int single_process()
{
    pid_t pid;
    /* fork a child process */
    printf("exce: %d \n", pid);
    pid = fork();
    if (pid < 0) { /* error occurred */
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    else if (pid == 0) { /* child process */
        execlp("/bin/ls","ls", NULL);
    }
    else { /* parent process */
    /* parent will wait for the child to complete */
        wait(NULL);
        printf("Child Complete");
    }
    return 0;
}

int mutiple_processes() {
    pid_t pids[10];
    int i;
    int n = 10;
    int mutex = 0;

    /* Start children. */
    for (i = 0; i < n; ++i) {
        if ((pids[i] = fork()) < 0) {
            perror("fork");
            abort();
        } else if (pids[i] == 0) {
            printf("Child Process: %d \n", i);
            // the mutex variable manipulated by all the children processes is not shared,
            // it is just a copy of original variable defined in the parent processes,
            // since its value always be 0
            mutex++;
            printf("Child Process mutex: %d \n", mutex);
            exit(0);
        }
    }

    /* Wait for children to exit. */
    int status;
    pid_t pid;
    // at parent processes, we need to wait all the child processes,  since the children' 
    // exit randomly, the wait will return the exited process id
    while (n > 0) {
        pid = wait(&status);
        // do little works as 1 child process has completed
        printf("Child with PID %ld exited with status 0x%x.\n", (long)pid, status);
        --n;  // TODO(pts): Remove pid from the pids array.
    }

    return 0;
}

int main() {
    return mutiple_processes();
}