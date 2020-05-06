#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int pid = fork();
    switch(pid){
        case 0:
            printf("Child process pid = %d\n",getpid());
            sleep(20);
            break;
        case -1:
            perror("Fail to fork\n");
            break;
        default:
            printf("Parrent process pid = %d\n", getpid());
    }

    return 0;
}


