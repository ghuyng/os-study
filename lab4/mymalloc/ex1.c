#include <stdio.h>
#include <stdlib.h>
#include "ex1.h"
#include "my_malloc.h"

void *aligned_malloc(unsigned int size, unsigned int align)       
{                                                                 
    if (size == 0)                                                
        return NULL;                                              

    if ((align & (align - 1)) != 0)
    {
        printf("Align must be power of 2 !!");
        return NULL;
    }
        
    size_t total_size = (size_t)(size + align - 1 + sizeof(void*));
    void *p1 = my_malloc(total_size);
    if (!p1)                                                       
        return NULL;                                               

    size_t aligned_addr = (size_t)(p1 + sizeof(void*) + align - 1) & (~((size_t)align - 1));
    void *p2 = (void*)(aligned_addr);
    *((void**)(aligned_addr - sizeof(void*))) = p1;
    return p2;                                                     
}

void *aligned_free(void *ptr)
{
    void *real_ptr = *((void**)((size_t)ptr - sizeof(void*))); 
    my_free(real_ptr);
    return ptr;
}
