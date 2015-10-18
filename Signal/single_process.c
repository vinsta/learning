//How to set signal handler and mask signal in a single process

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int flag_sigusr1 = 0;
int flag_sigusr2 = 0;

void sig_usr1(int signo)
{
    fprintf(stdout, "caught SIGUSR1\n");
    flag_sigusr1 = 1;
    return;
}

void sig_usr2(int signo)
{
    fprintf(stdout, "caught SIGUSR2\n");
    flag_sigusr2 = 1;
    return;
}

int main(void)
{
    sigset_t newmask, oldmask;
    signal(SIGUSR1, sig_usr1);
    signal(SIGUSR2, sig_usr2);

    fprintf(stdout, "first while, catch sigusr1 can break\n");
    while(1)
    {
        if (flag_sigusr1)
        {
            fprintf(stdout, "break");
            break;
        }
        sleep(10);
    }
    flag_sigusr1 = 0;
    flag_sigusr2 = 0;

    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1);
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
    {
        perror("sigprocmask error");
    }

    fprintf(stdout, "first while, catch sigusr1 or sigusr2 can break\n");
    while(1)
    {
        if (flag_sigusr1 || flag_sigusr2)
        {
            fprintf(stdout, "break");
            break;
        }
        sleep(10);
    }

    return 0;
}
