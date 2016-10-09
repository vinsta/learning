#include <stdio.h>
#include <time.h>

int main(int argc, const char* argv[])
{
    time_t t = time(0);
    struct tm *standTime = gmtime(&t);
    struct tm currentTime; 
    localtime_r(&t, &currentTime);
    char s[80];
    strftime(s, 80, "%Y-%m-%d WK%U %a %H:%M:%S::%Z", standTime);
    printf("%d: %s\n", (int)t, s);
    strftime(s, 80, "%Y-%m-%d WK%U %a %H:%M:%S::%Z", &currentTime);
    printf("%d: %s\n", (int)t, s);
}
