#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void *simple_malloc(size_t size)
{
    void *p = sbrk(0);
    if (sbrk(size) == (void*)-1)
        return NULL;
    return p;
}

int main()
{
    /*void *p = simple_malloc(1);      */
    /*printf("simp address = %p\n", p);*/
    char *ip = (char*)simple_malloc(2);
    ip[0] = 'c';
    ip[1] = 'h';
    ip[2] = 'g';
    ip[3] = 'k';

    printf("%s",ip);

    char *up = (char*)malloc(2);
    up[0] = 'c';
    up[1] = 'h';
    up[2] = 'g';
    up[3] = 'k';

    printf("%s",up);
    /*free(ip);*/

    free(up);
    /*sleep(3);*/
    return 0;
}
