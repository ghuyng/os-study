#include <stdio.h>
#include <stdlib.h>
#include "ex1.h"
#include "my_malloc.h"

void *aligned_malloc(unsigned int size, unsigned int align)       
{                                                                 
    if (size == 0 || align == 0)                                                
        return NULL;                                              

    /*Check if align is power of 2 */
    if ((align & (align - 1)) != 0)
    {
        printf("Align must be power of 2 !!");
        return NULL;
    }
        
    size_t alloc_size = (size_t)(size + align - 1 + sizeof(void*));
    void *p1 = my_malloc(alloc_size);
    if (!p1)                                                       
        return NULL;                                               

    /*Get the address that is multiple of align                    */
    /*Address is multiple of 2^n iff last n bits is 0              */
    /*~(align - 1) is 0b11...100...0 with n last bits is 0         */
    /*so AND-operation will give the address that multiple of align*/
    size_t aligned_addr = (size_t)(p1 + sizeof(void*) + align - 1) & (~((size_t)align - 1));
    void *p2 = (void*)(aligned_addr);

    /*Store the pointer p1 to use for aligned_free*/
    *((void**)(aligned_addr - sizeof(void*))) = p1;
    return p2;                                                     
}

void *aligned_free(void *ptr)
{
    if (!ptr)
        return NULL;
    /*Get the pointer of the block memory*/
    void *block_ptr= *((void**)((size_t)ptr - sizeof(void*))); 
    my_free(block_ptr);
    return ptr;
}

