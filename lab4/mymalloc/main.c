#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "ex1.h"

int main()
{
    void *ptr, *before_brk, *after_brk;
    printf("Test aligned_malloc and aligned_free\n");

    before_brk = sbrk(0);
    printf("program break before calling aligned_malloc : %p\n\n", before_brk);

    printf("----------Test if size == 0----------\n");
    ptr = aligned_malloc(0, 4);                            
    printf("Address return by aligned_malloc(0, 4) : %p\n", ptr);
    assert(ptr == NULL);

    printf("----------Test for different align value----------\n");
    unsigned int aligns[6] = {0, 8, 16, 64, 128, 7};
    for (int i = 0; i < 6; i++)                                                
    {                                                                          
        ptr = aligned_malloc(5, aligns[i]);                            
        printf("Address return by aligned_malloc(5, %d) : %p\n", aligns[i], ptr);
        assert(!ptr || (size_t)ptr % aligns[i] == 0);                          
        aligned_free(ptr);                                                     
    }                                                                          

    after_brk = sbrk(0);
    printf("\nprogram break after calling aligned_free to deallocate all the memory: %p\n", after_brk);
    assert(before_brk == after_brk);

    return 0;
}

