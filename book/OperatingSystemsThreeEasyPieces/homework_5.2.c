#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    close(STDOUT_FILENO);
    open("./homework.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        printf("I am in child\n");
    }
    else
    {
        printf("I am in parent\n");
    }
    return 0;
}
