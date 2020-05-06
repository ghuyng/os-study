#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    size_t MB = 1024 * 1024;
    size_t maxMB = 0;
    void *ptr = NULL;

    do{
        if (ptr)
        {
            printf("Bytes of memory checked: %zi\n", maxMB);
            memset(ptr, 0, maxMB);
        }
        maxMB += MB;
        ptr = malloc(maxMB);
    }while(ptr);

    return 0;
}
