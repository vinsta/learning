//key word "volatile" can be used to avoid optimized by compiler
//to missing some instructions.

#include <stdio.h>

int main()
{
    volatile const int count = 10;
    int *p = NULL;
    p = (int*)&count;
    *p = 20;
    printf("%d\n", count);
    return 0;
}
