//child process will exit from the first loop when receiving
//signal SIGUSR1 or SIGUSR2, and exit from the second loop
//when receiving only signal SIGUSR2.
//Main process will send signal SIGUSR2 twice to terminate
//child process when receiving signal SIGHUP, then exit.

#include <stdio.h>
#include <signal.h>
#include <pthread.h>

int flag_sigusr1 = 0;
int flag_sigusr2 = 0;
int flag_sighup = 0;

void sig_usr1(int signo)
{
    fprintf(stdout, "sig | caught SIGUSR1\n");
    flag_sigusr1 = 1;
    return;
}

void sig_usr2(int signo)
{
    fprintf(stdout, "sig | caught SIGUSR2\n");
    flag_sigusr2 = 1;
    return;
}

void sig_hup(int signo)
{
    fprintf(stdout, "sig | caught SIGNUP\n");
    flag_sighup = 1;
    return;
}

void *thread_control_signal(void *arg)
{
    sigset_t newmask, oldmask;
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGHUP);
    if (pthread_sigmask(SIG_BLOCK, &newmask, &oldmask) < 0)
    {
        perror("sigprocmask error");
    }

    fprintf(stdout, "thread | first while, catch sigusr1 or sigusr2 can break\n");
    while (1)
    {
        if (flag_sigusr1 || flag_sigusr2)
        {
            fprintf(stdout, "thread | break\n");
            break;
        }
    }
    flag_sigusr1 = 0;
    flag_sigusr2 = 0;

    sigaddset(&newmask, SIGUSR1);
    if (pthread_sigmask(SIG_BLOCK, &newmask, &oldmask) < 0)
    {
        perror("sigprocmask error");
    }

    fprintf(stdout, "thread | first while, catch sigusr2 can break\n");
    while (1)
    {
        if (flag_sigusr1 || flag_sigusr2)
        {
            fprintf(stdout, "break\n");
            break;
        }
    }

    fprintf(stdout, "thread | thread exit\n");
    return;
}

int main()
{
    sigset_t newmask;
    pthread_t tid;
    int signo;

    signal(SIGUSR1, sig_usr1);
    signal(SIGUSR2, sig_usr2);
    signal(SIGHUP, sig_hup);

    if (pthread_create(&tid, NULL, thread_control_signal, NULL) < 0)
    {
        perror("create pthread failed");
        return -1;
    }

    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1);
    if (pthread_sigmask(SIG_BLOCK, &newmask, NULL) < 0)
    {
        perror("sigprocmask error");
    }

    sigemptyset(&newmask);
    sigaddset(&newmask, SIGHUP);
    if (sigwait(&newmask, &signo) < 0)
    {
        perror("sigwait failed");
        return -1;
    }
    fprintf(stdout, "main | get SIGHUP\n");

    pthread_kill(tid, SIGUSR2);
    sleep(1);
    pthread_kill(tid, SIGUSR2);
    pthread_join(tid, NULL);

    fprintf(stdout, "main | exit\n");
    return 0;
} 
