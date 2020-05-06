/*
 * nMalloc.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: prasadnair
 */

#include <stdlib.h>
#include <stdio.h>

void * aligned_malloc(size_t size, int align) {
    /* alignment could not be less then zero */
    if (align < 0) {
        return NULL;
    }

    /* Allocate necessary memory area client request - size parameter -
     * plus area to store the address of the memory returned by standard
     * malloc().
     */
    void *ptr;
    
    /* accomodating atleast one aligned memory area by adding align-1
    /  size of (void *) is added since we intent to keep the below address
    /   in p. This will be retrieved later during free
    */
    void *p = malloc(size + align - 1 + sizeof(void*));

    if (p != NULL) {

        /* Address of the aligned memory according to the align parameter*/
        ptr = (void*) (((size_t)p + sizeof(void*) + align -1) & ~(align-1));

        /* store the address of the malloc() above the beginning of our total memory area.
         */
        *((void**)((size_t)ptr - sizeof(void*))) = p;

        /* Return the address of aligned memory */
        return ptr;
    }
    return NULL;
}

void aligned_free(void *p) {
    /* Get the address of the memory, stored at the
     * start of our total memory area.
     */
    void *ptr = *((void**)((size_t)p - sizeof(void*)));
    free(ptr);
    return;
}


int  main ()
{

    int align;
    for (align = 2; align < 5000000; align= align*2)
    {

        int *p = (int *) aligned_malloc (1024, align);

       // trying to see if its aligned properly by finding mode with align
       // mode operator should always return zero if memory is aligned to align
        printf (" %p %d \n",  p, ((long int)p)%align);
        aligned_free (p);
    }
    return 0;
}
