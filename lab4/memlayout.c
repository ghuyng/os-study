#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int glo_init_data = 99;
int glo_noninit;

void func()
{
    int local_data = 9;
    printf("Process ID = %d\n", getpid());
    printf("Addresses of the process:\n");
    printf("1. Global init data = %p\n",&glo_init_data);
    printf("2. Global uninit data = %p\n", &glo_noninit);
    printf("3. func() = %p\n", &func);
    printf("4. local data = %p\n", &local_data);
}

int main()
{
    func();
    /*sleep(3);*/
    return 0;
}
