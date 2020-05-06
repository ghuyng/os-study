#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "my_malloc.h"
#include "ex1.h"

int main()
{
    /*char *str, *str2;           */
    /*str = (char *)my_malloc(1); */
    /*str2 = (char *)my_malloc(1);*/
    printf("\n");
    printf("program break before calling aligned_malloc : %p\n", sbrk(0));
    printf("%p\n", sbrk(0));
    printf("%p\n", sbrk(0));
    int *p = (int*)aligned_malloc(sizeof(int) * 4, 8);
    /*int *p = (int*)malloc(sizeof(int) * 4);*/
    printf("%p\n", sbrk(0));
    /*printf("Address str = %p\n",str); */
    /*printf("Address str = %p\n",str2);*/
    printf("Address str = %p\n",p);
    /*str[0] = 'a';*/
    /*str[1] = 'b';*/
    p[0] = 1;
    p[1] = 2;
    /*printf("%s\n",str);*/
    printf("%d\n",p[1]);
    
    printf("%p\n", sbrk(0));
    printf("%ld\n", ((size_t)sbrk(0) - (size_t)p));
    /*my_free(str); */
    /*my_free(str2);*/
    aligned_free(p);
    /*free(p);*/
    /*printf("Address str = %p\n",str); */
    /*printf("Address str = %p\n",str2);*/
    printf("Address str = %p\n",p);
    /*printf("%s\n",str);*/
    /*printf("%d\n",p[1]);*/
    printf("%p\n", sbrk(0));
    return 0;
}

