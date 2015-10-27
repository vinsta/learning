#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int num = 100;
    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "fork failed");
	exit(1);
    }
    else if (rc == 0)
    {
        printf("num is %d in child\n", num);
	num++;
	printf("num is %d in child after change\n", num);
    }
    else
    {
        printf("num is %d in parent\n", num);
	int wc = wait(NULL);
	printf("num is %d in parent after child exit\n", num);
	num--;
	printf("num is %d in parent after change\n", num);
    }
    return 0;
}
