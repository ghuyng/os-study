#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    printf("Process ID : %d\n",getpid());
    printf("Parent's process ID : %d\n", getppid());
    printf("Process Group ID : %d", getpgrp());
    return 0;
}
