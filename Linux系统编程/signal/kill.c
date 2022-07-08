#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define N 5

int main(void)
{
    int i;
    pid_t pid, q;

    for (i = 0; i < N; i++) {
        pid = fork();
        if (pid == 0)
            break;
        if (i == 2)
            q = pid;
    }
    if (i < 5) {            //子进程
        while(1) {
            printf("I'm child %d, getpid = %u\n", i, getpid());
            sleep(1);
        }

    } else {                //父进程
        sleep(3);
        kill(q, SIGKILL);
        printf("------------kill %d child %u finish\n", 2, q);
        while (1);
    }

    return 0;
}
